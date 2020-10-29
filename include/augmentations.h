#pragma once
/*H**********************************************************************
* FILENAME :        augmentations.h
*
* AUTHOR :          IVAN KALINCHUK, 2020
*
*H*/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <utility>




/*
    Function: set_noise_value(const float& val)
    ----------------------------
    sets up a so called 'private' value of noise

        val: a number of bound noise.
 */
void set_noise_value(const float& val);




/*
    Function: set_brightness_value(const int& val)
    ----------------------------
    sets up a so called 'private' value of brightness

        val: a number of brightness.
 */
void set_brightness_value(const int& val);




/*
    Function: set_rotation_value(const int& val)
    ----------------------------
    sets up a so called 'private' value of rotation

        val: a number of bound rotation.
 */
void set_rotation_value(const int& val);




/*
    Function: set_resize_value(const cv::Size& val)
    ----------------------------
    sets up a so called 'private' value of new image size

        val: a cv2 lib Size structucture, which contains width and height values
 */
void set_resize_value(const cv::Size& val);




/*
    Function: get_random_rotated(const cv::Mat& image)
    ----------------------------
    rotates given image and saves it to another cv::Mat value

        image: an image, which should be rotated.

    Returns: a randomly rotated image (by a previosly set up rotation value)
 */
cv::Mat get_random_rotated(const cv::Mat& image);




/*
    Function: get_brighted(const cv::Mat& image)
    ----------------------------
    makes brighter (or darker according to bright value)
    given image and saves it to another cv::Mat value

        image: an image, which should be brighted.

    Returns: a brighted image (by a previosly set up brightness value)
 */
cv::Mat get_brighted(const cv::Mat& image);




/*
    Function: get_resized(const cv::Mat& image)
    ----------------------------
    resizes given image and saves it to another cv::Mat value

        image: an image, which should be resized.

    Returns: a resized image (to a previosly set up size value)
 */
cv::Mat get_resized(const cv::Mat& image);




/*
    Function: get_grayscaled(const cv::Mat& image)
    ----------------------------
    converts an rgb given image to another cv::Mat grayscaled iamge

        image: an image, which should be converted to grayscale.

    Returns: a grayscaled image
 */
cv::Mat get_grayscaled(const cv::Mat& image);




/*
    Function: get_noised(const cv::Mat& image)
    ----------------------------
    randomly adds pixels to given image and saves it to another cv::Mat value

        image: an image, which should be noised.

    Returns: a noised image (by a previosly set ip noise value)
 */
cv::Mat get_noised(const cv::Mat& image);