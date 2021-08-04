#include <opencv2/opencv.hpp>

#include "camera.h"

    void Camera::findWorldSpaceCorners(const cv::Size& boardSize, float blockWidth)
    {
        for (int i = 0; i < boardSize.height; i++) {
            for (int j = 0; j < boardSize.width; j++) {
                m_worldSpaceCorners[0].emplace_back(cv::Point3f(
                        (float)j * blockWidth, (float)i * blockWidth, 0.0f));
            }
        }
    }

    void Camera::findCameraSpaceCorners()
    {
        for (auto& image : m_images) {
            std::vector<cv::Point2f> corner;
            bool found = cv::findChessboardCorners(image, cv::Size(9, 6),
                                                   corner,
                                                   cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);
            if (found) {
                m_cameraSpaceCorners.emplace_back(corner);
            }
        }
    }

    void Camera::calibrate(const cv::Size& boardSize, float blockWidth)
    {
        findCameraSpaceCorners();
        findWorldSpaceCorners(boardSize, blockWidth);
        m_worldSpaceCorners.resize(m_cameraSpaceCorners.size(), m_worldSpaceCorners[0]);
        cv::calibrateCamera(m_worldSpaceCorners, m_cameraSpaceCorners, boardSize,
                            m_matrix, m_K, m_R, m_t);
    }

    Camera::Camera()
    {
        m_K = cv::Mat::zeros(8, 1, CV_64F);
        m_matrix = cv::Mat::eye(3, 3, CV_64F);
        m_worldSpaceCorners = std::vector<std::vector<cv::Point3f>>(1);
    }
