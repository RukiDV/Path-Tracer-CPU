#pragma once

#include "hittable.h"
#include "glm/glm.hpp"

class Sphere : public Hittable {

public:
    Sphere() {}
    Sphere(glm::vec3 cen, float r) : center(cen), radius(r) {}

    virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

public:
    glm::vec3 center;
    float radius;
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
    glm::vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto half_b = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius; 

    auto discriminant = half_b * half_b - a * c; 
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    //nearest root that in an acceptable range
    auto root = (-half_b - sqrtd) / a;

    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
    
        if (root < t_min || t_max < root)
            return false;
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    glm::vec3 outward_normal = (rec.p - center) / radius; 
    rec.set_face_normal(r, outward_normal);
    
    return true;
}
