cmake_minimum_required(VERSION 3.15)
project(demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

# Put .exe and .dll/.so in the same folder so the dynamic loader finds vision at runtime.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(vision)

add_executable(demo app/main.cpp)
target_link_libraries(demo PRIVATE vision)
