#pragma once
#include <cstdint>
#include <algorithm>

int8_t clamp(uint8_t target) { // encapsulate in CPP
    return std::min(std::max(target, static_cast<uint8_t>(0)), static_cast<uint8_t>(255));
}

struct ColorRGB {
    ColorRGB(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    ColorRGB(const ColorRGB& c) : r(c.r), g(c.g), b(c.b) {} // TODO check what happens without casting

    uint8_t r, g, b;

    ColorRGB operator*(float k) const {
        return ColorRGB(clamp(k*r), clamp(k*g), clamp(k*b));
    }

};

struct ColorRGBA : public ColorRGB {
    ColorRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : ColorRGB(r, g, b), a(a) {}
    ColorRGBA(ColorRGB c, uint8_t a) : ColorRGB(c), a(a) {}
    ColorRGBA(ColorRGB c) : ColorRGBA(c, 255) {}

    uint8_t a;

    ColorRGBA operator*(float k) const {
        return ColorRGBA(clamp(k*r), clamp(k*g), clamp(k*b), a);
    }
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