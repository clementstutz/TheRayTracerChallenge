#include "pch.h"
#include "Canvas.h"

TEST(CanvasTests, constructor_surcharged) {
	Canvas c1(10, 20);
	EXPECT_EQ(c1.getWidth(), 10);
	EXPECT_EQ(c1.getHeight(), 20);

    for (int y = 0; y < c1.getHeight(); y++) {
        for (int x = 0; x < c1.getWidth(); x++) {
            EXPECT_EQ(Color::black, c1.getPixel(x, y));
        }
    }
}

TEST(CanvasTests, fillCanvas) {
    Canvas c1(10, 20);
    c1.fillCanvas(Color::green);

    for (int y = 0; y < c1.getHeight(); y++) {
        for (int x = 0; x < c1.getWidth(); x++) {
            EXPECT_EQ(Color::green, c1.getPixel(x, y));
        }
    }
}

TEST(CanvasTests, constructor_copy) {
    Canvas c1(10, 20);
    c1.fillCanvas(Color::green);
    Canvas c2(c1);
    EXPECT_EQ(c2.getWidth(), 10);
    EXPECT_EQ(c2.getHeight(), 20);

    for (int y = 0; y < c2.getHeight(); y++) {
        for (int x = 0; x < c2.getWidth(); x++) {
            EXPECT_EQ(Color::green, c2.getPixel(x, y));
        }
    }
}

TEST(CanvasTests, constructor_affectation) {
    Canvas c1(10, 20);
    c1.fillCanvas(Color::green);
    Canvas c2 = c1;
    EXPECT_EQ(c2.getWidth(), 10);
    EXPECT_EQ(c2.getHeight(), 20);

    for (int y = 0; y < c2.getHeight(); y++) {
        for (int x = 0; x < c2.getWidth(); x++) {
            EXPECT_EQ(Color::green, c2.getPixel(x, y));
        }
    }
}

TEST(CanvasTests, setPixel) {
    Canvas c1(2, 2);
    c1.setPixel(1, 1, Color::red);
    EXPECT_EQ(Color::black, c1.getPixel(0, 0));
    EXPECT_EQ(Color::black, c1.getPixel(0, 1));
    EXPECT_EQ(Color::black, c1.getPixel(1, 0));
    EXPECT_EQ(Color::red, c1.getPixel(1, 1));
}