#pragma once

#include <cstdint>
#include <algorithm>

template <typename T, T MAX_VALUE>
class Color {
public:

    using value_type = T;
    enum { TOP_VALUE = MAX_VALUE };

    Color(float r, float g, float b, float a = 1)
        : r(r*MAX_VALUE), g(g*MAX_VALUE), b(b*MAX_VALUE), a(a*MAX_VALUE) {
        clamp();
    };

    void setAlpha(float a) {
//        this->a = std::min(std::max(a*MAX_VALUE, 0), MAX_VALUE);
        this->a = a; // TODO unsafe
    }

    Color operator*(float k) const {
        return Color(r/MAX_VALUE*k, g/MAX_VALUE*k, b/MAX_VALUE*k, a);//.clamp();
    }
    template<typename, size_t> friend Color<T, MAX_VALUE> operator*(float, const Color<T, MAX_VALUE>&);


    Color operator+(const Color& c) const {
        return Color(r+c.r, g+c.g, b+c.b, a);//.clamp();
    }

    bool operator==(const Color& c) const {
        return r == c.r && g == c.g && b == c.b && a == c.a;
    }
    bool operator!=(const Color& c) const {
        return !(*this == c);
    }

    T getR() { return r; }
    T getG() { return g; }
    T getB() { return b; }
    T getA() { return a; }

    static const Color<T, MAX_VALUE> red;
    static const Color<T, MAX_VALUE> green;
    static const Color<T, MAX_VALUE> blue;
    static const Color<T, MAX_VALUE> yellow;
    static const Color<T, MAX_VALUE> magenta;
    static const Color<T, MAX_VALUE> purple;
    static const Color<T, MAX_VALUE> white;
    static const Color<T, MAX_VALUE> black;

private:
    T r, g, b, a;

    Color& clamp() {
        r = std::min(std::max(r, static_cast<T>(0)), MAX_VALUE);
        g = std::min(std::max(g, static_cast<T>(0)), MAX_VALUE);
        b = std::min(std::max(b, static_cast<T>(0)), MAX_VALUE);
        a = std::min(std::max(a, static_cast<T>(0)), MAX_VALUE);
        return *this;
    }
};

template <typename T, T MAX_VALUE>
Color<T, MAX_VALUE> operator*(float k, const Color<T, MAX_VALUE>& c) { return c * k; }

template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::red = Color<T, MAX_VALUE>    (1, 0, 0);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::green = Color<T, MAX_VALUE>  (0, 1, 0);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::blue = Color<T, MAX_VALUE>   (0, 0, 1);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::yellow = Color<T, MAX_VALUE> (1, 1, 0);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::magenta = Color<T, MAX_VALUE>(1, 0, 1);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::purple = Color<T, MAX_VALUE> (0, 1, 1);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::white = Color<T, MAX_VALUE>  (1, 1, 1);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::black = Color<T, MAX_VALUE>  (0, 0, 0);

using ColorRGBA = Color<uint16_t, 0xFF>;

