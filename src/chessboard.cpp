#include "chessboard.h"

cv::Mat chessboard::create(const cv::Size& imgSize, const cv::Size& boardSize,
    std::vector<cv::Point2f>& imgSpaceCorners)
{
    // todo: assert aspect ration of image size
    //       using an invalid aspect ration causes and exception

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

// now I want to capture t_data data
void chessboard::capture(
    const bool& pass, t_RGBD& data, std::vector<t_RGBD>& dataCollection)
{
    if (pass) {
        dataCollection.emplace_back(data);
        int imgCount = (int)dataCollection.size();
        std::cout << "-- # of RGBD images: " << imgCount << std::endl;
    }
}

void chessboard::capture(
    const bool& pass, cv::Mat& src, std::vector<cv::Mat>& chessboardImages)
{
    if (pass) {
        // todo: does the cloning here serve a purpose?
        //   or is it mere redundant?
        cv::Mat dst;
        src.copyTo(dst);
        chessboardImages.emplace_back(dst);
        int imgCount = (int)chessboardImages.size();
        std::cout << "-- # of RGB images: " << imgCount << std::endl;
    }
}

bool chessboard::overlay(const cv::Mat& src, cv::Mat dst,
    const cv::Size& dChessboard, const std::string& window)
{
    std::vector<cv::Point2f> chessboardCorners;
    bool found = cv::findChessboardCorners(src, dChessboard, chessboardCorners,
        cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);
    if (found) {
        src.copyTo(dst);
        cv::drawChessboardCorners(dst, dChessboard, chessboardCorners, found);
        cv::imshow(window, dst);
    } else {
        cv::imshow(window, src);
    }
    return found;
}
