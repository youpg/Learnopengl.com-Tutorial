@echo off
setlocal enabledelayedexpansion

REM Check if chapter number was provided
if "%~1"=="" (
    echo Usage: run.bat [chapter_number] [rebuild]
    echo Example: run.bat 1
    echo Example: run.bat 1 rebuild
    exit /b 1
)

set CHAPTER_NUM=%~1
set REBUILD=%~2

REM Find the chapter directory with flexible numbering
set CHAPTER_DIR=
for /d %%d in (*_*) do (
    rem Extract the number part from the directory name
    for /f "tokens=1 delims=_" %%n in ("%%d") do (
        rem Remove leading zeros and compare
        set /a "NUM=%%n"
        if "!NUM!" equ "!CHAPTER_NUM!" (
            set CHAPTER_DIR=%%d
            goto found_chapter
        )
    )
)

:found_chapter
if "!CHAPTER_DIR!"=="" (
    echo Chapter !CHAPTER_NUM! not found.
    echo Available chapters:
    for /d %%d in (*_*) do (
        if "%%d" neq "deps" echo   %%d
    )
    exit /b 1
)

REM Check if we need to rebuild
set EXE_PATH=build\bin\!CHAPTER_DIR!\Debug\!CHAPTER_DIR!.exe
if "!REBUILD!"=="rebuild" (
    echo Rebuilding !CHAPTER_DIR!...
    goto build_chapter
)

REM Always build to ensure changes are captured
echo Building !CHAPTER_DIR! (incremental)...
goto build_chapter

:build_chapter
REM Build only the specific chapter
if not defined VCPKG_ROOT (
    echo VCPKG_ROOT environment variable is not set.
    echo Please set it to your vcpkg installation directory, for example:
    echo setx VCPKG_ROOT "C:\dev\apps\vcpkg"
    exit /b 1
)

if not exist "%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" (
    echo vcpkg.cmake not found at: %VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake
    echo Please check your VCPKG_ROOT environment variable
    exit /b 1
)

REM Configure if build directory doesn't exist
if not exist "build" (
    echo Configuring CMake...
    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake"
    if !errorlevel! neq 0 (
        echo CMake configuration failed
        exit /b 1
    )
)

REM Check if project file exists, if not, reconfigure
if not exist "build\!CHAPTER_DIR!.vcxproj" (
    echo Project file for !CHAPTER_DIR! not found, reconfiguring...
    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake"
    if !errorlevel! neq 0 (
        echo CMake configuration failed
        exit /b 1
    )
)

REM Build only the specific chapter
echo Building chapter !CHAPTER_DIR!...
cmake --build build --target !CHAPTER_DIR! --config Debug

REM Check if build was successful
if !errorlevel! neq 0 (
    echo Build failed for !CHAPTER_DIR!
    exit /b 1
)

if not exist "!EXE_PATH!" (
    echo Executable not found after build: !EXE_PATH!
    exit /b 1
)

:run_chapter
REM Change to the chapter's build directory where dependencies are located
set CHAPTER_BUILD_DIR=build\bin\!CHAPTER_DIR!
cd /d "!CHAPTER_BUILD_DIR!"

REM Run the executable
echo Running !CHAPTER_DIR!...
.\Debug\!CHAPTER_DIR!.exe

REM Return to original directory
cd /d %~dp0

endlocal