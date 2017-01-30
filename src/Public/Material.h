#pragma once
#include "Color.h"

struct Material {
    Material() = default;
    Material(const ColorRGBA& color) : color(color) {}
    ColorRGBA color = Color::magenta;
};

