#pragma once
#include "Image.h"
#include "Scene.h"
#include "MyMath.h"
#include "Color.h"
#include <iomanip>

#include <gmtl/gmtl.h>
using gmtl::Vec3f;
using gmtl::Rayf;
using gmtl::Point3f;
using gmtl::Matrix44f;

class Raytracer {
public:

    Raytracer(const Scene& scene, int width, int height, float fov_angle)
            : scene(scene), fov(deg2rad(fov_angle)), img(width, height, ColorRGBA(.2, .2, .2))
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
                img[i][j] = cast_ray(ray);
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
    Image<ColorRGBA> img;

    ColorRGBA cast_ray(const Rayf& ray, int depth = 0) {
        static const int MAX_DEPTH = 7;
        //static const float GLOSSINESS = 75.0f;
        //static const float FRESNEL = 10.0f;
        if (depth > MAX_DEPTH) {
            return ColorRGBA::black; //img.getBackgroundColor();
        }


        float nearDistance = 10e9f;
        const Object* nearObj = nullptr;
        Collision nearCollision;
        for (auto it = scene.getObjects().begin(); it != scene.getObjects().end(); ++it) {
            const Object& obj = *(*it);
            Collision collision = obj.checkCollision(ray);
            if (collision.hasCollided && collision.distance < nearDistance) {
                nearDistance = collision.distance;
                nearObj = &obj;
                nearCollision = collision;
            }
        }
        if (nearObj != nullptr) {
            ColorRGBA pixel = ColorRGBA::black;
            Vec3f normal = nearObj->getNormal(nearCollision.hitPoint);
            Vec3f reflection;
            for (auto light_it = scene.getLights().begin(); light_it != scene.getLights().end(); ++light_it) {
                const Light &light = *(*light_it);
                Vec3f lDir = light.centre - nearCollision.hitPoint;
                float lDistance = gmtl::length(lDir);
                gmtl::normalize(lDir);
                gmtl::reflect(reflection, ray.getDir(), normal);
                const Material& mat = nearObj->material;
                float diffuse = mat.kDiffuse * std::max(gmtl::dot(normal, lDir), 0.0f);
                reflection *= -1;
                float specular = mat.kSpecular * powf(std::max(gmtl::dot(ray.getDir(), reflection), 0.0f), mat.specularPower);
                reflection *= -1;
                float fresnel = mat.kFresnel * powf(std::max(gmtl::dot(ray.getDir(), reflection), 0.0f), mat.fresnelPower);
                float shading = (diffuse + specular + fresnel)/(lDistance*lDistance);
                pixel += shading * (mat.color * light.color);
            }
            return pixel + 0.75f * cast_ray(Rayf(nearCollision.hitPoint + static_cast<Vec3f>(normal*0.1f), reflection), depth + 1); // fixme color mult not working properly!
        }

        if (depth == 0) {
            return img.getBackgroundColor();
        } else {
            return ColorRGBA::black;
        }
    }
};