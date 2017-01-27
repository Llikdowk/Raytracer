#pragma once
#include <cstdint>

struct ColorRGB {
    uint8_t r, g, b;
};

namespace Color {
    constexpr ColorRGB red {255, 0, 0};
    constexpr ColorRGB green {0, 255, 0};
    constexpr ColorRGB blue {0, 0, 255};
    constexpr ColorRGB yellow {255, 255, 0};
    constexpr ColorRGB magenta {255, 0, 255};
    constexpr ColorRGB purple {0, 255, 255};
    constexpr ColorRGB white {255, 255, 255};
    constexpr ColorRGB black {0, 0, 0};
}