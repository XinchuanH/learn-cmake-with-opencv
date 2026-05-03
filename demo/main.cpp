#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat image = cv::imread("test.jpg");
    if (image.empty()) {
        std::cerr << "no image\n";
        return 1;
    }
    cv::imshow("img", image);
    cv::waitKey(0);
    return 0;
}
