#include "Image.h"
#include "Color.h"
#include <cmath>
#include <gmtl/gmtl.h>
#include <tuple>
#include <cmath>

using namespace gmtl;

/*
class Object {
public:
    float x, y, z;
protected:
    Object(float x, float y, float z) : x(x), y(y), z(z) {}
    virtual ~Object() = default;
    ColorRGB color = Color::magenta;
};
*/

class Sphere {//: protected Object {
public:
    float x, y, z, r;
    Sphere(float x, float y, float z, float r) : x(x), y(y), z(z), r(r) {}
    virtual ~Sphere() = default;
    ColorRGB color = Color::red;
};

std::vector<::Sphere> objects {::Sphere(0, 0, -2, 1)};
using quadratic_solution_t = std::tuple<int, float, float>;

quadratic_solution_t quadratic_solver(float a, float b, float c) { // a*x2 + b*x + c = 0
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0.0f) {
        return std::make_tuple(0, NAN, NAN);
    } else if (discriminant < 0.0001f) { // CAUTION! equals float comparison! check its correctness
        float result = -b / (2*a);
        return std::make_tuple(1, result, result);
    } else {
        float sign_b = (b > 0) - (b < 0);
        float q = -0.5f * (b + sign_b*sqrtf(b*b - 4*a*c)); // this quadratic formula avoids catastrophic cancellation
        float x1 = q/a;
        float x2 = c/q;
        if (x1 > x2) std::swap(x1, x2);
        return std::make_tuple(2, x1, x2);
    }
}

quadratic_solution_t intersects(const Rayf& ray, const ::Sphere obj) {
    Vec3f p = ray.getOrigin() - Vec3f(obj.x, obj.y, obj.z);
    return quadratic_solver(1, 2 * dot(p, ray.getDir()), dot(p, p) - obj.r * obj.r); // TODO test this
}

void cast_ray(const Rayf& ray, ColorRGB& pixel) {
    for (auto obj = objects.begin(); obj != objects.end(); ++obj) {
        quadratic_solution_t result = intersects(ray, *obj);
        if (std::get<0>(result) > 0) {
            pixel = (*obj).color;
        }
    }
}

void raytracer() {
    Image<640, 480> img(Color::white);
    float fov = M_PI_2;//90.0f;

    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            Point3f camera_raster {
                (2*i/img.widthf - 1) * img.aspect_ratio,
                (-2*j/img.heightf +  1) * tanf(fov/2.0f),
                -1
            };
            Point3f origin(0, 0, 0);
            Vec3f dir = camera_raster - origin;
            gmtl::normalize(dir);
            Rayf ray(origin, dir);
            //Matrix44f camera_to_world; // IDENTITY by default
            //ray = camera_to_world * ray;
            cast_ray(ray, img[i][j]);
        }
    }

    img.savePPM("output/out.ppm");
}

int main() {
    raytracer();
    return 0;
}