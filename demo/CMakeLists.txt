cmake_minimum_required(VERSION 3.15)
project(demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_subdirectory(vision)

add_executable(demo app/main.cpp)
target_link_libraries(demo PRIVATE vision)
