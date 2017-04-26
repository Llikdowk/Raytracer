#pragma once

#include "MyMath.h"
#include <cstdint>

template <typename T, T MAX_VALUE>
class Color { // TODO: fix internal color type
public:

    using value_type = T;
    enum { TOP_VALUE = MAX_VALUE };

    Color(float r, float g, float b)
        : r(clamp(r, 0.0f, 1.0f)*MAX_VALUE), g(clamp(g, 0.0f, 1.0f)*MAX_VALUE),
          b(clamp(b, 0.0f, 1.0f)*MAX_VALUE) {
    };

    Color operator*(float k) const {
        return Color(
                r/static_cast<float>(MAX_VALUE)*k,
                g/static_cast<float>(MAX_VALUE)*k,
                b/static_cast<float>(MAX_VALUE)*k
                );
    }
    template<typename, T> friend Color<T, MAX_VALUE> operator*(float, const Color<T, MAX_VALUE>&);

    Color operator*(const Color& c) const {
        return Color(r/static_cast<float>(MAX_VALUE) * c.r/static_cast<float>(MAX_VALUE),
                     g/static_cast<float>(MAX_VALUE) * c.g/static_cast<float>(MAX_VALUE),
                     b/static_cast<float>(MAX_VALUE) * c.b/static_cast<float>(MAX_VALUE)
                     );
    }

    Color operator+(const Color& c) const {
        return Color(r/static_cast<float>(MAX_VALUE) + c.r/static_cast<float>(MAX_VALUE),
                     g/static_cast<float>(MAX_VALUE) + c.g/static_cast<float>(MAX_VALUE),
                     b/static_cast<float>(MAX_VALUE) + c.b/static_cast<float>(MAX_VALUE)
                     );
    }

    Color operator+=(const Color& c) {
        r = MAX_VALUE * (r / static_cast<float>(MAX_VALUE) + c.r/static_cast<float>(MAX_VALUE));
        g = MAX_VALUE * (g / static_cast<float>(MAX_VALUE) + c.g/static_cast<float>(MAX_VALUE));
        b = MAX_VALUE * (b / static_cast<float>(MAX_VALUE) + c.b/static_cast<float>(MAX_VALUE));
    }

    Color operator-(const Color& c) const {
        return Color(r/ static_cast<float>(MAX_VALUE) - c.r/static_cast<float>(MAX_VALUE),
                     g/ static_cast<float>(MAX_VALUE) - c.g/static_cast<float>(MAX_VALUE),
                     b/ static_cast<float>(MAX_VALUE) - c.b/static_cast<float>(MAX_VALUE)
                     );
    }

    Color operator-=(const Color& c) {
        r = MAX_VALUE * (r / static_cast<float>(MAX_VALUE) - c.r/static_cast<float>(MAX_VALUE));
        g = MAX_VALUE * (g / static_cast<float>(MAX_VALUE) - c.g/static_cast<float>(MAX_VALUE));
        b = MAX_VALUE * (b / static_cast<float>(MAX_VALUE) - c.b/static_cast<float>(MAX_VALUE));
    }

    bool operator==(const Color& c) const {
        return r == c.r && g == c.g && b == c.b;
    }
    bool operator!=(const Color& c) const {
        return !(*this == c);
    }

    T getR() { return r; }
    T getG() { return g; }
    T getB() { return b; }

    static const Color<T, MAX_VALUE> red;
    static const Color<T, MAX_VALUE> green;
    static const Color<T, MAX_VALUE> blue;
    static const Color<T, MAX_VALUE> yellow;
    static const Color<T, MAX_VALUE> magenta;
    static const Color<T, MAX_VALUE> cyan;
    static const Color<T, MAX_VALUE> white;
    static const Color<T, MAX_VALUE> black;

private:
    T r, g, b;
};

template <typename T, T MAX_VALUE>
Color<T, MAX_VALUE> operator*(float k, const Color<T, MAX_VALUE>& c) { return c * k; }

template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::red = Color<T, MAX_VALUE>    (1, 0, 0);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::green = Color<T, MAX_VALUE>  (0, 1, 0);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::blue = Color<T, MAX_VALUE>   (0, 0, 1);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::yellow = Color<T, MAX_VALUE> (1, 1, 0);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::magenta = Color<T, MAX_VALUE>(1, 0, 1);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::cyan = Color<T, MAX_VALUE> (0, 1, 1);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::white = Color<T, MAX_VALUE>  (1, 1, 1);
template <typename T, T MAX_VALUE> const Color<T, MAX_VALUE> Color<T, MAX_VALUE>::black = Color<T, MAX_VALUE>  (0, 0, 0);

using ColorRGB = Color<uint16_t, 0xFF>; // fixme! mismatch between max size available and max size set to fix rare overflow issues
