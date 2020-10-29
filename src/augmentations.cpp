/*H**********************************************************************
* FILENAME :        augmentations.cpp
*
* AUTHOR :          IVAN KALINCHUK, 2020
*
*H*/

#include "augmentations.h"
#include <time.h>


float noise_value;
int rotation_value, brightness_value;
cv::Size resize_value;


void set_noise_value(const float& val) {
    noise_value = val;
}


void set_brightness_value(const int& val) {
    brightness_value = val;
}


void set_rotation_value(const int& val) {
    srand(time(0));
    rotation_value = val;
}


void set_resize_value(const cv::Size& val) {
    resize_value = val;
}

cv::Mat get_random_rotated(const cv::Mat& image)
{
    cv::Mat random_rotated;
    int random_rotation_deg = rand() % rotation_value;
    cv::Mat rotation = getRotationMatrix2D(cv::Point2f(image.cols / 2, image.rows / 2), random_rotation_deg, 1);
    warpAffine(image, random_rotated, rotation, image.size());
    return random_rotated;
}

cv::Mat get_brighted(const cv::Mat& image)
{
    cv::Mat brighted_img = image.clone();
    brighted_img += brightness_value;
    return brighted_img;
}


cv::Mat get_resized(const cv::Mat& image) {
    cv::Mat resized_img;
    cv::resize(image, resized_img, resize_value, 0, 0, CV_INTER_LINEAR);
    return resized_img;
}


cv::Mat get_grayscaled(const cv::Mat& image) {
    cv::Mat grayscaled_img;
    cv::cvtColor(image, grayscaled_img, cv::COLOR_BGR2GRAY);
    return grayscaled_img;
}


cv::Mat get_noised(const cv::Mat& image) {
    cv::Mat noised_img = image.clone();
    cv::Mat noise_pixels(image.size(), image.type());
    cv::randn(noise_pixels, 0, cv::InputArray(256 * noise_value));
    noised_img += noise_pixels;
    return noised_img;
}
