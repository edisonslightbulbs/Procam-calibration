#ifndef PARAMETERS
#define PARAMETERS

#include <string>
#include <opencv2/opencv.hpp>

namespace parameters {
    bool write(
            const std::string& name, cv::Mat cameraMatrix, cv::Mat distanceCoefficients);

    bool read(const std::string& name, cv::Mat& cameraMatrix,
              cv::Mat& distanceCoefficients);
}
#endif //PARAMETERS
