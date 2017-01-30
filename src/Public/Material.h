#pragma once
#include "Color.h"

struct Material {
    Material() = default;
    Material(ColorRGB color, float opacity) : color(color), opacity(opacity) {
    }
    ColorRGB color = Color::magenta;
    float opacity = 1.0; // from 0.0 to 1.0
};

