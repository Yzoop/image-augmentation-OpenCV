/*H**********************************************************************
* FILENAME :        image_augmentator.cpp
*
* AUTHOR :          IVAN KALINCHUK, 2020
*
*H*/

#include <windows.h>
#include <string>
#include <thread>
#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include "configurations.h"
#include <algorithm>    // std::min
#include "augmentations.h"
#include <cmath>
// 1-st is the program, the 2-nd is path to an augmentation file,
// the 3-rd contains full path to the folder with images
// the 4-th contains full path to the folder to store new images
#define NUM_AUGMENTATION_ARGS 4
// In future provide user a possibility to input a number of threads
#define NUM_THREADS (size_t)3


typedef std::vector<std::string> vec_image_pathes;

namespace fs = std::experimental::filesystem::v1;


std::vector<std::string> get_image_pathes_from(const std::string& folder_path) {
	std::vector<std::string> image_pathes;
	for (const auto& entry : fs::directory_iterator(folder_path)) {
		image_pathes.push_back(entry.path().string());
	}
	return image_pathes;
}


void thread_augment_images(const vec_image_pathes::iterator& from,
							const vec_image_pathes::iterator& to,
							const vec_funcs_t& augm_funcs,
							const std::string& direction) {
	for (auto cur_img_path = from; cur_img_path != to; cur_img_path++) {
		cv::Mat augmented_img = cv::imread(*cur_img_path);
		for (vec_funcs_t::const_iterator func = augm_funcs.begin(); func != augm_funcs.end(); func++) {
			augmented_img = (*func)(augmented_img);
		}
		std::string new_path = (fs::path(direction) / fs::path(*cur_img_path).filename()).string();
		cv::imwrite(new_path, augmented_img);
	}
}


void run_augmentations(vec_image_pathes& image_pathes, const vec_funcs_t& augm_funcs, const std::string& direction_path) {
	int num_threads_to_create = std::min(NUM_THREADS, image_pathes.size());
	int thread_step = image_pathes.size() / num_threads_to_create;
	std::vector<std::thread> augm_threads;// (num_threads_to_create);
	for (size_t thread_idx = 0; thread_idx <= num_threads_to_create; thread_idx++) {
		size_t from_idx = thread_idx * thread_step;
		size_t to_idx = std::min(image_pathes.size(), from_idx + thread_step);
		vec_image_pathes::iterator from = image_pathes.begin() + from_idx;
		vec_image_pathes::iterator to;
		if (to_idx == image_pathes.size()) {
			to = image_pathes.end();
		}
		else {
			to = image_pathes.begin() + to_idx;
		}
		augm_threads.push_back(std::thread(thread_augment_images, from, 
												to, std::ref(augm_funcs), 
												std::ref(direction_path)));
	}
	for (auto& th : augm_threads) {
		th.join();
	}
}


void show_results(const double& exec_time, const size_t& num_imgs) {
	std::cout << "Images augmentation job finished.\n";
	std::cout << "Statistics:\n" << "-------------------------------------------------\n";
	std::cout << "Number of images:\t" << num_imgs << "\n";
	std::cout << "Execution time:\t\t" << exec_time << " seconds\n";
	std::cout << "-------------------------------------------------\n";
}


int main(int argc, char* argv[]) {
	if (argc != NUM_AUGMENTATION_ARGS) {
		std::cout << "Error! Please, pass the next arguments: \n"
			<< "1. executable program name\n"
			<< "2. path to an augmentation config file\n"
			<< "3. path to the folder, which contains images to work with\n"
			<< "4. path to the folder, where augmented images will be stored.\n";
	}
	else {
		std::ifstream args_stream(argv[1]);
		if (!args_stream.is_open()) {
			std::cout << "Error! Given file '"<< argv[1] << "' doesn't exist.\n";
		}
		clock_t start_time = clock();
		vec_funcs_t functions_to_use = get_functions(args_stream);
		vec_image_pathes image_pathes = get_image_pathes_from(argv[2]);
		run_augmentations(image_pathes, functions_to_use, argv[3]);
		double execution_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
		show_results(execution_time, image_pathes.size());
	}

	return 0;
}