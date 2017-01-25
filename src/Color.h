#pragma once
#include <cstdint>

/*
struct ColorRGB {
    uint8_t r, g, b;
    operator ColorRGB() {
        return ColorRGB{r, g, b, 255};
    }
};
 */

struct ColorRGB {
    uint8_t r, g, b;
    /*
    operator ColorRGB() {
        return ColorRGB{r, g, b};
    };
     */
};

namespace Color {
    const ColorRGB red {255, 0, 0};
    const ColorRGB green {0, 255, 0};
    const ColorRGB blue {0, 0, 255};
    const ColorRGB yellow {255, 255, 0};
    const ColorRGB magenta {255, 0, 255};
    const ColorRGB purple {0, 255, 255};
    const ColorRGB white {255, 255, 255};
    const ColorRGB black {0, 0, 0};
}