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
    opaqueMat.color = ColorRGB::black;
    Sphere* opaqueSphere = new Sphere(0.20, -0.4f, 0.25f, 0.12);
    opaqueSphere->material = opaqueMat;


    scene.addObject(new Sphere(0.0, -0.25f, -1.0f, 1.0f, ColorRGB(0.0,0.25,0.25)))
         .addObject(new Sphere(-1.5f, 0, -2.5f, 1.5f, ColorRGB::magenta))
         .addObject(new Sphere(0.25f, -0.5f, 2.5, 1.0f, ColorRGB::yellow))
         .addObject(new Sphere(2.5, 0.15, -2.5f, 1.5, ColorRGB::green))
         .addObject(new Sphere(0.3, 0.2, 0.2f, 0.25f, Material(ColorRGB::red)))
         .addObject(opaqueSphere)
         .addLight((new Light(-0.5f, -0.5f, 0, ColorRGB::white))->setRadius(2.0f))
         .addLight((new Light(0.5, 1, 0, ColorRGB::cyan)))
    ;

    //Raytracer raytracer(scene, 1366, 768, 90);
    Raytracer raytracer(scene, 300, 200, 90);
    raytracer.run();
    return 0;
}