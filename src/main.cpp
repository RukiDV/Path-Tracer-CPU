#include <iostream> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "ray.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "math.h"
#include "sphere.h"

#define CHANNEL_NUM 4
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Color ray_color(const Ray& r, const Hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) { 
        return Color(0.5f * (rec.normal + glm::vec3(1.0f, 1.0f, 1.0f)));
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    auto t = 0.5f * (unit_direction.y + 1.0f);
    return Color((1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f));
}

int main() {

    //Image
    const auto aspect_ratio = 16.0f/10.0f;
    const int image_width = 1000;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    Hittable_list world; 
    world.add(make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f)); 
    world.add(make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f));

    //Camera
    auto viewport_height = 2.0f;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 25.0f;

    auto origin = glm::vec3(0.0f, 0.0f, 20.0f);
    auto horizontal = glm::vec3(viewport_width, 0.0f, 0.0f);
    auto vertical = glm::vec3(0.0f, viewport_height, 0.0f);
    auto lower_left_corner = origin - horizontal/2.0f - vertical/2.0f - glm::vec3(0, 0, focal_length);

    std::vector<uint32_t> pixels(image_width * image_height);

    int index = 0;

    for (int i = image_height - 1; i >= 0; --i) {
        for (int j = 0; j < image_width; ++j) {
            //Color pixel_color(double(j) / (image_width - 1), double(i) / (image_height - 1), 0.75f);
            float u = float(j) / (image_width - 1);
            float v = float(i) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            Color pixel_color = ray_color(r, world);
            pixels[index++] = pixel_color.convert_to_8_bit();
        }
    }

    int exit_code_img_wr = stbi_write_png("test.png", image_width, image_height, CHANNEL_NUM, reinterpret_cast<uint8_t*>(pixels.data()), image_width * CHANNEL_NUM);
    std::cout << "Writing image: " << exit_code_img_wr << std::endl;

    return 0;
}