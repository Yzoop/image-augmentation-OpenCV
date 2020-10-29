/*H**********************************************************************
* FILENAME :        configurations.cpp
*
* AUTHOR :          IVAN KALINCHUK, 2020
*
*H*/

#include <algorithm>
#include "configurations.h"
#include "augmentations.h"

#define LINE_NOT_FOUND -1
#define POINTER_PUT_SUCCESS 1

const std::string CODE_START_LINE = "_COMMANDS_START",
CODE_FINISH_LINE = "_COMMANDS_FINISH",
CODE_COMMAND_SPLITTER = " ",
CODE_PAIR_SPLITTER = ",",
COMMAND_RESIZE = "RESIZE",
COMMAND_GRAYSCALE = "GRAY_SCALE",
COMMAND_NOISE = "NOISE",
COMMAND_BRIGHTNESS = "BRIGHTNESS",
COMMAND_ROTATION = "ROTATION";



std::pair<std::string, std::string> get_current_command_value(std::string line) {
    int first_space_idx = line.find(CODE_COMMAND_SPLITTER);
    const std::string command = line.substr(0, first_space_idx);
    const std::string value = line.substr(first_space_idx + 1);
    return std::make_pair(command, value);
}


int put_ifstream_to_line(std::ifstream& args_stream, const std::string& target_line=CODE_START_LINE) {
    std::string line;
    vec_funcs_t vec_func_data;
    bool target_line_found = false;
    while (std::getline(args_stream, line) && !target_line_found) {
        target_line_found = target_line == CODE_START_LINE;
    }
    if (target_line_found)
    {
        return POINTER_PUT_SUCCESS;
    }
    else {
        return LINE_NOT_FOUND;
    }
}


void save_commands_from_stream(std::ifstream& commands_stream, map_arg_data& save_map) {
    std::string line;
    while (std::getline(commands_stream, line) && line != CODE_FINISH_LINE) {
        std::pair<std::string, std::string> command_value = get_current_command_value(line);
        save_map[command_value.first] = command_value.second;
    }
}


cv::Size get_img_size_from_str(const std::string& str_img_size) {
    int split_idx = str_img_size.find(CODE_COMMAND_SPLITTER);
    const size_t width = std::stoi(str_img_size.substr(0, split_idx));
    const size_t height = std::stoi(str_img_size.substr(split_idx + 1));
    return cv::Size(width, height);
}


void save_augfunctions_with_data(const map_arg_data& func_data, vec_funcs_t& save_vec) {
    for (map_arg_data::const_iterator cur_arg = func_data.begin(); cur_arg != func_data.end(); cur_arg++) {
        if (cur_arg->first == COMMAND_RESIZE) {
            cv::Size config_img_size = get_img_size_from_str(cur_arg->second);   
            set_resize_value(config_img_size);
            save_vec.push_back(get_resized);
        }
        else if (cur_arg->first == COMMAND_NOISE) {
            float noise = std::stof(cur_arg->second);
            set_noise_value(noise);
            save_vec.push_back(get_noised);
        }
        else if (cur_arg->first == COMMAND_GRAYSCALE) {
            bool grayscale = std::stoi(cur_arg->second);
            save_vec.push_back(get_grayscaled);
        }
        else if (cur_arg->first == COMMAND_ROTATION) {
            int rotation = std::stoi(cur_arg->second);
            set_rotation_value(rotation);
            save_vec.push_back(get_random_rotated);
        }
        else if (cur_arg->first == COMMAND_BRIGHTNESS) {
            int brightness = std::stoi(cur_arg->second);
            set_brightness_value(brightness);
            save_vec.push_back(get_brighted);
        }
    }
}


vec_funcs_t get_functions(std::ifstream& args_stream) {
    vec_funcs_t vec_func_data;
    bool end_line_faced = false;
    if (put_ifstream_to_line(args_stream) == POINTER_PUT_SUCCESS) {
        std::string line;
        map_arg_data arguments_data;
        save_commands_from_stream(args_stream, arguments_data);
        save_augfunctions_with_data(arguments_data, vec_func_data);
        return vec_func_data;
    }
}
