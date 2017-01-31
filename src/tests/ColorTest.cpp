
#include "Color.h"
#include <gtest/gtest.h>

TEST (ColorTest, creation) {
    ColorRGBA c = ColorRGBA::green;
    EXPECT_EQ(c, ColorRGBA::green);
}

TEST (ColorTest, kMul) {

    ColorRGBA b = ColorRGBA::black;
    ColorRGBA bb = 2*b;
    ColorRGBA bhalf = 0.5*b;
    EXPECT_EQ(bb, b);
    EXPECT_EQ(bhalf, ColorRGBA(0, 0, 0));

    b = ColorRGBA::white;
    bb = 2*b;
    bhalf = 0.5*b;
    EXPECT_EQ(bb, b);
    EXPECT_EQ(bhalf, ColorRGBA(0.5, 0.5, 0.5));
}

TEST (ColorTest, ColorMul) {
    ColorRGBA black = ColorRGBA::black;
    ColorRGBA white = ColorRGBA::white;
    EXPECT_EQ(black*white, ColorRGBA::black);
    ColorRGBA halfWhite = ColorRGBA(0.5, 0.5, 0.5, 0.5) * white;
    EXPECT_EQ(halfWhite, ColorRGBA(0.5, 0.5, 0.5, 0.5));
}

TEST (ColorTest, ColorAdd) {
    ColorRGBA black = ColorRGBA::black;
    ColorRGBA white = ColorRGBA::white;
    EXPECT_EQ(white + white, ColorRGBA::white);
    EXPECT_EQ(white + black, ColorRGBA::white);
    white += black;
    EXPECT_EQ(white, ColorRGBA::white);
}

TEST (ColorTest, ColorSub) {
    ColorRGBA black = ColorRGBA::black;
    ColorRGBA white = ColorRGBA::white;
    EXPECT_EQ(white - white, ColorRGBA(0,0,0,0));
    EXPECT_EQ(white - black, ColorRGBA(1,1,1,0));
    white -= black;
    EXPECT_EQ(white, ColorRGBA(1,1,1,0));
}
