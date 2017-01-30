#pragma once
#include "Image.h"
#include "Scene.h"
#include "MyMath.h"
#include <iomanip>

#include <gmtl/gmtl.h>
using gmtl::Vec3f;
using gmtl::Rayf;
using gmtl::Point3f;
using gmtl::Matrix44f;

class Raytracer {
public:

    Raytracer(const Scene& scene, int width, int height, float fov_angle)
            : scene(scene), fov(deg2rad(fov_angle)), img(width, height, Color::white)
    {}

    void run() {
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

private:
    float fov; // rad
    const Scene& scene;
    Image img;

    void cast_ray(const Rayf& ray, ColorRGB& pixel) {
        float nearDistance = 4294967296.0f;
        for (auto it = scene.getObjects().begin(); it != scene.getObjects().end(); ++it) {
            const Object* obj = it->get(); // TODO you shouldn't have to know about scene implementation!
            Collision collision = obj->checkCollision(ray);
            if (collision.hasCollided && collision.distance < nearDistance) {
                pixel = (*obj).material.color;
                nearDistance = collision.distance;
            }
        }
    }
};