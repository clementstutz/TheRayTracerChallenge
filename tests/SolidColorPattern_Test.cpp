#include "pch.h"
#include "SolidColorPattern.h"


TEST(SolidColorPatternTests, patternAt) {
    SolidColorPattern pattern_1;
    EXPECT_EQ(pattern_1.patternAt(Point(0, 0, 0)), Color::black);

    SolidColorPattern pattern_2(Color::red);
    EXPECT_EQ(pattern_2.patternAt(Point(0, 0, 0)), Color::red);
}
