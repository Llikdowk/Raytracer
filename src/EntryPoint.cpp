#include "Scene.h"
#include "Raytracer.h"

int main() {

    Scene scene;
/*
    Material opaqueMat;
    opaqueMat.kRefraction = 0.1f;
    opaqueMat.kReflection = 0.05f;
    opaqueMat.kSpecular = 0.025f;
    opaqueMat.specularPower = 1.0f;
    opaqueMat.kFresnel = 0.15f;
    opaqueMat.color = ColorRGB::black;
    Sphere* opaqueSphere = new Sphere(0.20, -0.4f, 0.25f, 0.12);
    opaqueSphere->material = opaqueMat;

    Material planeMat;
    planeMat.kReflection = 0.25f;
    planeMat.kRefraction = 0.75f;
    planeMat.kSpecular = 0.0f;
    planeMat.specularPower = 0.0f;
    planeMat.kFresnel = 0.0f;
    planeMat.kDiffuse = 0.6f;
    planeMat.kEmission = 0.01f;
    planeMat.color = ColorRGB::white;
    Plane* plane = new Plane(0.0f, -1.5f, 0.0f, 0,1,0);
    plane->material = planeMat;


    scene.addObject(new Sphere(0.0, -0.25f, -1.0f, 1.0f, ColorRGB(0.0,0.25,0.25)))
         .addObject(new Sphere(-1.5f, 0, -2.5f, 1.5f, ColorRGB::magenta))
         .addObject(new Sphere(0.25f, -0.5f, 2.5, 1.0f, ColorRGB::yellow))
         .addObject(new Sphere(2.5, 0.15, -2.5f, 1.5, ColorRGB::green))
         .addObject(new Sphere(0.3, 0.2, 0.2f, 0.25f, Material(ColorRGB::red)))
         .addObject(opaqueSphere)
         .addObject(plane)
         .addLight((new Light(-0.5f, 1.5f, 0, ColorRGB::white))->setRadius(15.0f))
         .addLight((new Light(0.5, 1, 0, ColorRGB::cyan)))
    ;
*/


    Material planeMat;

    planeMat.kReflection = 0.0f;
    planeMat.kRefraction = 0.0f;
    planeMat.kSpecular = 0.5f;
    planeMat.specularPower = 10.0f;
    planeMat.kFresnel = 0.0f;
    planeMat.kDiffuse = 0.75f;
    planeMat.kEmission = 0.01f;
    planeMat.color = ColorRGB::white;
    Plane* plane = new Plane(0.0f, -1.5f, 0.0f, 0,1,0);
    plane->material = planeMat;

    Material sphereMat;
    sphereMat.kEmission = 0.1f;
    sphereMat.kDiffuse = 1.0f;
    sphereMat.kSpecular = 1.0f;
    sphereMat.specularPower = 10.0f;
    sphereMat.kRefraction = 0.65f;
    sphereMat.kReflection = 0.35f;
    sphereMat.kFresnel = 0.5f;
    sphereMat.color = ColorRGB::red;
    Sphere* sphere = new Sphere(-0.25f, 0.0f, -1.0f, 1.0f);
    sphere->material = sphereMat;


    Light* light = new Light(0.0, 2.0, 0.0);
    light->setRadius(35.0f);
    Light* light2 = new Light(1, 1, 0);
    light2->color = ColorRGB::cyan;

    scene.addObject(plane)
            .addObject(sphere)
            .addObject(new Sphere(1.25, 0, -1.5f, 0.75f, ColorRGB::cyan))
            .addObject(new Sphere(-2.0f, 0.5, -2.75f, 1.5f, ColorRGB::green))
            //.addLight(light2)
            .addLight(light);


    Raytracer raytracer(scene, 1366, 768, 90, ColorRGB::black);//ColorRGB(0.0, 0.0, 0.0));
    //Raytracer raytracer(scene, 640, 360, 90, ColorRGB(0.0, 0.0, 0.0));
    raytracer.run();
    return 0;

}