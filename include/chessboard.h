#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <opencv2/opencv.hpp>

namespace chessboard {

const float R_BLOCK_WIDTH = 0.02500f;
const float P_BLOCK_WIDTH = 0.06050f;

cv::Mat create(const cv::Size& imgSize, const cv::Size& boardSize,
    std::vector<cv::Point2f>& imgSpaceCorners);

void capture(
    const bool& pass, cv::Mat& src, std::vector<cv::Mat>& chessboardImages);

bool overlay(const cv::Mat& src, cv::Mat dst, const cv::Size& dChessboard,
    const std::string& window);
}

#endif // CHESSBOARD_H
