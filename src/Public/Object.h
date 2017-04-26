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

    virtual Collision checkCollision(const Rayf& ray) const override {
        Vec3f p = ray.getOrigin() - centre;
        QuadraticSolution result = quadratic_solver(1, 2 * dot(p, ray.getDir()), dot(p, p) - r * r);
        if (result.numSolutionsFound > 0) {
            float r = result.x1 > 0 ? result.x1 : result.x2;
            if (r > 0) {
                Vec3f hitPoint = ray.getOrigin() + static_cast<Vec3f>(r * ray.getDir());
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

class Plane : public Object {
public:

    Plane(float x, float y, float z, float nx, float ny, float nz) : Object(x, y, z), normal(nx, ny, nz) {
    }

    Collision checkCollision(const Rayf &r) const override {
        float denominator = gmtl::dot(r.getDir(), normal);
        if (fabs(denominator) > 0.0001f) {
            float t = gmtl::dot(centre - r.getOrigin(), normal)/denominator;
            if (t > 0) {
                Vec3f hitPoint = r.getOrigin() + Vec3f(t*r.getDir());
                return {true, r.getOrigin() + hitPoint, gmtl::length(Vec3f(hitPoint - r.getOrigin()))};
            }
        }
        return {false, Vec3f(0,0,0), 0};
    }

    Vec3f getNormal(const Vec3f &point) const override {
        return normal;
    }

private:
    Vec3f normal;
};

class Light : public Object {
public:
    ColorRGB color = ColorRGB::white;

    Light(float x, float y, float z) : Object(x, y, z) {}
    Light(float x, float y, float z, ColorRGB c) : Object(x, y, z), color(c) {}
    Light* setColor(ColorRGB color) {
        this->color = color;
        return this;
    }

    virtual Collision checkCollision(const Rayf& ray) const override {
        return {false, Vec3f(0,0,0), 0.0f};
    }

    float getRadius() const {
        return radius;
    }

    Light* setRadius(float r) {
        radius = r;
        return this;
    }


private:
    float radius = 1.0f;
};
