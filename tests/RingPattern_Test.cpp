#include "pch.h"
#include "RingPattern.h"
#include "SolidColorPattern.h"

TEST(RingPatternTests, patternAt) {
    RingPattern pattern;
    EXPECT_EQ(pattern.patternAt(Point(-1.9, 0, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(-1, 0, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(-0.9, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0.9, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1, 0, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(1.9, 0, 0)), Color::black);

    EXPECT_EQ(pattern.patternAt(Point(0, 0, -1.9)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, -1)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, -0.9)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 0.9)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 1)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 1.9)), Color::black);

    EXPECT_EQ(pattern.patternAt(Point(-1.708, 0, -1.708)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(-1, 0, -1)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(-0.708, 0, -0.708)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(-0.707, 0, -0.707)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0.707, 0, 0.707)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0.708, 0, 0.708)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(1, 0, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(1.708, 0, 1.708)), Color::white);

    RingPattern pattern_2(SolidColorPattern(Color(1, 0, 0)), SolidColorPattern(Color(0, 1, 0)));
    EXPECT_EQ(pattern_2.patternAt(Point(0, 0, 0)), Color::red);
    EXPECT_EQ(pattern_2.patternAt(Point(1, 0, 0)), Color::green);

}
