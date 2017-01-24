#pragma once
#include "Color.h"
#include <array>
#include <iostream>
#include <cassert>

template <int width, int height>
class Image {
    class Proxy;

public:
    Image() {
        for (auto column = img.begin(); column != img.end(); ++column) {
            column->fill(Color::white);
        }
    }

    Proxy operator[](int x) {
        assert(x >= 0 && x < width);
        return Proxy(img[x]);
    }

private:
    using data_t = std::array<std::array<ColorRGBA, height>, width>;
    data_t img;

    class Proxy {
    public:
        ColorRGBA& operator[](int y) { assert(y >= 0 && y < height); return column[y];}
        Proxy(std::array<ColorRGBA, height>& column) : column(column) {}
    private:
        std::array<ColorRGBA, height>& column;
    };
};