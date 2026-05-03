cmake_minimum_required(VERSION 3.15)
project(demo LANGUAGES CXX)

# Emit build/compile_commands.json so clangd / IDE tooling knows
# how every file is compiled (include paths, defines, flags, standard, ...).
# Only the Makefile and Ninja generators honor this; with MSVC generators,
# pass `-G Ninja` when configuring.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Modern CMake: do NOT set the C++ standard globally with
#   set(CMAKE_CXX_STANDARD 17)
#   set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Instead, declare it per target with target_compile_features (see vision/CMakeLists.txt).
# Why: globals leak to every target in the build, including third-party
# add_subdirectory()'d code that may want a different standard.

find_package(OpenCV REQUIRED)

# Put .exe and .dll/.so in the same folder so the dynamic loader finds vision at runtime.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(vision)

add_executable(demo app/main.cpp)
target_link_libraries(demo PRIVATE vision)
# demo inherits cxx_std_17 from vision (PUBLIC feature), no need to repeat it here.
