#include <iostream>
#include <opencv2/opencv.hpp>
#include "vision.hpp"

int main() {
    cv::Mat image = cv::imread("test.jpg");
    if (image.empty()) {
        std::cerr << "no image\n";
        return 1;
    }
    cv::Mat gray = toGray(image);
    cv::imshow("gray", gray);
    cv::waitKey(0);
    return 0;
}
