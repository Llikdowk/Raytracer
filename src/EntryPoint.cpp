#include "Public/Image.h"
#include "MyMath.h"
#include "Scene.h"
#include <gmtl/gmtl.h>
#include <iomanip>

using gmtl::Vec3f;
using gmtl::Rayf;
using gmtl::Point3f;
using gmtl::Matrix44f;

Scene scene;

QuadraticSolution intersects(const Rayf& ray, const Sphere& obj) {
    Vec3f p = ray.getOrigin() - Vec3f(obj.x, obj.y, obj.z);
    return quadratic_solver(1, 2 * dot(p, ray.getDir()), dot(p, p) - obj.r * obj.r);
}

void cast_ray(const Rayf& ray, ColorRGB& pixel) {
    for (auto it = scene.getObjects().begin(); it != scene.getObjects().end(); ++it) {
        const Object* obj = it->get(); // TODO you shouldn't have to know about scene implementation!
        QuadraticSolution result = intersects(ray, *dynamic_cast<const Sphere*>(obj));
        if (result.numSolutionsFound > 0) {
            pixel = (*obj).material.color;
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
            Matrix44f camera_to_world; // IDENTITY by default
            ray = camera_to_world * ray;
            cast_ray(ray, img[i][j]);
        }
        std::cout << "\r" << ( i / static_cast<float>(img.width) * 100) << "%                         ";
    }
    std::cout << "\r" << "100.0%                         ";
    std::cout << "\nImage generated!";

    img.savePPM("output/out.ppm");
}

int main() {
    scene.addObject(new Sphere(0, 0, -2, 1))
         .addObject(new Sphere(0, 1, -2, 0.5f));
    raytracer();
    return 0;
}