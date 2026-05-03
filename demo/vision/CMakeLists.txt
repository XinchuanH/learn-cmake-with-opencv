# SHARED: build vision as a dynamic library
#   Windows -> vision.dll  (+ vision.lib import library)
#   Linux   -> libvision.so
#
# Trade-off vs STATIC:
#   - Smaller executable, can be replaced without relinking demo.
#   - BUT the .dll/.so must be findable at *runtime*, not just at build time.
#     On Windows, place vision.dll next to demo.exe, or have it on PATH.
#     On Linux, set LD_LIBRARY_PATH or bake an RPATH.
#   - Typical symptom: "compiles fine, crashes on launch" -> dynamic loader
#     can't find the .dll/.so.
#
# Switch back to STATIC by replacing SHARED with STATIC below.
add_library(vision SHARED src/vision.cpp)

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

# Modern CMake: declare the C++ standard per target, not globally.
# PUBLIC because vision.hpp may use C++17 features in its API,
# so any downstream that includes it must also compile as C++17 (or later).
target_compile_features(vision PUBLIC cxx_std_17)
