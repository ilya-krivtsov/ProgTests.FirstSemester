$root = $PSScriptRoot

$buildDirectory = [System.IO.Path]::Combine($root, "build")

if (Test-Path -Path config.env -PathType Leaf)
{
    Get-Content config.env | Foreach {
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

function Run-Command($command, $commandArgs, $workingDirectory, $quiet)
{
    $returnTo = $pwd
    cd $workingDirectory
    try
    {
        Invoke-Expression "& `"$command`" $commandArgs $(if ($quiet) {'| Out-Null'} else {''})"
    }
    finally
    {
        cd $returnTo
        if ($LastExitCode -ne 0) { exit 1 }
    }
}

function CMake-BuildInternal($target, $configuration, $quiet)
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
        Run-Command "$cmake" @("-DCMAKE_BUILD_TYPE:STRING=$configuration", "-DCMAKE_C_COMPILER:FILEPATH=$compiler",
            "-S", $root, "-B", $buildDirectory, "-G", "'$generator'") $root $quiet

        $configuration | Out-File $configurationCacheFile
    }

    Run-Command "$cmake" @("--build", $buildDirectory, "--config", $configuration, "--target", $target, "-j", "14") $root $quiet
}

function CMake-RunInternal($test, $task, $target, $quiet)
{
    Run-Command "$buildDirectory/$test/$task/$target$executableExtension" @() "$root/$test/$task" $quiet
}

function CMake-Build($test, $task, $configuration, $quietBuild)
{
    CMake-BuildInternal "$($test)_$task" $configuration $quietBuild
}

function CMake-Run($test, $task, $configuration, $quietBuild)
{
    CMake-Build $test $task $configuration $quietBuild
    CMake-RunInternal $test $task "$($test)_$task"
}

function CMake-BuildTest($test, $task, $configuration, $quietBuild)
{
    CMake-BuildInternal "$($test)_$($task)_test" $configuration $quietBuild
}

function CMake-Test($test, $task, $configuration, $quietBuild, $quietTest)
{
    CMake-BuildTest $test $task $configuration $quietBuild
    CMake-RunInternal $test $task "$($test)_$($task)_test" $quietTest
}

function DoForeach-TestAndTask($toRun)
{
    foreach ($test in Get-ChildItem -Filter "test_*")
    {
        foreach ($task in Get-ChildItem $test -Filter "task_*")
        {
            & $toRun $test.Name $task.Name
        }
    }
}

function CMake-BuildAll($configuration, $quietBuild)
{
    DoForeach-TestAndTask { param($test, $task) CMake-Build $test $task $configuration $quietBuild }
}

function CMake-TestAll($configuration, $quietBuild, $quietTest)
{
    DoForeach-TestAndTask { param($test, $task) CMake-Test $test $task $configuration $quietBuild $quietTest }
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
        default  { Write-Error "unknown argument: $arg"; exit 1 }
    }
}

if ($command -eq 'undefined_command' )
{
    Write-Error "command not specified"
    exit 1
}

switch ($command)
{
    build { Cmake-Build $test $task $configuration $quietBuild }
    run { Cmake-Run $test $task $configuration $quietBuild }
    buildTest { CMake-BuildTest $test $task $configuration $quietBuild }
    test { CMake-Test $test $task $configuration $quietBuild $quietTest }
    buildAll { CMake-BuildAll $configuration $quietBuild }
    testAll { CMake-TestAll $configuration $quietBuild $quietTest }
}
