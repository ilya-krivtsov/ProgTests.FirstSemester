$root = $PSScriptRoot

$buildDirectory = [System.IO.Path]::Combine($root, "build")

if (Test-Path -Path config.env -PathType Leaf)
{
    Get-Content config.env | ForEach-Object {
        $name, $value = $_.Split('=')
        Set-Content env:\$name $value
    }
}

$cmake = $env:TESTS_CMAKE
$compiler = $env:TESTS_CMAKE_COMPILER
$generator = $env:TESTS_CMAKE_GENERATOR
$executableExtension = $env:TESTS_EXE_EXTENSION

if (-not $cmake)
{
    Write-Error "cmake not specified"
    exit 1
}

if (-not $compiler)
{
    Write-Error "compiler not specified"
    exit 1
}

if (-not $generator)
{
    Write-Error "generator not specified"
    exit 1
}

if (-not $executableExtension)
{
    Write-Host "warning: executable extension not specified - assuming there is no executable extension"
    $executableExtension = 'none'
}

if ($executableExtension -eq 'none')
{
    $executableExtension = ''
}

function Invoke-Command($command, $commandArgs, $workingDirectory, $quiet)
{
    $returnTo = $pwd
    Set-Location $workingDirectory
    try
    {
        Invoke-Expression "& `"$command`" $commandArgs $(if ($quiet) {'| Out-Null'} else {''})"
    }
    finally
    {
        Set-Location $returnTo
        if ($LastExitCode -ne 0) { exit 1 }
    }
}

function Invoke-CMakeBuildInternal($target, $configuration, $quiet)
{
    $configurationCacheFile = "$buildDirectory/__last_configuration"
    $lastConfiguration = 'none'

    if (-not (Test-Path -Path $buildDirectory -PathType Container))
    {
        New-Item -ItemType Directory $buildDirectory | Out-Null
    }
    elseif (Test-Path -Path $configurationCacheFile -PathType Leaf)
    {
        $lastConfiguration = Get-Content $configurationCacheFile
    }

    if ($configuration -ne $lastConfiguration)
    {
        Invoke-Command "$cmake" @("-DCMAKE_BUILD_TYPE:STRING=$configuration", "-DCMAKE_C_COMPILER:FILEPATH=$compiler",
            "-S", $root, "-B", $buildDirectory, "-G", "'$generator'") $root $quiet

        $configuration | Out-File $configurationCacheFile
    }

    Invoke-Command "$cmake" @("--build", $buildDirectory, "--config", $configuration, "--target", $target, "-j", "14") $root $quiet
}

function Invoke-CMakeRunInternal($test, $task, $target, $quiet)
{
    Invoke-Command "$buildDirectory/$test/$task/$target$executableExtension" @() "$root/$test/$task" $quiet
}

function Invoke-CMakeBuild($test, $task, $configuration, $quietBuild)
{
    Invoke-CMakeBuildInternal "$($test)_$task" $configuration $quietBuild
}

function Invoke-CMakeRun($test, $task, $configuration, $quietBuild)
{
    Invoke-CMakeBuild $test $task $configuration $quietBuild
    Invoke-CMakeRunInternal $test $task "$($test)_$task"
}

function Invoke-CMakeBuildTest($test, $task, $configuration, $quietBuild)
{
    Invoke-CMakeBuildInternal "$($test)_$($task)_test" $configuration $quietBuild
}

function Invoke-CMakeTest($test, $task, $configuration, $quietBuild, $quietTest)
{
    Invoke-CMakeBuildTest $test $task $configuration $quietBuild
    Invoke-CMakeRunInternal $test $task "$($test)_$($task)_test" $quietTest
}

function Invoke-ForeachTestAndTask($toRun, $isTest)
{
    $rootFile = './CMakeLists.txt'
    foreach ($rootLine in Get-Content $rootFile)
    {
        if (-not ($rootLine -match 'add_subdirectory\((.*)\)')) { continue }

        $test = $Matches.1
        $testFile = "./$test/CMakeLists.txt"

        if (-not (Test-Path -Path $testFile -PathType Leaf))
        {
            Write-Host "test file '$testFile' not found"
            exit 1
        }

        foreach ($testLine in Get-Content $testFile)
        {
            if (-not ($testLine -match 'add_subdirectory\((.*)\)')) { continue }

            $task = $Matches.1
            $taskFile = "./$test/$task/CMakeLists.txt"

            if (-not (Test-Path -Path $testFile -PathType Leaf))
            {
                Write-Host "task file '$taskFile' not found"
                exit 1
            }

            foreach ($taskLine in Get-Content $taskFile)
            {
                if (-not ($taskLine -match 'add_executable\((.+) .+\)')) { continue }

                $target = $Matches.1

                if ($isTest -eq ($target -match '.+_test'))
                {
                    & $toRun $test $task
                }
            }
        }
    }
}

function Invoke-CMakeBuildAll($configuration, $quietBuild)
{
    Invoke-ForeachTestAndTask { param($test, $task) Invoke-CMakeBuild $test $task $configuration $quietBuild } $false
}

function Invoke-CMakeTestAll($configuration, $quietBuild, $quietTest)
{
    Invoke-ForeachTestAndTask { param($test, $task) Invoke-CMakeTest $test $task $configuration $quietBuild $quietTest } $true
}

$isDotSourced = $MyInvocation.InvocationName -eq '.' -or $MyInvocation.Line -eq ''
if ($isDotSourced)
{
    exit
}

$configuration = 'Debug'
$command = 'undefined_command'
$quietBuild = $false
$quietTest = $false
for ($i = 0; $i -lt $args.Count; $i++)
{
    $arg = $args[$i]
    switch -Regex ($arg)
    {
        { ($_ -eq 'build') -or ($_ -eq 'run') -or ($_ -eq 'buildTest') -or ($_ -eq 'test') }
        {
            $command = $arg
            $i++

            if ($i -ge $args.Count)
            {
                Write-Error "no test folder specified"
                exit 1
            }

            $test = $args[$i]
            if (-not (Test-Path -Path "$test" -PathType Container))
            {
                Write-Error "test folder '$test' not found"
                exit 1
            }
            $i++

            if ($i -ge $args.Count)
            {
                Write-Error "no task folder specified"
                exit 1
            }

            $task = $args[$i]
            if (-not (Test-Path -Path "$test/$task" -PathType Container))
            {
                Write-Error "task folder '$task' not found in test folder '$test'"
                exit 1
            }
        }
        { ($_ -eq 'buildAll') -or ($_ -eq 'testAll') } { $command = $arg }
        { ($_ -eq '-r') -or ($_ -eq '--release') } { $configuration = 'Release' }
        { ($_ -eq '-d') -or ($_ -eq '--debug') } { $configuration = 'Debug' }
        { ($_ -eq '-qb') -or ($_ -eq '--quiet-build') } { $quietBuild = $true }
        { ($_ -eq '-qt') -or ($_ -eq '--quiet-test') } { $quietTest = $true }
        { ($_ -eq '-c') -or ($_ -eq '--clear') } { Remove-Item -Recurse -Force -ErrorAction Ignore $buildDirectory }
        { $_ -eq 'clear' } { Remove-Item -Recurse -Force -ErrorAction Ignore $buildDirectory; exit 0 }
        default { Write-Error "unknown argument: $arg"; exit 1 }
    }
}

if ($command -eq 'undefined_command')
{
    Write-Error "command not specified"
    exit 1
}

switch ($command)
{
    build { Invoke-CMakeBuild $test $task $configuration $quietBuild }
    run { Invoke-CMakeRun $test $task $configuration $quietBuild }
    buildTest { Invoke-CMakeBuildTest $test $task $configuration $quietBuild }
    test { Invoke-CMakeTest $test $task $configuration $quietBuild $quietTest }
    buildAll { Invoke-CMakeBuildAll $configuration $quietBuild }
    testAll { Invoke-CMakeTestAll $configuration $quietBuild $quietTest }
}
