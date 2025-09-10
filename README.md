# LearnOpenGL.com
This repo follows [learnopengl.com](https://learnopengl.com) with my own interpetation to the approaches taken.  
Each chapter is a separate folder (`01_HelloTriangle`, `02_Shaders`, …) built automatically with CMake.

## Build Instructions

```bash
# Install vcpkg and the dependencies
>git clone https://github.com/microsoft/vcpkg.git
>cd vcpkg
>bootstrap-vcpkg.bat
>vcpkg install glfw3 glad imgui[glfw-binding,opengl3-binding]

# Clone repo
>git clone https://github.com/youpg/Learnopengl.com-Tutorial.git
>cd Learnopengl.com-Tutorial

# Build 
>build.bat

# Run
>run.bat [chapterNumber]
Example use: >run.bat 1, runs 1_HelloTriangle
