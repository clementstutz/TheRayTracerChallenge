#include "pch.h"
#include "Color.h"

TEST(ColorTests, constructor_default) {
	Color c1;
	EXPECT_FLOAT_EQ(c1.getR(), 0.0f);
	EXPECT_FLOAT_EQ(c1.getG(), 0.0f);
	EXPECT_FLOAT_EQ(c1.getB(), 0.0f);
}

TEST(ColorTests, constructor_values) {
	Color c1(1.0f);
	EXPECT_FLOAT_EQ(c1.getR(), 1.0f);
	EXPECT_FLOAT_EQ(c1.getG(), 0.0f);
	EXPECT_FLOAT_EQ(c1.getB(), 0.0f);

	Color c2(1.0f, 2.0f);
	EXPECT_FLOAT_EQ(c2.getR(), 1.0f);
	EXPECT_FLOAT_EQ(c2.getG(), 2.0f);
	EXPECT_FLOAT_EQ(c2.getB(), 0.0f);

	Color c3(1.0f, 2.0f, 3.0f);
	EXPECT_FLOAT_EQ(c3.getR(), 1.0f);
	EXPECT_FLOAT_EQ(c3.getG(), 2.0f);
	EXPECT_FLOAT_EQ(c3.getB(), 3.0f);
}

TEST(ColorTests, constructor_copy) {
	Color c1(1.0f, 2.0f, 3.0f);
	Color c2(c1);
	EXPECT_FLOAT_EQ(c2.getR(), 1.0f);
	EXPECT_FLOAT_EQ(c2.getG(), 2.0f);
	EXPECT_FLOAT_EQ(c2.getB(), 3.0f);
}

TEST(ColorTests, constructor_move) {
	Color c2(Color(1.0f, 2.0f, 3.0f));
	EXPECT_FLOAT_EQ(c2.getR(), 1.0f);
	EXPECT_FLOAT_EQ(c2.getG(), 2.0f);
	EXPECT_FLOAT_EQ(c2.getB(), 3.0f);
}

TEST(ColorTests, affectation_copy) {
	Color c1(1.0f, 2.0f, 3.0f);
	Color c2;
	c2 = c1;
	EXPECT_FLOAT_EQ(c2.getR(), 1.0f);
	EXPECT_FLOAT_EQ(c2.getG(), 2.0f);
	EXPECT_FLOAT_EQ(c2.getB(), 3.0f);
}

TEST(ColorTests, affectation_move) {
	Color c1(1.0f, 2.0f, 3.0f);
	Color c2;
	c2 = std::move(c1);
	EXPECT_FLOAT_EQ(c2.getR(), 1.0f);
	EXPECT_FLOAT_EQ(c2.getG(), 2.0f);
	EXPECT_FLOAT_EQ(c2.getB(), 3.0f);
}

TEST(ColorTests, equality) {
	Color c1(1.0f, 2.0f, 3.0f);
	Color c2(1.0f, 2.0f, 3.0f);
	Color c3(3.0f, 2.0f, 1.0f);

	EXPECT_TRUE(c1 == c1);
	EXPECT_FALSE(c1 != c1);
	EXPECT_TRUE(c1 == c2);
	EXPECT_FALSE(c1 != c2);
	EXPECT_TRUE(c1 != c3);
	EXPECT_FALSE(c1 == c3);
}

TEST(ColorTests, add_two_Colors) {
	Color c1(1, 2.5, 3);
	Color c2(4, -2.5, 2);
	Color ref1(5, 0, 5);
	c1 += c2;
	EXPECT_TRUE(c1 == ref1);

	Color c3(-7, 0, 3);
	Color c4(2, -1, 8);
	Color ref2(-5, -1, 11);
	Color c5 = c3 + c4;
	EXPECT_TRUE(c5 == ref2);
}

TEST(ColorTests, substract_two_Colors) {
	Color c1(1, 2.5, 3);
	Color c2(4, -2.5, 2);
	Color ref1(-3, 5, 1);
	c1 -= c2;
	EXPECT_TRUE(c1 == ref1);

	Color c3(-7, 0, 3);
	Color c4(2, -1, 8);
	Color ref2(-9, 1, -5);
	Color c5 = c3 - c4;
	EXPECT_TRUE(c5 == ref2);
}

