#pragma once

#include "glm/glm.hpp"
#include <iostream>

class Color {
public:
    explicit Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) { rgba = glm::vec4(r, g, b, a); }
    glm::vec4 rgba;

    uint32_t convert_to_8_bit() {
        uint32_t converted_color = glm::clamp(static_cast<uint32_t>(255.999 * rgba.a), 0u, 255u);
        converted_color <<= 8;
        converted_color += glm::clamp(static_cast<uint32_t>(255.999 * rgba.b), 0u, 255u);
        converted_color <<= 8;
        converted_color += glm::clamp(static_cast<uint32_t>(255.999 * rgba.g), 0u, 255u);
        converted_color <<= 8;
        converted_color += glm::clamp(static_cast<uint32_t>(255.999 * rgba.r), 0u, 255u);
        return converted_color;
    }
};
