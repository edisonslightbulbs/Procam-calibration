#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "pcloud.h"
#include <opencv2/opencv.hpp>

using t_RGBD = std::pair<cv::Mat, std::vector<t_rgbd>>;

namespace chessboard {

const float R_BLOCK_WIDTH = 0.02500f;
const float P_BLOCK_WIDTH = 0.06050f;

cv::Mat create(const cv::Size& imgSize, const cv::Size& boardSize,
    std::vector<cv::Point2f>& imgSpaceCorners);

void capture(
    const bool& pass, cv::Mat& src, std::vector<cv::Mat>& chessboardImages);

bool overlay(const cv::Mat& src, cv::Mat dst, const cv::Size& dChessboard,
    const std::string& window);

void capture(const bool& pass, std::pair<cv::Mat, std::vector<t_rgbd>>& data,
    std::vector<t_RGBD>& dataCollection);

void project(const cv::Size& dChessboard);
}

#endif // CHESSBOARD_H
