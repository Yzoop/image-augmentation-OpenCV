/*H**********************************************************************
* FILENAME :        configurations.h
*
* AUTHOR :          IVAN KALINCHUK, 2020
*
*H*/

#pragma once
#include <string>
#include <opencv2/opencv.hpp>
#include <fstream>
#include<map>
#include <utility>
#include<vector>


typedef std::function<cv::Mat(const cv::Mat&)> func_t;
typedef std::vector<func_t> vec_funcs_t;
typedef std::map<std::string, std::string> map_arg_data;



/*
    Function: get_functions(std::ifstream& args_stream)
    ----------------------------
    reads configurations from stream. Configuration should match features.txt format.

        image: an image, which should be converted to grayscale.

    Returns: a grayscaled image
 */
vec_funcs_t get_functions(std::ifstream& args_stream);