#include "pch.h"
#include "StripePattern.h"
#include "SolidColorPattern.h"

TEST(StripePatternTests, patternAt) {
    StripePattern pattern;
    EXPECT_EQ(pattern.patternAt(Point(-1.1, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(-0.1, 0, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0, 1, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0, 2, 3)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0.9, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1, 0, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(2, 0, -3)), Color::white);

    StripePattern pattern_2(SolidColorPattern(Color(1, 0, 0)), SolidColorPattern(Color(0, 1, 0)));
    EXPECT_EQ(pattern_2.patternAt(Point(0, 0, 0)), Color::red);
    EXPECT_EQ(pattern_2.patternAt(Point(1, 0, 0)), Color::green);
}
