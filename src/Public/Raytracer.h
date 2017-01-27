#pragma once
#include "Image.h"
#include "Scene.h"
#include "MyMath.h"
#include <gmtl/gmtl.h>
#include <iomanip>

using gmtl::Vec3f;
using gmtl::Rayf;
using gmtl::Point3f;
using gmtl::Matrix44f;

template<int width, int height>
class Raytracer {
public:
    Raytracer(const Scene& s, float fov_angle)
            : scene(s), fov(deg2rad(fov_angle)), img(Image<width, height>(Color::white))
    {}

    void run() {
        std::cout << "Generating image..." << std::endl;
        std::cout << std::fixed;
        std::cout << std::setprecision(1);

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
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

private:
    Image<width, height> img;
    const Scene& scene;
    float fov;


    QuadraticSolution intersects(const Rayf& ray, const Sphere& obj) {
        Vec3f p = ray.getOrigin() - Vec3f(obj.x, obj.y, obj.z);
        return quadratic_solver(1, 2 * dot(p, ray.getDir()), dot(p, p) - obj.r * obj.r);
    }

    void cast_ray(const Rayf& ray, ColorRGB& pixel) {
        for (auto it = scene.getObjects().begin(); it != scene.getObjects().end(); ++it) {
            const Object* obj = it->get(); // TODO you shouldn't have to know about scene implementation!
            QuadraticSolution result = intersects(ray, *dynamic_cast<const Sphere*>(obj)); // TODO check different types!
            if (result.numSolutionsFound > 0) {
                pixel = (*obj).material.color;
            }
        }
    }
};