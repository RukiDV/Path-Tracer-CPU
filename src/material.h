#pragma once

#include "math.h"
#include "ray.h"
#include "randomGenerator.h"
#include "sphere.h"

struct hit_record;

class Material {
    public:
    virtual bool scatter(const Ray& r_in, const hit_record& rec, glm::vec4& attenuation, Ray& scattered, RandomGenerator& rg) const = 0;
};

class lambertian : public Material {

public:
    lambertian(const glm::vec3 a) : albedo(a) {}
    virtual bool scatter(const Ray& r_in, const hit_record& rec, glm::vec4& attenuation, Ray& scattered, RandomGenerator& rg) const override {
        auto scatter_direction = rec.normal + rg.random_in_unit_sphere();
        scattered = Ray(rec.p, scatter_direction);
        attenuation = glm::vec4(albedo, 1.0f);
        return true;
    }

public:
glm::vec3 albedo;

};

class metal : public Material {

public:
    metal(const glm::vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}
    virtual bool scatter(const Ray& r_in, const hit_record& rec, glm::vec4& attenuation, Ray& scattered, RandomGenerator& rg) const override {
        glm::vec3 reflected = glm::reflect(glm::normalize(r_in.direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * rg.random_in_unit_sphere());
        attenuation = glm::vec4(albedo, 1.0f);
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
glm::vec3 albedo;
glm::vec3 fuzz;

};

class dielectric : public Material {

public:
    dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    virtual bool scatter(const Ray& r_in, const hit_record& rec, glm::vec4& attenuation, Ray& scattered, RandomGenerator& rg) const override {
        attenuation = glm::vec4(1.0, 1.0, 1.0, 1.0);
        float refraction_ratio = rec.front_face ? (1.0/ir) : ir;

        glm::vec3 unit_direction = glm::normalize(r_in.direction());
        float cos_theta = std::min(glm::dot(-unit_direction, rec.normal), 1.0f);
        
        float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
        bool cannot_refract = refraction_ratio * sin_theta > 1.0f; 
        glm::vec3 direction;

        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > rg.random_num()) {
            direction = glm::reflect(unit_direction, rec.normal); 
        } else {
            direction = glm::refract(unit_direction, rec.normal, refraction_ratio);
        }
       
    scattered = Ray(rec.p, direction);
        
    return true;
}

public:
double ir; // Index of Refraction

private:
float reflectance(float cosine, float ref_idx) const { // Use Schlick's approximation for reflectance.
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

};