#pragma once
#include "Image.h"
#include "Scene.h"
#include "MyMath.h"
#include "Color.h"
#include <iomanip>
#include <chrono>

#include <gmtl/gmtl.h>
#include <omp.h>

using gmtl::Vec3f;
using gmtl::Rayf;
using gmtl::Point3f;
using gmtl::Matrix44f;


class Raytracer {
public:

    Raytracer(const Scene& scene, int width, int height, float fov_angle)
            : scene(scene), fov(deg2rad(fov_angle)), img(width, height, ColorRGBA(0.1, 0.1, 0.1))
    {
    }

    void run() {
        std::cout << "Generating image..." << std::endl;
        std::cout << std::fixed;
        std::cout << std::setprecision(1);

        auto start = std::chrono::high_resolution_clock::now();
        float progress = 0.0f;
        const float step = 1.0f/(img.width);
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                Point3f camera_raster{ // TODO: convert to object and move to Object.h
                        (2 * i / img.widthf - 1) * img.aspect_ratio,
                        (-2 * j / img.heightf + 1) * tanf(fov / 2.0f),
                        -1
                };
                Point3f origin(0, 0, 0);
                Vec3f dir = camera_raster - origin;
                gmtl::normalize(dir);
                Rayf ray(origin, dir);
                Matrix44f camera_to_world; // IDENTITY by default
                camera_to_world[0][3] = 0.0f; // x
                camera_to_world[1][3] = 0.0f; // y
                camera_to_world[2][3] = 1.0f; // z
                ray = camera_to_world * ray;
                img[i][j] = cast_ray(ray);
            }
            #pragma omp atomic
            progress += step;
            if (omp_get_thread_num() == 0) {
                std::cout << "\r" << progress * 100.0f << "%                         ";
            }
        }

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt = finish - start;
        std::cout << "\nElapsed time: " << dt.count() << "s" << std::endl;
        std::cout << "\nImage generated!";

        img.savePPM("output/out.ppm");
    }

private:
    float fov; // rad
    const Scene& scene;
    Image<ColorRGBA> img;

    Vec3f refract(const Vec3f& incident, const Vec3f& normal, float matRefraction) {
        Vec3f n = normal;
        float n1 = RefractionCoefficient::empty; //etai
        float n2 = matRefraction; // etat

        float c = gmtl::dot(normal, incident);
        if (c > 0.0f) {// from filled to empty medium
            std::swap(n1, n2);
            n *= -1;
        }
        else {
            c *= -1;
        }
        float r = n1/n2;
        float k = 1 - r * r * (1 - c*c);
        return k < 0 ? Vec3f(0, 0, 0) : r*incident + n*(r*c - sqrtf(k));
    }

    ColorRGBA cast_ray(const Rayf& ray, int depth = 0) {
        static const int MAX_DEPTH = 7;
        if (depth > MAX_DEPTH) {
            return ColorRGBA::black;
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
            const Material& mat = nearObj->material;
            for (auto light_it = scene.getLights().begin(); light_it != scene.getLights().end(); ++light_it) {
                const Light &light = *(*light_it);
                Vec3f lDir = light.centre - nearCollision.hitPoint;
                float lDistance = gmtl::length(lDir);
                gmtl::normalize(lDir);
                gmtl::reflect(reflection, ray.getDir(), normal);
                gmtl::normalize(reflection);
                float lightAttenuation = light.getRadius()/(lDistance*lDistance);
                ColorRGBA cEmission = mat.kEmission * mat.color;
                float diffuse = mat.kDiffuse * std::max(gmtl::dot(normal, lDir), 0.25f);
                ColorRGBA cDif = diffuse * lightAttenuation * mat.color * light.color;
                reflection *= -1;
                float specular = mat.kSpecular * powf(std::max(gmtl::dot(ray.getDir(), reflection), 0.0f), mat.specularPower);
                ColorRGBA cSpec = specular * lightAttenuation * light.color;
                reflection *= -1;
                float fresnel = mat.kFresnel * powf(std::max(gmtl::dot(ray.getDir(), reflection), 0.0f), mat.fresnelPower);
                ColorRGBA cFres = fresnel * lightAttenuation * light.color;
                pixel += cEmission + cDif + cSpec + cFres;
            }
            Vec3f refraction = refract(ray.getDir(), normal, mat.matRefraction);
            gmtl::normalize(refraction);
            Vec3f reflectionOffset = normal * 0.001f * gmtl::dot(reflection, normal);
            Vec3f refractionOffset = normal * 0.001f * gmtl::dot(refraction, normal);
            return pixel + 0.85f
                   * ( mat.kReflection * cast_ray(Rayf(nearCollision.hitPoint + reflectionOffset, reflection), depth + 1)
                     + mat.kRefraction * cast_ray(Rayf(nearCollision.hitPoint + refractionOffset, refraction), depth + 1)
                     );
        }

        return depth == 0 ? img.getBackgroundColor() : ColorRGBA::black;
    }
};