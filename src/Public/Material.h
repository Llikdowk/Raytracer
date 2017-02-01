#pragma once
#include "Color.h"

namespace RefractionCoefficient {
    const float empty = 1.0;
    const float glass = 1.52;
    const float water = 1.333;
};

struct Material {
    Material() = default;
    Material(const ColorRGBA& color) : color(color) {}
    ColorRGBA color = ColorRGBA::magenta;
    float kEmission = 0.001f;
    float kDiffuse = 0.750f;
    float kSpecular = 1.0f;
    float specularPower = 250.0f; // glossiness
    float kFresnel = 1.0f;
    float fresnelPower = 10.0f;
    float kRefraction = RefractionCoefficient::glass;
};

