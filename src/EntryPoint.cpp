#include "Scene.h"
#include "Raytracer.h"

int main() {
    Scene scene;
    Material opaqueMat;
    opaqueMat.kRefraction = 0.1f;
    opaqueMat.kReflection = 0.05f;
    opaqueMat.kSpecular = 0.025f;
    opaqueMat.specularPower = 1.0f;
    opaqueMat.kFresnel = 0.15f;
    opaqueMat.color = ColorRGBA::black;
    Sphere* opaqueSphere = new Sphere(0.20, -0.4f, 0.25f, 0.12);
    opaqueSphere->material = opaqueMat;


    scene.addObject(new Sphere(0.0, -0.25f, -1.0f, 1.0f, ColorRGBA(0.0,0.25,0.25)))
         .addObject(new Sphere(-1.5f, 0, -2.5f, 1.5f, ColorRGBA::magenta))
         .addObject(new Sphere(0.25f, -0.5f, 2.5, 1.0f, ColorRGBA::yellow))
         .addObject(new Sphere(2.5, 0.15, -2.5f, 1.5, ColorRGBA::green))
         .addObject(new Sphere(0.3, 0.2, 0.2f, 0.25f, Material(ColorRGBA::red)))
         .addObject(opaqueSphere)
         .addLight((new Light(-0.5f, -0.5f, 0, ColorRGBA::white))->setRadius(2.0f))
         .addLight((new Light(0.5, 1, 0, ColorRGBA::cyan)))
    ;

    Raytracer raytracer(scene, 1366, 768, 90);
    raytracer.run();
    return 0;
}