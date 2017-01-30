#pragma once
#include <cmath>
#include <utility>

struct QuadraticSolution {
    int numSolutionsFound;
    float x1, x2;
};

QuadraticSolution quadratic_solver(float a, float b, float c) { // a*x2 + b*x + c = 0
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0.0f) {
        return QuadraticSolution{0, NAN, NAN};
    } else if (discriminant < 0.0001f) { // CAUTION! equals float comparison! check its correctness
        float result = -b / (2*a);
        return QuadraticSolution{1, result, result};
    } else {
        float sign_b = (b > 0) - (b < 0);
        float q = -0.5f * (b + sign_b*sqrtf(b*b - 4*a*c)); // this quadratic formula avoids catastrophic cancellation
        float x1 = q/a;
        float x2 = c/q;
        if (x1 > x2) std::swap(x1, x2);
        return QuadraticSolution{2, x1, x2};
    }
}

float deg2rad(float deg) {
    return 2 * static_cast<float>(M_PI) / 360.0f * deg;
}

float rad2deg(float rad) {
    return 360.0f / (2 * static_cast<float>(M_PI)) * rad;
}
