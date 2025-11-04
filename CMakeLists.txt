cmake_minimum_required(VERSION 3.20)
project(intro-to-graphics-SDL3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0135 NEW)

# exe path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# static lib path
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/intermediate)

# Compiled path
set(CMAKE_OBJECT_PATH_MAX 100)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SDL3
set(SDL3_VERSION 3.2.26)
find_package(SDL3 ${SDL3_VERSION} QUIET) # QUIET or REQUIRED
if (NOT SDL3_FOUND) # If there's none, fetch and build SDL3
    include(FetchContent)
    if (UNIX)
        FetchContent_Declare(
            SDL3
            URL https://github.com/libsdl-org/SDL/releases/download/release-${SDL3_VERSION}/SDL3-${SDL3_VERSION}.tar.gz
        )
        FetchContent_MakeAvailable(SDL3)
    elseif (WIN32)
        FetchContent_Declare(
            SDL3
            URL https://github.com/libsdl-org/SDL/releases/download/release-${SDL3_VERSION}/SDL3-${SDL3_VERSION}.zip
        )
        FetchContent_MakeAvailable(SDL3)
    endif()
endif()

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} "src/Engine/Window.h" "src/Engine/Window.cpp" "src/Engine/Time.h" "src/Engine/Time.cpp" "src/Engine/Input/InputState.h" "src/Engine/Scene/Scene.h"  "src/Engine/Scene/Child/Scene01Clear.h" "src/Engine/Scene/Child/Scene01Clear.cpp" "src/Engine/Renderer/Renderer.h" "src/Engine/Renderer/Renderer.cpp" "src/Engine/Scene/Child/Scene02Triangle.h" "src/Engine/Scene/Child/Scene02Triangle.cpp" "src/Engine/Scene/Child/Scene03VertexBuffer.h" "src/Engine/Scene/Child/Scene03VertexBuffer.cpp" "src/Engine/Renderer/PositionColorVertex.h")

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} SDL3::SDL3)

# Copy sdl3.dll in the build folder
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:SDL3::SDL3>"
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
# Copy content file in build folder
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/content"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/content"
)