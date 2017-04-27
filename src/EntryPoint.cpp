#include "Scene.h"
#include "Raytracer.h"

int main() {

    Scene scene;
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
    sphereMat.kSpecular = 0.1f;
    sphereMat.specularPower = 1.0f;
    sphereMat.kRefraction = 0.65f;
    sphereMat.kReflection = 0.35f;
    sphereMat.kFresnel = 0.5f;
    sphereMat.color = ColorRGB::red;
    Sphere* sphere = new Sphere(-0.25f, 0.45f, -1.0f, 1.0f);
    sphere->material = sphereMat;

    Material opaqueMat;
    opaqueMat.kEmission = 0.25f;
    opaqueMat.kDiffuse = 0.5f;
    opaqueMat.kSpecular = 0.1f;
    opaqueMat.specularPower = 1.0f;
    opaqueMat.kFresnel = 0.1f;
    opaqueMat.kRefraction = 0.5f;
    opaqueMat.kReflection = 0.05;
    opaqueMat.color = ColorRGB::white;
    Sphere* matSphere = new Sphere(0.0f, -0.35f, -0.10f, 0.25f);
    matSphere->material = opaqueMat;

    Light* light = new Light(-1, 1, 0);
    light->setRadius(5.0f);
    light->color = ColorRGB::green;
    Light* light2 = new Light(1, 1, 0);
    light2->color = ColorRGB::blue;
    light2->setRadius(5.0f);
    Light* centralLight = new Light(0, 2, 0);
    centralLight->setRadius(15.0f);

    scene.addObject(plane)
            .addObject(sphere)
            .addObject(new Sphere(1.25, 0.25, -1.5f, 0.75f, ColorRGB::cyan))
            .addObject(new Sphere(-2.1f, 0.5, -2.7f, 1.5f, ColorRGB::green))
            .addObject(matSphere)
            .addLight(light2)
            .addLight(light)
            .addLight(centralLight);


    Raytracer raytracer(scene, 1366, 768, 90, ColorRGB::black);//ColorRGB(0.0, 0.0, 0.0));
    //Raytracer raytracer(scene, 640, 360, 90, ColorRGB(0.0, 0.0, 0.0));
    raytracer.run();
    return 0;

}