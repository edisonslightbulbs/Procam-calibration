#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <opencv2/opencv.hpp>

namespace chessboard {
    // measurement of square side in meters
    const float CHESSBOARD_SQUARE_DIMENSION = 0.02500f;

void findSquareCorners(std::vector<cv::Mat>& images,
    std::vector<std::vector<cv::Point2f>>& allFoundCorners,
    bool showResults = false);

void findSquareEdges(const cv::Size& boardSize, float squareEdgeLength,
    std::vector<cv::Point3f>& corners);
}
#endif //CHESSBOARD_H
