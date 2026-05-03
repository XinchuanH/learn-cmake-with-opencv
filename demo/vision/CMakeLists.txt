add_library(vision STATIC src/vision.cpp)

# Visibility recap:
#   PUBLIC    -> I use it,  downstream uses it too
#   PRIVATE   -> I use it,  downstream does NOT
#   INTERFACE -> I do NOT use it, but downstream does

target_include_directories(vision
    # PUBLIC: vision.cpp includes "vision/vision.hpp" (I use it),
    #         and main.cpp also includes "vision/vision.hpp" (downstream uses it).
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include

    # PRIVATE: src/ holds internal headers (e.g. internal_log.hpp).
    #          Only files inside this library can find them; downstream cannot.
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(vision
    # PUBLIC because vision.hpp exposes cv::Mat in its API,
    # so anyone including it must also link against OpenCV.
    PUBLIC ${OpenCV_LIBS}
)
