#include "pch.h"
#include "GradientPattern.h"
#include "SolidColorPattern.h"

TEST(GradientPatternTests, patternAt) {
    GradientPattern pattern;
    EXPECT_EQ(pattern.patternAt(Point(-1.1, 0, 0)), Color(0.1, 0.1, 0.1));
    EXPECT_EQ(pattern.patternAt(Point(-0.99, 0, 0)), Color(0.99, 0.99, 0.99));
    EXPECT_EQ(pattern.patternAt(Point(-0.1, 0, 0)), Color(0.1, 0.1, 0.1));
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0.999, 0, 0)), Color(0.001, 0.001, 0.001));
    EXPECT_EQ(pattern.patternAt(Point(1, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1.1, 0, 0)), Color(0.9, 0.9, 0.9));

    GradientPattern pattern_2(SolidColorPattern(Color(1, 0, 0)), SolidColorPattern(Color(0, 1, 0)));
    EXPECT_EQ(pattern_2.patternAt(Point(-0.1, 0, 0)), Color(0.1, 0.9, 0));
    EXPECT_EQ(pattern_2.patternAt(Point(0, 0, 0)), Color::red);
}
