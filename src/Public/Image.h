#pragma once
#include "Color.h"
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

class Image {
    class ColumnAccessor;

public:
    using iterator = ColorRGB*;
    using const_iterator = const ColorRGB*;

    const int width;
    const int height;
    const float widthf = static_cast<float>(width);
    const float heightf = static_cast<float>(height);
    const float aspect_ratio = widthf/heightf;

    Image(int width, int height, ColorRGB bgColor)
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
        file << "255" << "\n";

        for (int j = 0; j < height; ++j) {
            file << " ";
            for (int i = 0; i < width; ++i) {
                file << static_cast<int>(img[i][j].r) << " "
                     << static_cast<int>(img[i][j].g) << " "
                     << static_cast<int>(img[i][j].b) << " ";
            }
            file << " \n";
        }

        file.close();
    }

    ColorRGB getBackgroundColor() {
        return bgColor;
    }

private:
    using data_t = std::vector<std::vector<ColorRGB> >;
    data_t img;
    ColorRGB bgColor;

    class ColumnAccessor {
    public:
        ColorRGB& operator[](int y) { assert(y >= 0 && y < column.size()); return column[y];}
        ColumnAccessor(std::vector<ColorRGB>& column) : column(column) {}
    private:
        std::vector<ColorRGB>& column;
    };
};