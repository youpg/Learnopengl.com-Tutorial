cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)

# vcpkg / system dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# --- ImGui local sources (core + backends) ---
set(IMGUI_SRC
    deps/imgui/imgui.cpp
    deps/imgui/imgui_draw.cpp
    deps/imgui/imgui_tables.cpp
    deps/imgui/imgui_widgets.cpp
)

set(IMGUI_BACKENDS
    deps/imgui/backends/imgui_impl_glfw.cpp
    deps/imgui/backends/imgui_impl_opengl3.cpp
)

include_directories(
    deps/imgui
    deps/imgui/backends
)

# --- Copy deps/ to the build root (next to the .sln) ---
set(DEP_SRC_DIR "${CMAKE_SOURCE_DIR}/deps")
set(DEP_DST_DIR "${CMAKE_BINARY_DIR}/deps")

if(EXISTS "${DEP_SRC_DIR}")
    add_custom_target(copy_deps ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Copying runtime deps to ${DEP_DST_DIR}"
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${DEP_DST_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${DEP_SRC_DIR}" "${DEP_DST_DIR}"
        COMMENT "Copying deps/ to build folder"
    )
else()
    message(WARNING "deps/ folder not found at: ${DEP_SRC_DIR}. Add it to the repo or adjust DEP_SRC_DIR.")
endif()

# Macro to build a chapter
function(add_chapter name folder)
    file(GLOB CHAPTER_SOURCES "${folder}/*.cpp" "${folder}/*.c")

    add_executable(${name} ${CHAPTER_SOURCES} ${IMGUI_SRC} ${IMGUI_BACKENDS})
    target_include_directories(${name} PRIVATE ${folder} deps/imgui deps/imgui/backends)
    target_link_libraries(${name} PRIVATE glfw glad::glad OpenGL::GL)

    if(TARGET copy_deps)
        add_dependencies(${name} copy_deps)
    endif()

    set_target_properties(${name} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
endfunction()

# === Auto-discover chapters ===
file(GLOB children RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/*)
foreach(child ${children})
    if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${child}")
        if(child MATCHES "^[0-9][0-9]_.*")
            message(STATUS "Adding chapter: ${child}")
            add_chapter(${child} ${child})
        endif()
    endif()
endforeach()