TEST(ColorTests, negate_Color) {
	Color c1(10, -5, -4);
	Color c2(-10, 5, 4);
	EXPECT_TRUE(c2 == -c1);
}

TEST(ColorTests, scalar_multiplication) {
	float s1 = 2.0f;
	float s2 = 0.25f;
	Color c1(1.0f, 2.0f, 3.0f);
	Color ref1(2.0f, 4.0f, 6.0f);
	Color c2 = c1 * s1;

	EXPECT_TRUE(c2 == ref1);
	EXPECT_FLOAT_EQ(c2.getR(), ref1.getR());
	EXPECT_FLOAT_EQ(c2.getG(), ref1.getG());
	EXPECT_FLOAT_EQ(c2.getB(), ref1.getB());

	Color c3 = s2 * c2;
	Color ref2(0.5f, 1.0f, 1.5f);
	EXPECT_TRUE(c3 == ref2);
	EXPECT_FLOAT_EQ(c3.getR(), ref2.getR());
	EXPECT_FLOAT_EQ(c3.getG(), ref2.getG());
	EXPECT_FLOAT_EQ(c3.getB(), ref2.getB());

	c1 *= s1;
	EXPECT_TRUE(c1 == ref1);
	EXPECT_FLOAT_EQ(c1.getR(), ref1.getR());
	EXPECT_FLOAT_EQ(c1.getG(), ref1.getG());
	EXPECT_FLOAT_EQ(c1.getB(), ref1.getB());

	c2 *= s2;
	EXPECT_TRUE(c2 == ref2);
	EXPECT_FLOAT_EQ(c2.getR(), ref2.getR());
	EXPECT_FLOAT_EQ(c2.getG(), ref2.getG());
	EXPECT_FLOAT_EQ(c2.getB(), ref2.getB());
}

TEST(ColorTests, multiply_two_colors) {
	Color c1(1.0f, 2.0f, 3.0f);
	Color c2(2.0f, 4.0f, 5.0f);
	Color ref1(2.0f, 8.0f, 15.0f);
	Color c3 = c1 * c2;

	EXPECT_TRUE(c3 == ref1);
	EXPECT_FLOAT_EQ(c3.getR(), ref1.getR());
	EXPECT_FLOAT_EQ(c3.getG(), ref1.getG());
	EXPECT_FLOAT_EQ(c3.getB(), ref1.getB());

	c1 *= c2;
	EXPECT_TRUE(c3 == c1);
	EXPECT_FLOAT_EQ(c3.getR(), c1.getR());
	EXPECT_FLOAT_EQ(c3.getG(), c1.getG());
	EXPECT_FLOAT_EQ(c3.getB(), c1.getB());
}

TEST(ColorTests, static_colors) {
	Color ref_red(1.0f, 0.0f, 0.0f);
	EXPECT_EQ(Color::red, ref_red);

	Color ref_green(0.0f, 1.0f, 0.0f);
	EXPECT_EQ(Color::green, ref_green);

	Color ref_blue(0.0f, 0.0f, 1.0f);
	EXPECT_EQ(Color::blue, ref_blue);

	Color ref_cyan(0.0f, 1.0f, 1.0f);
	EXPECT_EQ(Color::cyan, ref_cyan);

	Color ref_magenta(1.0f, 0.0f, 1.0f);
	EXPECT_EQ(Color::magenta, ref_magenta);

	Color ref_yellow(1.0f, 1.0f, 0.0f);
	EXPECT_EQ(Color::yellow, ref_yellow);

	Color ref_white(1.0f, 1.0f, 1.0f);
	EXPECT_EQ(Color::white, ref_white);

	Color ref_grey(0.5f, 0.5f, 0.5f);
	EXPECT_EQ(Color::grey, ref_grey);

	Color ref_black(0.0f, 0.0f, 0.0f);
	EXPECT_EQ(Color::black, ref_black);
}
