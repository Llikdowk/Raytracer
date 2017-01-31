#include "Scene.h"
#include "Raytracer.h"

int main() {
    Scene scene;
    scene.addObject(new Sphere(0, 0, -2, 1, ColorRGBA::black))
         .addObject(new Sphere(0, 0, 2, 1, ColorRGBA::magenta))
         .addObject(new Sphere(-1.25f, 1, -2, 0.5f, Material(ColorRGBA::blue)))
         .addObject(new Sphere(1, 1, -2, 0.75f, Material(ColorRGBA::green)))
         .addObject(new Sphere(1.5f, -.25f, -1.5f, 0.5, Material(ColorRGBA::red)))
         .addLight(new Light(1, 1, 0, ColorRGBA::white))
         .addLight(new Light(-3, -3, 0))
    ;

    Raytracer raytracer(scene, 1366, 768, 90);
    raytracer.run();
    return 0;
}