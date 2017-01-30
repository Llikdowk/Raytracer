#pragma once
#include <cstdint>

struct ColorRGB {
    ColorRGB(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    ColorRGB(const ColorRGB& c) : r(c.r), g(c.g), b(c.b) {}

    uint8_t r, g, b;
};

struct ColorRGBA : public ColorRGB {
    ColorRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : ColorRGB(r, g, b), a(a) {}
    ColorRGBA(ColorRGB c, uint8_t a) : ColorRGB(c), a(a) {}
    ColorRGBA(ColorRGB c) : ColorRGBA(c, 255) {}

    uint8_t a;

};


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