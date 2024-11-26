#include "pch.h"
#include "Save.h"
#include "Canvas.h"

TEST(SaveTests, saveCanvas) {
    Canvas c1(10, 2, Color::red);

    // Modification de quelques pixels
    c1.setPixel(0, 0, Color::red);
    c1.setPixel(1, 0, Color::green);
    c1.setPixel(2, 0, Color::blue);
    c1.setPixel(0, 1, Color::yellow);
    c1.setPixel(1, 1, Color::magenta);
    c1.setPixel(2, 1, Color::cyan);

    Save::saveCanvas(c1, "save_test");
}
