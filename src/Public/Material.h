#pragma once
#include "Color.h"

namespace RefractionCoefficient {
    const float empty = 1.0;
    const float glass = 1.52;
    const float water = 1.333;
};

struct Material {
    Material() = default;
    Material(const ColorRGB& color) : color(color) {}
    ColorRGB color = ColorRGB::magenta;
    float kEmission = 0.001f;
    float kDiffuse = 0.750f;
    float kSpecular = 1.0f;
    float specularPower = 250.0f; // glossiness
    float kFresnel = 0.5f;
    float fresnelPower = 10.0f;
    float matRefraction = RefractionCoefficient::glass;
    float kRefraction = 1.0f;
    float kReflection = 0.5f;
};

