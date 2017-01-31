#pragma once
#include "Object.h"
#include <vector>
#include <memory>

class Scene {
public:
    using VectorObj = std::vector<std::unique_ptr<Object>>;
    using VectorLight = std::vector<std::unique_ptr<Light>>;

    Scene& addObject(Object* obj) {
        objects.push_back(VectorObj::value_type(obj));
        return *this;
    }

    Scene& addLight(Light* obj) {
        lights.push_back(VectorLight::value_type(obj));
        return *this;
    }

    const VectorObj& getObjects() const { return objects; }
    const VectorLight& getLights() const { return lights; }

private:
    VectorObj objects;
    VectorLight lights;
    //Camera camera;
};