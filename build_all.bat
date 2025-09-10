@echo off
if "%VCPKG_ROOT%"=="" (
    echo VCPKG_ROOT environment variable is not set.
    echo Please set it to your vcpkg installation directory, for example:
    echo setx VCPKG_ROOT "/path/to/vcpkg/"
    pause
    exit /b 1
)

if not exist "%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" (
    echo vcpkg.cmake not found at: %VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake
    echo Please check your VCPKG_ROOT environment variable
    pause
    exit /b 1
)

echo Building with vcpkg toolchain...
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake"
cmake --build build