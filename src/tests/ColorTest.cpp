
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
