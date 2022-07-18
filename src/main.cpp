#include <iostream> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "ray.h"
#include "color.h"

#define CHANNEL_NUM 4
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


int main() {

    const int image_width = 500;
    const int image_height = 500;

    std::vector<uint32_t> pixels(image_width * image_height);

    int index = 0;

    for (int i = image_height - 1; i >= 0; --i) {
        for (int j = 0; j < image_width; ++j) {
            Color pixel_color(double(j) / (image_width - 1), double(i) / (image_height - 1), 0.75f);
            pixels[index++] = pixel_color.convert_to_8_bit();
        }
    }

    int exit_code_img_wr = stbi_write_png("test.png", image_width, image_height, CHANNEL_NUM, reinterpret_cast<uint8_t*>(pixels.data()), image_width * CHANNEL_NUM);
    std::cout << "Writing image: " << exit_code_img_wr << std::endl;

    return 0;
}