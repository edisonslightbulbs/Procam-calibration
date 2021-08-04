#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <opencv2/opencv.hpp>

namespace chessboard {

const float R_BLOCK_WIDTH = 0.02500f;
const float P_BLOCK_WIDTH = 0.06050f;

void findImageSpaceCorners(std::vector<cv::Mat>& images,
    std::vector<std::vector<cv::Point2f>>& corners, bool show = false);

void findWorldSpaceCorners(const cv::Size& boardSize, float blockWidth,
    std::vector<cv::Point3f>& worldSpaceCorners);

cv::Mat create(const cv::Size& imgSize, const cv::Size& boardSize,
    std::vector<cv::Point2f>& imgSpaceCorners);
}
#endif // CHESSBOARD_H
