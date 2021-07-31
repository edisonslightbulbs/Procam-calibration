#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <opencv2/opencv.hpp>

namespace chessboard {

const float PHYSICAL_BOARD_BLOCK_WIDTH = 0.02500f;
const float PROJECTED_BOARD_BLOCK_WIDTH = 0.05400f;

void findImageSpaceCorners(std::vector<cv::Mat>& images,
    std::vector<std::vector<cv::Point2f>>& imageSpaceCorners,
    bool show = false);

void findWorldSpaceCorners(const cv::Size& boardSize, float blockWidth,
    std::vector<cv::Point3f>& worldSpaceCorners);

cv::Mat create(const cv::Size& imgSize, const cv::Size& boardSize,
    std::vector<cv::Point2f>& imgSpaceCorners);
}
#endif // CHESSBOARD_H
