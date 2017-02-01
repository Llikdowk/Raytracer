#pragma once
#include "Color.h"
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

template <class ColorEncoding>
class Image {
    class ColumnAccessor;

public:
    using iterator = ColorEncoding*;
    using const_iterator = const ColorEncoding*;

    const int width;
    const int height;
    const float widthf = static_cast<float>(width);
    const float heightf = static_cast<float>(height);
    const float aspect_ratio = widthf/heightf;

    Image(int width, int height, ColorEncoding bgColor)
        : width(width), height(height), bgColor(bgColor) {

        img.resize(width);
        for (int i = 0; i < width; ++i) {
            img[i].reserve(height);
            for (int j = 0; j < height; ++j) {
                img[i].push_back(bgColor);
            }
        }
    }

    ColumnAccessor operator[](int x) {
        assert(x >= 0 && x < width);
        return ColumnAccessor(img[x]);
    }

    void savePPM(const char* path) {
        std::ofstream file;
        file.open(path);

        file << "P3\n";
        file << "#" << path << "\n";
        file << width << " " << height << "\n";
        file << ColorEncoding::TOP_VALUE << "\n";

        for (int j = 0; j < height; ++j) {
            file << " ";
            for (int i = 0; i < width; ++i) {
                file << static_cast<unsigned int>(img[i][j].getR()) << " "
                     << static_cast<unsigned int>(img[i][j].getG()) << " "
                     << static_cast<unsigned int>(img[i][j].getB()) << " ";
            }
            file << " \n";
        }

        file.close();
    }

    ColorEncoding getBackgroundColor() {
        return bgColor;
    }

private:
    using data_t = std::vector<std::vector<ColorEncoding> >;
    data_t img;
    ColorEncoding bgColor;

    class ColumnAccessor {
    public:
        ColorEncoding& operator[](int y) { assert(y >= 0 && y < column.size()); return column[y];}
        ColumnAccessor(std::vector<ColorEncoding>& column) : column(column) {}
    private:
        std::vector<ColorEncoding>& column;
    };
};