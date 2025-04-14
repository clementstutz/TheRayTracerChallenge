#include "pch.h"
#include "CheckersPattern.h"
#include "SolidColorPattern.h"

TEST(CheckersPatternTests, patternAt) {
    CheckersPattern pattern;
    EXPECT_EQ(pattern.patternAt(Point(-0.1, 0, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(-0.99, 0, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(-0.99, 0.99, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(-0.1, 0.99, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(-0.1, 0, 0.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(-0.99, 0, 0.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(-0.99, 0.99, 0.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(-0.1, 0.99, 0.99)), Color::black);

    EXPECT_EQ(pattern.patternAt(Point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 0.99, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0, 0.99, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 0.99)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 0, 0.99)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 0.99, 0.99)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0, 0.99, 0.99)), Color::white);

    EXPECT_EQ(pattern.patternAt(Point(1, 0, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(1.99, 0, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(1.99, 0.99, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(1, 0.99, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(1, 0, 0.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(1.99, 0, 0.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(1.99, 0.99, 0.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(1, 0.99, 0.99)), Color::black);

    EXPECT_EQ(pattern.patternAt(Point(0, 1, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 1, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 1.99, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0, 1.99, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0, 1, 0.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 1, 0.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 1.99, 0.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0, 1.99, 0.99)), Color::black);

    EXPECT_EQ(pattern.patternAt(Point(0, 0, 1)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 0, 1)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 0.99, 1)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0, 0.99, 1)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 1.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 0, 1.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0.99, 0.99, 1.99)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(0, 0.99, 1.99)), Color::black);

    EXPECT_EQ(pattern.patternAt(Point(1, 0, 1)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1.99, 0, 1)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1.99, 0.99, 1)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1, 0.99, 1)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1, 0, 1.99)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1.99, 0, 1.99)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1.99, 0.99, 1.99)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1, 0.99, 1.99)), Color::white);

    CheckersPattern pattern_2(SolidColorPattern(Color(1, 0, 0)), SolidColorPattern(Color(0, 1, 0)));
    EXPECT_EQ(pattern_2.patternAt(Point(0, 0, 0)), Color::red);
    EXPECT_EQ(pattern_2.patternAt(Point(1, 0, 0)), Color::green);
}
