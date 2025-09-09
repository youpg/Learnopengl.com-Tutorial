# LearnOpenGL.com
This repo follows [learnopengl.com](https://learnopengl.com) with my own interpetation to the approaches taken.  
Each chapter is a separate folder (`01_HelloTriangle`, `02_Shaders`, …) built automatically with CMake.

## Build Instructions

```bash
# Install vcpkg and the dependencies
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg install glfw3 glad

# Clone repo
git clone https://github.com/youpg/Learnopengl.com-Tutorial.git
cd Learnopengl.com-Tutorial

# Configure with vcpkg
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build build
