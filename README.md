# Repository with tests from first semester

> [!NOTE]
> Build system is same as in [homework repository](https://github.com/ilya-krivtsov/ProgHomework.FirstSemester)

## Pre-build

Run

```sh
git submodule update --init
```

and create `config.env` in repository root; it should look like this:

```bash
TESTS_CMAKE="CMake path"
TESTS_CMAKE_COMPILER="C compiler path"
TESTS_CMAKE_GENERATOR="CMake generator"
TESTS_EXE_EXTENSION="executable files extension" # set to ".exe" on Windows and to "none" on Unix-like systems
```

You can also set those environment variables before running build script

## Commands

You can run either `build.sh` or `build.ps1`, they are functionally identical

Arguments in square brackets are optional

Arguments in parentheses must be specified only when running `build` / `run` / `buildTest` / `test` commands

```ps1
./build.ps1 {command} (test_x) (task_y) [-c|--clear] [-r|--release] [-d|--debug] [-qb|--quiet-build]
./build.sh {command} (test_x) (task_y) [-c|--clear] [-r|--release] [-d|--debug] [-qb|--quiet-build]
```

When running/testing tasks(s) working directory is set to `test_x/task_y`

Running task or testing also builds it, so you don't have to run both `build`/`buildTest` and `run`/`test` commands

| Command     | Description                                               |
|-------------|-----------------------------------------------------------|
| `build`     | Build `task_y` in `test_x`                                |
| `run`       | Build and run `task_y` in `test_x`                        |
| `buildTest` | Build tests for `task_y` in `test_x`                      |
| `test`      | Build and run tests for `task_y` in `test_x`              |
| `buildAll`  | Build all tasks in all test folders                       |
| `buildAll`  | Build and run tests for all tasks in all test folders     |

| Argument                 | Description                                     |
|--------------------------|-------------------------------------------------|
| `command`                | Command to run                                  |
| `test`                   | The test folder                                 |
| `task`                   | The task folder inside the test folder          |
| `-c` or `--clear`        | Clear cache before running                      |
| `-r` or `--release`      | Use release configuration when building         |
| `-d` or `--debug`        | Use debug configuration when building (default) |
| `-qb` or `--quiet-build` | Disable output from CMake (even if build fails) |
| `-qt` or `--quiet-test`  | Disable output from tests (even if test fails)  |
