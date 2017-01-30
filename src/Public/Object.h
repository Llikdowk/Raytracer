#pragma once
#include "Color.h"
#include "Material.h"
#include "MyMath.h"

#include <gmtl/gmtl.h>
using gmtl::Vec3f;
using gmtl::Rayf;

struct Collision {
    bool hasCollided;
    Vec3f hitPoint;
    float distance;
};

class Object {
public:
    Vec3f centre;
    Material material;
    virtual ~Object() = default;
    virtual Collision checkCollision(const Rayf& r) const = 0;
    virtual Vec3f getNormal(const Vec3f& point) const { return Vec3f(0,0,0); };


protected:
    Object(float x, float y, float z) : centre(x, y, z) {}
};


class Sphere : public Object {
public:
    float r;
    Sphere(float x, float y, float z, float r) : Object(x, y, z), r(r) {}
    Sphere(float x, float y, float z, float r, Material mat) : Sphere(x, y, z, r) { material = mat; }
    virtual ~Sphere() = default;

    virtual Collision checkCollision(const Rayf& ray) const override {
        Vec3f p = ray.getOrigin() - centre;
        QuadraticSolution result = quadratic_solver(1, 2 * dot(p, ray.getDir()), dot(p, p) - r * r);
        if (result.numSolutionsFound > 0) {
            float r = result.x1 > 0 ? result.x1 : result.x2;
            if (r > 0) {
                Vec3f hitPoint = ray.getOrigin() + r * ray.getDir();
                return {true, hitPoint, r};
            }
        }

        return {false, Vec3f(0,0,0), 0};
    }

    virtual Vec3f getNormal(const Vec3f& point) const override {
        Vec3f dif = point - centre;
        gmtl::normalize(dif);
        return dif;
    }
};

class Light : public Object {
public:
    Light(float x, float y, float z) : Object(x, y, z) {}
    Light& setColor(ColorRGBA color) {
        this->color = color;
        return *this;
    }
    Light& setColor(ColorRGB color) {
        this->color = ColorRGBA(color, 255);
        return *this;
    }
    Light& setIntensity(float f) {
        f = std::min(std::max(f, 0.0f), 1.0f);
        color.a = static_cast<uint8_t>(f*255);
    }

    virtual Collision checkCollision(const Rayf& ray) const override {
        return {false, Vec3f(0,0,0), 0.0f};
    }

    ColorRGBA color = Color::white;
};
