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
    // opencv requires white boarders around chessboard
    cv::Mat imgCheckerboard(imgSize, CV_8UC3, cv::Scalar::all(255));

    // create chessboard using blocks
    const int OFFSET = 10;
    const int BLOCK_SIDE_LENGTH
        = (imgSize.width - (2 * OFFSET)) / boardSize.width + 1;
    const int LEEWAY = BLOCK_SIDE_LENGTH + OFFSET;

    int height = (BLOCK_SIDE_LENGTH * boardSize.height + 1) + (2 * OFFSET);
    int width = (BLOCK_SIDE_LENGTH * boardSize.width + 1) + (2 * OFFSET);

    std::cout << "--      image: pixel rows = " << imgSize.height << std::endl;
    std::cout << "--      image: pixel cols = " << imgSize.width << std::endl;
    std::cout << "-- chessboard: pixel rows = " << height << std::endl;
    std::cout << "-- chessboard: pixel cols = " << width << std::endl;
    std::cout << "--      block: pixel size = " << BLOCK_SIDE_LENGTH
              << std::endl;

    int count = 0;
    unsigned char color = 1;
    for (int y = OFFSET; y <= (height - LEEWAY); y += BLOCK_SIDE_LENGTH) {
        count++;
        std::cout << count << std::endl;
        // color = ~color;
        // for (int x = OFFSET; x <= width - OFFSET; x = x + BLOCK_SIDE_LENGTH)
        // {
        //      color = ~color;
        //     corners.emplace_back(x, y);
        //     cv::Mat blocks
        //             = imgCheckerboard(cv::Rect(x, y, BLOCK_SIDE_LENGTH,
        //             BLOCK_SIDE_LENGTH));
        //     blocks.setTo(cv::Scalar::all(color));
        // }
    }
    return imgCheckerboard;
}
