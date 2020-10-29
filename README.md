# image augmentation OpenCV

A console projects for image augmentation, using OpenCV library and multithreading for speeding up.

## Features which this project can deal with:
1. Resizing images
2. Images to graysacle
3. Noising images
4. Rotating images
5. Changing images' brightness

Some examples of image changing (resize to 256x256 pixels, noise 0.3, to grayscale):
![compare image](https://github.com/Yzoop/image-augmentation-OpenCV/blob/main/proj_description/compare_before_after.png)

## Installing
So as to use the program, you need to install OpenCV and add dependencies to that library according to the rules of your development environment. Also, an already compiled and built solution can be downloaded from releases **image_augmentator.zip**).

## Using
Having downloaded and unzipped the release or built from source, you see a binary file `ImageAugmentation_с.exe` and an `augmentation_arguments.txt` file. `augmentation_arguments.txt` - is a file, which contains configuration data for the program. Read more in `features.txt`. So as to run the program, you have to first run a cmd.exe in the folder with the executable file. Then pass the next arguments:
`ImageAugmentation_с.exe augmentation_arguments.txt image_source_path\folder image_destination_path\some_folder` where:
* `ImageAugmentation_с.exe` - is a binary file application name
* `augmentation_arguments.txt` - path to a file with configuration for augmenting
* `image_source_path\folder` - full path to images to be augmented
* `image_destination_path\some_folder` - full path to folder, where augmented images will be stored 

## Example of using:
in *cmd.exe*:
`C:\Programs\ImageAugmentation_с.exe augmentation_arguments.txt C:\images D:\straight_images\out`
If you've done everything correctly, you'll see statistics of the program: execution time and a number of images augmented.
