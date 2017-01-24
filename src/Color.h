#pragma once
#include <cstdint>

/*
struct ColorRGB {
    uint8_t r, g, b;
    operator ColorRGBA() {
        return ColorRGBA{r, g, b, 255};
    }
};
 */

struct ColorRGBA {
    uint8_t r, g, b, a;
    /*
    operator ColorRGB() {
        return ColorRGB{r, g, b};
    };
     */
};

namespace Color {
    const ColorRGBA red {255, 0, 0, 255};
    const ColorRGBA green {0, 255, 0, 255};
    const ColorRGBA blue {0, 0, 255, 255};
    const ColorRGBA yellow {255, 255, 0, 255};
    const ColorRGBA magenta {255, 0, 255, 255};
    const ColorRGBA purple {0, 255, 255, 255};
    const ColorRGBA white {255, 255, 255, 255};
    const ColorRGBA black {0, 0, 0, 255};

}