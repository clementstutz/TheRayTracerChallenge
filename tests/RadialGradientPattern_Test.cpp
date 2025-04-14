#include "pch.h"
#include "RadialGradientPattern.h"
#include "SolidColorPattern.h"

TEST(RadialGradientPatternTests, patternAt) {
    RadialGradientPattern pattern;
    EXPECT_EQ(pattern.patternAt(Point(-1.9, 0, 0)), Color(0.1, 0.1, 0.1));
    EXPECT_EQ(pattern.patternAt(Point(-1.1, 0, 0)), Color(0.9, 0.9, 0.9));
    EXPECT_EQ(pattern.patternAt(Point(-1, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(-0.9, 0, 0)), Color(0.1, 0.1, 0.1));
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0.9, 0, 0)), Color(0.1, 0.1, 0.1));
    EXPECT_EQ(pattern.patternAt(Point(1, 0, 0)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1.1, 0, 0)), Color(0.9, 0.9, 0.9));
    EXPECT_EQ(pattern.patternAt(Point(1.9, 0, 0)), Color(0.1, 0.1, 0.1));

    EXPECT_EQ(pattern.patternAt(Point(0, 0, -1.9)), Color(0.1, 0.1, 0.1));
    EXPECT_EQ(pattern.patternAt(Point(0, 0, -1)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, -0.9)), Color(0.1, 0.1, 0.1));
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 0.9)), Color(0.1, 0.1, 0.1));
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 1)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 1.9)), Color(0.1, 0.1, 0.1));

    EXPECT_EQ(pattern.patternAt(Point(-1.708, 0, -1.708)), Color(0.5845232354, 0.5845232354, 0.5845232354));
    EXPECT_EQ(pattern.patternAt(Point(-1, 0, -1)), Color(0.5857864376, 0.5857864376, 0.5857864376));
    EXPECT_EQ(pattern.patternAt(Point(-0.708, 0, -0.708)), Color(0.9987367978, 0.9987367978, 0.9987367978));
    EXPECT_EQ(pattern.patternAt(Point(-0.707, 0, -0.707)), Color(0.0001510114, 0.0001510114, 0.0001510114));
    EXPECT_EQ(pattern.patternAt(Point(0.707, 0, 0.707)), Color(0.0001510114, 0.0001510114, 0.0001510114));
    EXPECT_EQ(pattern.patternAt(Point(0.708, 0, 0.708)), Color(0.9987367978, 0.9987367978, 0.9987367978));
    EXPECT_EQ(pattern.patternAt(Point(1.708, 0, 1.708)), Color(0.5845232354, 0.5845232354, 0.5845232354));

    RadialGradientPattern pattern_2(SolidColorPattern(Color(1, 0, 0)), SolidColorPattern(Color(0, 1, 0)));
    EXPECT_EQ(pattern_2.patternAt(Point(-0.1, 0, 0)), Color(0.9, 0.1, 0));
    EXPECT_EQ(pattern_2.patternAt(Point(0, 0, 0)), Color::red);
}
