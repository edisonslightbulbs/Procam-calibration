#include "chessboard.h"

void chessboard::findImageSpaceCorners(std::vector<cv::Mat>& images,
    std::vector<std::vector<cv::Point2f>>& allFoundCorners, bool showResults)
{
    for (auto& image : images) {
        std::vector<cv::Point2f> pointBuf;
        bool found = cv::findChessboardCorners(image, cv::Size(9, 6), pointBuf,
            cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);

        if (found) {
            allFoundCorners.emplace_back(pointBuf);
        }

        if (showResults) {
            cv::drawChessboardCorners(image, cv::Size(9, 6), pointBuf, found);
            cv::imshow("Looking for Corners", image);
            cv::waitKey(0);
        }
    }
}

void chessboard::findWorldSpaceCorners(const cv::Size& boardSize,
    float squareEdgeLength, std::vector<cv::Point3f>& corners)
{
    for (int i = 0; i < boardSize.height; i++) {
        for (int j = 0; j < boardSize.width; j++) {
            corners.emplace_back(cv::Point3f((float)j * squareEdgeLength,
                (float)i * squareEdgeLength, 0.0f));
        }
    }
}

cv::Mat chessboard::generate(const cv::Size& imgSize, const cv::Size& boardSize,
    std::vector<cv::Point2f>& corners)
{
    // todo bug: chessboard dimensions are onto honoured
    int offset
        = 50; // opencv requires white boarders around checkerboard pattern

    // checkerboard image
    cv::Mat imgCheckerboard(imgSize, CV_8UC3, cv::Scalar::all(255));

    // block size
    int squareWidth = floor((imgSize.width - 2 * offset) / boardSize.width);
    int squareHeight = floor((imgSize.height - 2 * offset) / boardSize.height);

    // block color
    unsigned char color = 1;

    //! The order must be consistent with OpenCV order:
    // row first then column, each row sweep from left to right
    for (int y = offset; y < imgSize.height - offset; y = y + squareHeight) {
        color = ~color; // bitwise complement
        if (y + squareHeight > imgSize.height - offset) {
            break;
        }
        for (int x = offset; x < imgSize.width - offset; x = x + squareWidth) {
            color = ~color;
            if (x + squareWidth > imgSize.width - offset) {
                break;
            }
            // save checkerboard points
            if (x > offset && y > offset) {
                corners.emplace_back(x, y);
            }
            // color the block
            cv::Mat block
                = imgCheckerboard(cv::Rect(x, y, squareWidth, squareHeight));
            block.setTo(cv::Scalar::all(color));
        }
    }
    return imgCheckerboard;
}
