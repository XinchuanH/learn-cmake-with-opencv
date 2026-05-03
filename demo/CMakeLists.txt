cmake_minimum_required(VERSION 3.15)
project(demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(demo main.cpp vision.cpp)
target_link_libraries(demo PRIVATE ${OpenCV_LIBS})
