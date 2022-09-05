#include <iostream> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "ray.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "math.h"
#include "sphere.h"
#include "camera.h"
#include "randomGenerator.h"
#include "material.h"
#include <thread>

#define CHANNEL_NUM 4
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Color ray_color(const Ray& r, const Hittable& world, int depth, RandomGenerator& rg) {
    hit_record rec;

    if(depth <= 0) {
        return Color(0.0f, 0.0f, 0.0f);
    }
    if (world.hit(r, 0.00001, infinity, rec)) { 
        Ray scattered;
        glm::vec4 attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered, rg)) {
            return Color(attenuation * ray_color(scattered, world, depth - 1.0f, rg).rgba); 
        }
    return Color(glm::vec3(0.0f,0.0f,0.0f));
        
        //glm::vec3 target = rec.p + rec.normal + random_generator.random_in_unit_sphere();
        //return Color(0.5f * (rec.normal + glm::vec3(1.0f, 1.0f, 1.0f))); // + 0.01f * rec.normal
        //return Color(glm::vec3(ray_color(Ray(rec.p, target - rec.p), world, depth - 1, random_generator).rgba * glm::vec4(0.5f)));
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    auto t = 0.5f * (unit_direction.y + 1.0f);
    return Color(1.0f, 1.0f, 1.0f);//(1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f));
}

void render_pixel_row(const int image_width, const int image_height, const int samples_per_pixel, const int max_depth, const Hittable& world, Camera cam, int start, int end) {
    RandomGenerator rg;
    for (int j = 0; j < image_width; ++j) {
        Color pixel_color(0.0f, 0.0f, 0.0f);
        for (int k = 0; k < samples_per_pixel; ++k) {
            float v = float(i + rg.random_num()) / (image_height - 1.0f);
            float u = float(j + rg.random_num()) / (image_width - 1.0f);
                
            Ray r = cam.get_ray(u,v); 
            pixel_color.rgba += ray_color(r, world, max_depth, rg).rgba;
        }
        pixel_color.rgba /= static_cast<float>(samples_per_pixel);
        pixels[((image_height - 1) - i) * image_width + j] = pixel_color.convert_to_8_bit();
    }
}

int main() {

    //Image
    const auto aspect_ratio = 16.0f/10.0f;
    const int image_width = 1000;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 128;
    const int max_depth = 8;

    RandomGenerator rg;

    // World
    Hittable_list world; 
    //world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f)); 
    //world.add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f));

    auto material_ground = std::make_shared<lambertian>(glm::vec3(0.8f, 0.8f, 0.0f)); 
    auto material_center = std::make_shared<lambertian>(glm::vec3(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<dielectric>(1.5); 
    auto material_right = std::make_shared<metal>(glm::vec3(0.8, 0.6, 0.2), 0.0);

    world.add(std::make_shared<Sphere>(glm::vec3( 0.0f, -100.5f, -1.0f), 100.0f, material_ground)); 
    world.add(std::make_shared<Sphere>(glm::vec3( 0.0f, 0.0f, -1.0f), 0.5f, material_center));
    world.add(std::make_shared<Sphere>(glm::vec3(-1.0, 0.0, -1.0), 0.5, material_left));
   // world.add(std::make_shared<Sphere>(glm::vec3(-1.0f, 0.0f, -1.0f), -0.4f, material_left));
    world.add(std::make_shared<Sphere>(glm::vec3( 1.0f, 0.0f, -1.0f), 0.5f, material_right));

    //Camera
    Camera cam;

    //Renderer
    std::vector<uint32_t> pixels(image_width * image_height);
    std::thread t1 = std::thread(render_pixel_row, );

    for (int i = image_height - 1.0f; i >= 0; --i) {
 
    }

    int exit_code_img_wr = stbi_write_png("beautiful.png", image_width, image_height, CHANNEL_NUM, reinterpret_cast<uint8_t*>(pixels.data()), image_width * CHANNEL_NUM);
    std::cout << "Writing image: " << exit_code_img_wr << std::endl;

    t1.join();

    return 0;
}
