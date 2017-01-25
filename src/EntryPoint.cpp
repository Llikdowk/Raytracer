#include "Image.h"
#include "Color.h"

int main() {
    Image<4, 4> img(Color::magenta);
    img[2][2] = Color::black;
    img.savePPM("output/example.ppm");

    return 0;
}