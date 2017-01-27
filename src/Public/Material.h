#pragma once
#include "Color.h"

struct Material {
    ColorRGB color = Color::magenta;
    float opacity = 1.0; // from 0.0 to 1.0
};

