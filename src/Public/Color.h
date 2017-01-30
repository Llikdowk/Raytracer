#pragma once
#include <cstdint>

class ColorRGBA;
struct ColorRGB {
    ColorRGB(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    uint8_t r, g, b;
    operator ColorRGBA();
};

struct ColorRGBA : ColorRGB {
    ColorRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : ColorRGB(r, g, b), a(a) {}
    uint8_t a;
    operator ColorRGB();
};

ColorRGB::operator ColorRGBA() {
    return ColorRGBA(r, g, b, 255);
}

ColorRGBA::operator ColorRGB() {
    return ColorRGB(r, g, b);
}


namespace Color {
    const ColorRGB red      (255, 0, 0);
    const ColorRGB green    (0, 255, 0);
    const ColorRGB blue     (0, 0, 255);
    const ColorRGB yellow   (255, 255, 0);
    const ColorRGB magenta  (255, 0, 255);
    const ColorRGB purple   (0, 255, 255);
    const ColorRGB white    (255, 255, 255);
    const ColorRGB black    (0, 0, 0);
}