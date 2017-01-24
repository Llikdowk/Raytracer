#include "Image.h"
#include "Color.h"

int main() {
    Image<640, 480> img;
    std::cout << (int)img[4][4].r << std::endl;
    std::cout << (int)img[639][479].r << std::endl;

    return 0;
}