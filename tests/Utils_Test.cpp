#include "pch.h"
#include "Utils.h"

TEST(UtilsTests, FE) {
    float a = 1.0;
    float b = 2.0;
    float c = 2.0;

    EXPECT_TRUE(Utils::FE(a, a));
    EXPECT_FALSE(Utils::FE(a, b));
    EXPECT_TRUE(Utils::FE(b, c));

    a = 3.06162e-16;
    b = 0;
    EXPECT_TRUE(Utils::FE(a, b));

    a = 0;
    b = -0;
    EXPECT_TRUE(Utils::FE(a, b));

    a = 1.2;
    b = 1.202;
    EXPECT_FALSE(Utils::FE(a, b));

    a = 0.0f;
    b = 0.000000001f;
    EXPECT_TRUE(Utils::FE(a, b));
}