cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)

# vcpkg dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Macro to build a chapter
function(add_chapter name folder)
    file(GLOB CHAPTER_SOURCES "${folder}/*.cpp" "${folder}/*.c")

    add_executable(${name} ${CHAPTER_SOURCES})
    target_include_directories(${name} PRIVATE ${folder})
    target_link_libraries(${name} PRIVATE glfw glad::glad OpenGL::GL imgui::imgui)

    # Copy only fonts and shaders for this specific chapter
    set(DEP_SRC_DIR "${CMAKE_SOURCE_DIR}/${folder}/deps")
    set(DEP_DST_DIR "${CMAKE_BINARY_DIR}/bin/${folder}/deps")
    
    if(EXISTS "${DEP_SRC_DIR}")
        add_custom_command(TARGET ${name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Copying runtime deps to ${DEP_DST_DIR}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${DEP_DST_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${DEP_SRC_DIR}" "${DEP_DST_DIR}"
            COMMENT "Copying deps/ to build folder for ${name}"
        )
    else()
        message(WARNING "deps/ folder not found at: ${DEP_SRC_DIR}")
    endif()

    # Set output directory to a clean structure
    set_target_properties(${name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${folder}"
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${folder}"
    )
endfunction()

# Create output directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# === Auto-discover chapters ===
file(GLOB children RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/*)
foreach(child ${children})
    if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${child}")
        # Match both single-digit and double-digit chapter numbers
        if(child MATCHES "^[0-9]+_.*")
            message(STATUS "Adding chapter: ${child}")
            add_chapter(${child} ${child})
        endif()
    endif()
endforeach()
