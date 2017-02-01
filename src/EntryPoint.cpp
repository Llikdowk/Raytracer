#include "Scene.h"
#include "Raytracer.h"

int main() {
    Scene scene;
    Sphere* black = new Sphere(0.75, 0.35, -1, 0.45f, ColorRGBA::black);
    black->material.kSpecular = 0;
    black->material.kFresnel = 0.20;

    scene.addObject(new Sphere(0, 0, -2, 1, ColorRGBA::red))
         .addObject(black)
         .addObject(new Sphere(0, 0, 2, 1, ColorRGBA::magenta))
         .addObject(new Sphere(-0.5f, 1.2, -2, 0.5f, Material(ColorRGBA::blue)))
         .addObject(new Sphere(1, 1, -2, 0.75f, Material(ColorRGBA::green)))
         .addObject(new Sphere(1.5f, -.25f, -1.5f, 0.5, Material(ColorRGBA::yellow)))
         .addLight(new Light(1, 1, 0, ColorRGBA::white))
         .addLight(new Light(-2, -2, 0, ColorRGBA::cyan))
    ;

    Raytracer raytracer(scene, 800, 600, 90);
    raytracer.run();
    return 0;
}