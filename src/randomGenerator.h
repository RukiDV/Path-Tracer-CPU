#pragma once

#include <random>
#include "glm/glm.hpp"

class RandomGenerator
{
public:
    RandomGenerator() {
        //std::random_device rd;
        //std::uniform_real_distribution<float> dis(0, 20000);
        distribution = std::uniform_real_distribution<float>(0.0f, 1.0f);
        generator = std::mt19937(0/*dis(rd)*/);
    };

    inline float random_num()
    {return distribution(generator);}

    glm::vec3 random_in_unit_sphere() {
        glm::vec3 p;
        do {
        p = 2.0f * glm::vec3(random_num(), random_num(), random_num()) - glm::vec3(1.0f, 1.0f, 1.0f);
        }
        while (glm::length(p) >= 1.0f);
        return p;
    };

private:
    std::uniform_real_distribution<float> distribution;
    std::mt19937 generator;
};