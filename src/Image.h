#pragma once
#include "Color.h"
#include <array>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

template <int width, int height>
class Image {
    class Proxy;

public:
    using iterator = ColorRGB*;
    using const_iterator = const ColorRGB*;

    Image() {
        Image(Color::white);
    }

    Image(ColorRGB c) {
        for(int i = 0; i < width; ++i){
            img[i].fill(c);
        }
    }

    Proxy operator[](int x) {
        assert(x >= 0 && x < width);
        return Proxy(img[x]);
    }

    void savePPM(const char* path) {
        std::ofstream file;
        file.open(path);

        //myfile << "Writing this to a file.\n";
        file << "P3\n";
        file << "#" << path << "\n";
        file << width << " " << height << "\n";
        file << "255" << "\n";

        for (int j = 0; j < height; ++j) {
            file << " ";
            for (int i = 0; i < width; ++i) {
                file << static_cast<int>(img[i][j].r) << " "
                     << static_cast<int>(img[i][j].g) << " "
                     << static_cast<int>(img[i][j].b) << " \t";
            }
            file << " \n";
        }

        file.close();
    }

    //iterator begin() { return img[0][0]; }
    //iterator end() { return img[width][height]; }
    const_iterator begin() const { return img[0][0]; }
    const_iterator end() const { return img[width][height]; }

private:
    using data_t = std::array<std::array<ColorRGB, height>, width>;
    data_t img;

    class Proxy {
    public:
        ColorRGB& operator[](int y) { assert(y >= 0 && y < height); return column[y];}
        Proxy(std::array<ColorRGB, height>& column) : column(column) {}
    private:
        std::array<ColorRGB, height>& column;
    };
};