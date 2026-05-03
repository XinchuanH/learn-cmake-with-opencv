#include "vision/vision.hpp"
#include "internal_log.hpp"  // PRIVATE header: only this module can include it

cv::Mat toGray(const cv::Mat& image) {
    vision_internal::log("toGray called");
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    return gray;
}
