#pragma once
#include "Color.h"

struct Material {
    Material() = default;
    Material(const ColorRGBA& color) : color(color) {}
    ColorRGBA color = ColorRGBA::magenta;
    float kDiffuse = 1.0f;
    float kSpecular = 1.0f;
    float specularPower = 75.0f; // glossiness
    float kFresnel = 1.0f;
    float fresnelPower = 10.0f;

};

