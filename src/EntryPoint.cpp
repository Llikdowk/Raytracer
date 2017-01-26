#include "Image.h"
#include "Color.h"
#include <cmath>
#include <gmtl/Vec.h>

struct Coordinates {
    float x, y, z;
};

struct Object {
    float x, y, z;
};

struct Sphere : public Object {
    float r;
    gmtl::Vec3f f;
};

void raytracer() {
    Image<640, 480> img(Color::green);
    float fov = 90.0f;

    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            Coordinates world {
                (2*i/img.widthf - 1) * img.aspect_ratio,
                (-2*j/img.heightf +  1) * tanf(fov/2.0f),
                -1
            };
            // castray
            // check intersection
            //     if true: shade
        }
    }

    img.savePPM("output/out.ppm");
}

int main() {
    raytracer();
    return 0;
}