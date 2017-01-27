#include "Public/Image.h"
#include "MyMath.h"
#include <gmtl/gmtl.h>
#include <iomanip>

using gmtl::Vec3f;
using gmtl::Rayf;
using gmtl::Point3f;

class Object {
public:
    float x, y, z;
protected:
    Object(float x, float y, float z) : x(x), y(y), z(z) {}
    virtual ~Object() = default;
    ColorRGB color = Color::magenta;
};


class Sphere {//: protected Object {
public:
    float x, y, z, r;
    Sphere(float x, float y, float z, float r) : x(x), y(y), z(z), r(r) {}
    virtual ~Sphere() = default;
    ColorRGB color = Color::red;
};

class Light : public Object {
public:
    Light(float x, float y, float z) : Object(x, y, z) {}
    float intensity = 1.0f;
};

std::vector<::Sphere> objects {::Sphere(0, 0, -2, 1), ::Sphere(0, 1, -2, 0.5f)};

QuadraticSolution intersects(const Rayf& ray, const ::Sphere obj) {
    Vec3f p = ray.getOrigin() - Vec3f(obj.x, obj.y, obj.z);
    return quadratic_solver(1, 2 * dot(p, ray.getDir()), dot(p, p) - obj.r * obj.r); // TODO test this
}

void cast_ray(const Rayf& ray, ColorRGB& pixel) {
    for (auto obj = objects.begin(); obj != objects.end(); ++obj) {
        QuadraticSolution result = intersects(ray, *obj);
        if (result.numSolutionsFound > 0) {
            pixel = (*obj).color;
        }
    }
}

void raytracer() {
    Image<640, 480> img(Color::white);
    float fov = deg2rad(90);
    std::cout << "Generating image..." << std::endl;
    std::cout << std::fixed;
    std::cout << std::setprecision(1);
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
        std::cout << "\r" << ( i / static_cast<float>(img.width) * 100) << "%                         ";
    }
    std::cout << "\r" << "100.0%                         ";
    std::cout << "\nImage generated!";

    img.savePPM("output/out.ppm");
}

int main() {
    raytracer();
    return 0;
}