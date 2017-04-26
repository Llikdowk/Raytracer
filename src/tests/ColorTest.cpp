
#include "Color.h"
#include <gtest/gtest.h>

TEST (ColorTest, creation) {
    ColorRGB c = ColorRGB::green;
    EXPECT_EQ(c, ColorRGB::green);
}

TEST (ColorTest, kMul) {

    ColorRGB b = ColorRGB::black;
    ColorRGB bb = 2*b;
    ColorRGB bhalf = 0.5*b;
    EXPECT_EQ(bb, b);
    EXPECT_EQ(bhalf, ColorRGB(0, 0, 0));

    b = ColorRGB::white;
    bb = 2*b;
    bhalf = 0.5*b;
    EXPECT_EQ(bb, b);
    EXPECT_EQ(bhalf, ColorRGB(0.5, 0.5, 0.5));
    
    EXPECT_EQ(ColorRGB::white * 1.0f, ColorRGB::white);
} 

TEST (ColorTest, ColorMul) {
    ColorRGB black = ColorRGB::black;
    ColorRGB white = ColorRGB::white;
    EXPECT_EQ(black*white, ColorRGB::black);
    ColorRGB halfWhite = ColorRGB(0.5, 0.5, 0.5, 0.5) * white;
    EXPECT_EQ(halfWhite, ColorRGB(0.5, 0.5, 0.5, 0.5));
}

TEST (ColorTest, ColorAdd) {
    ColorRGB black = ColorRGB::black;
    ColorRGB white = ColorRGB::white;
    EXPECT_EQ(white + white, ColorRGB::white);
    EXPECT_EQ(white + black, ColorRGB::white);
    white += black;
    EXPECT_EQ(white, ColorRGB::white);
}

TEST (ColorTest, ColorSub) {
    ColorRGB black = ColorRGB::black;
    ColorRGB white = ColorRGB::white;
    EXPECT_EQ(white - white, ColorRGB(0,0,0,0));
    EXPECT_EQ(white - black, ColorRGB(1,1,1,0));
    white -= black;
    EXPECT_EQ(white, ColorRGB(1,1,1,0));
}
