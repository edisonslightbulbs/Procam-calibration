#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <opencv2/opencv.hpp>

namespace chessboard {
const float PHYSICAL_BOARD_BLOCK_LENGTH = 0.02500f;
const float PROJECTED_BOARD_BLOCK_LENGTH = 0.05400f;

void findImageSpaceCorners(std::vector<cv::Mat>& images,
    std::vector<std::vector<cv::Point2f>>& allFoundCorners,
    bool showResults = false);

void findWorldSpaceCorners(const cv::Size& boardSize, float squareEdgeLength,
    std::vector<cv::Point3f>& corners);

cv::Mat generate(const cv::Size& imgSize, const cv::Size& boardSize,
    std::vector<cv::Point2f>& corners);
}
#endif // CHESSBOARD_H
