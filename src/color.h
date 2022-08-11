#pragma once

#include "glm/glm.hpp"
#include <iostream>

class Color {
public:
    explicit Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) { rgba = glm::vec4(r, g, b, a); }
    explicit Color(glm::vec4 color) : rgba(color) {}
    explicit Color(glm::vec3 color) : rgba(glm::vec4(color, 1.0f)) {}
    glm::vec4 rgba;

    uint32_t convert_to_8_bit(int samples_per_pixel) {
        
        //auto r = pixel_color.rgba.r;
        //auto g = pixel_color.rgba.g;
        //auto b = pixel_color.rgba.b;
        
        // Divide the color by the number of samples.
        //auto scale = 1.0 / samples_per_pixel;
        //r *= scale;
        //g *= scale;
        //b *= scale;

        uint32_t converted_color = glm::clamp(static_cast<int32_t>(255.999 * rgba.a), 0, 255);
        converted_color <<= 8;
        converted_color += glm::clamp(static_cast<int32_t>(255.999 * rgba.b), 0, 255);
        converted_color <<= 8;
        converted_color += glm::clamp(static_cast<int32_t>(255.999 * rgba.g), 0, 255);
        converted_color <<= 8;
        converted_color += glm::clamp(static_cast<int32_t>(255.999 * rgba.r), 0, 255);
        return converted_color;
    }
};
