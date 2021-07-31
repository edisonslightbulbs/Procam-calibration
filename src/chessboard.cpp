#include "chessboard.h"

cv::Mat chessboard::create(const cv::Size& imgSize, const cv::Size& boardSize,
    std::vector<cv::Point2f>& imgSpaceCorners)
{
    int offset = 50;
    unsigned char color = 255;
    cv::Mat board(imgSize, CV_8UC3, cv::Scalar::all(255));
    int blockWidth
        = floor((imgSize.height - 2 * offset) / (boardSize.height + 1));
    int maxWidth = (blockWidth * (boardSize.width + 1)) + (2 * offset);

    std::cout << "--      image height: " << imgSize.height << std::endl;
    std::cout << "--      image  width: " << imgSize.width << std::endl;
    std::cout << "-- chessboard height: " << boardSize.height << std::endl;
    std::cout << "--  chessboard width: " << boardSize.width << std::endl;

    for (int y = offset; y < imgSize.height - offset; y = y + blockWidth) {
        if (y + blockWidth > imgSize.height - offset) {
            break;
        }
        for (int x = offset; x < imgSize.width - offset; x = x + blockWidth) {
            color = ~color;
            if (x + blockWidth > maxWidth) {
                break;
            }
            // collect image space points
            if (x > offset && y > offset) {
                imgSpaceCorners.emplace_back(x, y);
            }
            cv::Mat block = board(cv::Rect(x, y, blockWidth, blockWidth));
            block.setTo(cv::Scalar::all(color));
        }
    }
    return board;
}

void chessboard::findImageSpaceCorners(std::vector<cv::Mat>& images,
    std::vector<std::vector<cv::Point2f>>& imageSpaceCorners, bool show)
{
    for (auto& image : images) {
        std::vector<cv::Point2f> corner;
        bool found = cv::findChessboardCorners(image, cv::Size(9, 6), corner,
            cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);

        if (found) {
            imageSpaceCorners.emplace_back(corner);
        }

        if (show) {
            cv::drawChessboardCorners(image, cv::Size(9, 6), corner, found);
            cv::imshow("CALIBRATION CORNERS", image);
            cv::waitKey(0);
        }
    }
}

void chessboard::findWorldSpaceCorners(const cv::Size& boardSize,
    float blockWidth, std::vector<cv::Point3f>& worldSpaceCorners)
{
    for (int i = 0; i < boardSize.height; i++) {
        for (int j = 0; j < boardSize.width; j++) {
            worldSpaceCorners.emplace_back(cv::Point3f(
                (float)j * blockWidth, (float)i * blockWidth, 0.0f));
        }
    }
}
