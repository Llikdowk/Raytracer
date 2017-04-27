#pragma once
#include "Image.h"
#include "Scene.h"
#include "MyMath.h"
#include "Color.h"
#include <iomanip>
#include <chrono>

#include <gmtl/gmtl.h>
#include <omp.h>
#include <algorithm>

using gmtl::Vec3f;
using gmtl::Rayf;
using gmtl::Point3f;
using gmtl::Matrix44f;


class Raytracer {
public:

    Raytracer(const Scene& scene, int width, int height, float fov_angle, ColorRGB baseColor)
            : scene(scene), fov(deg2rad(fov_angle)), img(width, height, baseColor)
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
                camera_to_world[1][3] = 0.25f; // y
                camera_to_world[2][3] = 1.0f; // z
                ray = camera_to_world * ray;
                img[i][j] = cast_ray(ray);
            }
            #pragma omp atomic
            progress += step;

            //if (omp_get_thread_num() == 0) {
                std::cout << "\r" << progress * 100.0f << "%                         ";
            //}

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
    Image<ColorRGB> img;

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

    ColorRGB cast_ray(const Rayf& ray, const Object* const lastObject = nullptr, int depth = 0) {
        static const float bias = 1E-5f;
        static const int MAX_DEPTH = 2;
        if (depth > MAX_DEPTH) {
            return ColorRGB::white;//ColorRGB::black;
        }

        float nearDistance = 10e9f;
        const Object* nearObj = nullptr;
        Collision nearCollision;
        for (auto it = scene.getObjects().begin(); it != scene.getObjects().end(); ++it) {
            const Object& obj = *(*it);
            if (lastObject == &obj) continue;
            Collision collision = obj.checkCollision(ray);
            if (collision.hasCollided && collision.distance < nearDistance) {
                nearDistance = collision.distance;
                nearObj = &obj;
                nearCollision = collision;
            }
        }
        if (nearObj != nullptr) {
            ColorRGB pixel = ColorRGB::black;
            Vec3f normal = nearObj->getNormal(nearCollision.hitPoint);
            const Material& mat = nearObj->material;

            ColorRGB reflectionColor = ColorRGB::black;
            ColorRGB cEmission = mat.kEmission * mat.color;
            ColorRGB cDiffuse = ColorRGB::black;
            ColorRGB cSpecular = ColorRGB::black;
            ColorRGB cFresnel = ColorRGB::black;
            for (auto light_it = scene.getLights().begin(); light_it != scene.getLights().end(); ++light_it) {
                const Light &light = *(*light_it);
                Vec3f lDir = light.centre - nearCollision.hitPoint;
                float lDistance = gmtl::length(lDir);
                gmtl::normalize(lDir);
                float shadowing = 1.0f;


                Rayf lightRay = Rayf(nearCollision.hitPoint, lDir);
                for (auto it = scene.getObjects().begin(); it != scene.getObjects().end(); ++it) {
                    const Object &obj = *(*it);
                    if (&obj == nearObj) continue;
                    Collision collision = obj.checkCollision(lightRay);
                    if (collision.hasCollided) {
                        shadowing *= 0.25f;
                        //break;
                    }
                }

                float lightAttenuation = light.getRadius() / (lDistance * lDistance) * shadowing;
                float diffuse = mat.kDiffuse * std::max(gmtl::dot(normal, lDir), 0.25f);
                cDiffuse += diffuse * lightAttenuation * mat.color * light.color;
                Vec3f reflection;
                gmtl::reflect(reflection, Vec3f(-lDir), normal);
                float specular = mat.kSpecular * powf(std::max(gmtl::dot(-ray.getDir(), reflection), 0.0f), mat.specularPower);
                cSpecular += specular * lightAttenuation * light.color;
                float fresnel = mat.kFresnel * powf(std::max(1 - gmtl::dot(-ray.getDir(), normal), 0.0f), mat.fresnelPower);
                cFresnel += fresnel * lightAttenuation * light.color;

                if (mat.kReflection > 0) {
                    //pixel += cEmission + cDif;// + cSpec + cFres;
                    reflectionColor += mat.kReflection *
                                       cast_ray(Rayf(nearCollision.hitPoint + Vec3f(normal * bias), reflection),
                                                nullptr, depth + 1);
                }
            }
            ColorRGB refractionColor = ColorRGB::black;
            if (mat.kRefraction > 0) {
                Vec3f refraction = refract(ray.getDir(), normal, mat.matRefraction);
                gmtl::normalize(refraction);
                float refractionSign = gmtl::dot(refraction, normal) >= 0 ? 1.0f : -1.0f;
                Vec3f refractionOffset = normal * 0.001f * refractionSign;
                refractionColor += mat.kRefraction * cast_ray(Rayf(nearCollision.hitPoint + Vec3f(refractionSign*normal*bias), refraction), nullptr, depth + 1);
            }

            if (mat.kRefraction == 0 && mat.kReflection == 0) {
                pixel = cEmission + cDiffuse;
            } else {
                pixel = cEmission + (cFresnel + cSpecular) * reflectionColor + cDiffuse * refractionColor;
            }

            return pixel;
        }

        return depth == 0 ? img.getBackgroundColor() : ColorRGB::white;//ColorRGB::black;
    }
};