add_library(vision STATIC src/vision.cpp)

target_include_directories(vision
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(vision
    PUBLIC ${OpenCV_LIBS}
)
