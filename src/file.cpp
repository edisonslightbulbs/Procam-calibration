#include <chrono>
#include <fstream>
#include <thread>

#include "file.h"

bool parameters::write(
    const std::string& name, cv::Mat cameraMatrix, cv::Mat distanceCoefficients)
{
    std::ofstream outStream(name);
    if (outStream) {
        uint16_t rows = cameraMatrix.rows;
        uint16_t columns = cameraMatrix.cols;
        outStream << rows << std::endl;
        outStream << columns << std::endl;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                double value = cameraMatrix.at<double>(r, c);
                outStream << value << std::endl;
            }
        }

        rows = distanceCoefficients.rows;
        columns = distanceCoefficients.cols;
        outStream << rows << std::endl;
        outStream << columns << std::endl;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                double value = distanceCoefficients.at<double>(r, c);
                outStream << value << std::endl;
            }
        }

        // write and wait for operation to complete
        outStream.close();
        std::this_thread::sleep_for(std::chrono::seconds(6));
        return true;
    }
    return false;
}

bool parameters::read(const std::string& name, cv::Mat& cameraMatrix,
    cv::Mat& distanceCoefficients)
{
    std::ifstream inStream(name);
    if (inStream) {
        uint16_t rows;
        uint16_t columns;
        inStream >> rows;
        inStream >> columns;
        cameraMatrix = cv::Mat(cv::Size(columns, rows), CV_64F);
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                double read = 0.0f;
                inStream >> read;
                cameraMatrix.at<double>(r, c) = read;
                std::cout << cameraMatrix.at<double>(r, c) << "\n";
            }
        }

        inStream >> rows;
        inStream >> columns;
        distanceCoefficients = cv::Mat(cv::Size(columns, rows), CV_64F);
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                double read = 0.0f;
                inStream >> read;
                distanceCoefficients.at<double>(r, c) = read;
                std::cout << cameraMatrix.at<double>(r, c) << "\n";
            }
        }
        inStream.close();
        return true;
    }
    return false;
}
