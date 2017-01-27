#pragma once
#include "Color.h"
#include "Material.h"

class Object {
public:
    float x, y, z;
    Material material;
    virtual ~Object() = default;

protected:
    Object(float x, float y, float z) : x(x), y(y), z(z) {}
};


class Sphere : public Object {
public:
    float r;
    Sphere(float x, float y, float z, float r) : Object(x, y, z), r(r) {}
    //virtual ~Sphere() = default;
};

class Light : public Object {
public:
    Light(float x, float y, float z) : Object(x, y, z) {}
    float intensity = 1.0f;
};
