#ifndef SCENE_H
#define SCENE_H

#include <opencv2/opencv.hpp>
#include <string>

#include "kinect.h"

namespace scene {

    cv::Mat grabFrame(std::shared_ptr<Kinect>& sptr_kinect)
    {
        sptr_kinect->capture();
        sptr_kinect->depthCapture();
        sptr_kinect->pclCapture();
        sptr_kinect->imgCapture();
        sptr_kinect->c2dCapture();
        sptr_kinect->transform(RGB_TO_DEPTH);

        auto* rgbData = k4a_image_get_buffer(sptr_kinect->m_c2d);
        int w = k4a_image_get_width_pixels(sptr_kinect->m_c2d);
        int h = k4a_image_get_height_pixels(sptr_kinect->m_c2d);

        cv::Mat frame
                = cv::Mat(h, w, CV_8UC4, (void*)rgbData, cv::Mat::AUTO_STEP).clone();

        sptr_kinect->releaseK4aCapture();
        sptr_kinect->releaseK4aImages();

        return frame;
    }

void load(std::vector<cv::Mat>& scene)
{
    const std::string file_0 = "./output/scene/black.png";
    const std::string file_1 = "./output/scene/white.png";
    cv::Mat img_0 = cv::imread(file_0, cv::IMREAD_COLOR);
    cv::Mat img_1 = cv::imread(file_1, cv::IMREAD_COLOR);
    scene[0] = img_0;
    scene[1] = img_1;
}

void write(std::vector<cv::Mat> scene)
{
    const std::string file_0 = "./output/scene/black.png";
    const std::string file_1 = "./output/scene/white.png";
    cv::imwrite(file_0, scene[0]);
    cv::imwrite(file_1, scene[1]);
}

cv::Mat contrastImg(const bool& contrast, const int& w, const int& h)
{
    cv::Mat black(h, w, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat white(h, w, CV_8UC3, cv::Scalar(255, 255, 255));

    if (contrast) {
        return white;
    } else {
        return black;
    }
}

    // flicker black then white images
void flicker(std::shared_ptr<Kinect>& sptr_kinect, const std::string& window,
    const int& w, const int& h, std::vector<cv::Mat>& scene)
{
    bool contrast = false;
    cv::namedWindow(window,cv::WINDOW_NORMAL);
    cv::setWindowProperty(window, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    while (true) {
        cv::Mat img = contrastImg(contrast, w, h);
        cv::imshow(window, img);
        cv::moveWindow(window, 3000, 0);
        if (cv::waitKey(2000) >= 0) {
            break;
        }

        // capture scene
        cv::Mat frame = grabFrame(sptr_kinect);
        scene.emplace_back(frame);
        contrast = !contrast;

        if (scene.size() == 2) {
            cv::waitKey(1000);
            cv::destroyWindow(window);
            break;
        }
    }
}
}
#endif // SCENE_H
