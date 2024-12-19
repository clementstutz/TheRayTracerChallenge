#include "pch.h"
#include "Point.h"
#include "Vector.h"
#include "Mat4.h"

TEST(PointTests, constructor_default) {
	Point p1;
	EXPECT_EQ(typeid(p1).name(), typeid(Point).name());
	EXPECT_FLOAT_EQ(p1.getX(), 0.0);
	EXPECT_FLOAT_EQ(p1.getY(), 0.0);
	EXPECT_FLOAT_EQ(p1.getZ(), 0.0);
	EXPECT_FLOAT_EQ(p1.getW(), 1.0);
}

TEST(PointTests, constructor_surcharged) {
	Point p1(1.0);
	EXPECT_EQ(typeid(p1).name(), typeid(Point).name());
	EXPECT_FLOAT_EQ(p1.getX(), 1.0);
	EXPECT_FLOAT_EQ(p1.getY(), 0.0);
	EXPECT_FLOAT_EQ(p1.getZ(), 0.0);
	EXPECT_FLOAT_EQ(p1.getW(), 1.0);

	Point p2(1.0, 2.0);
	EXPECT_EQ(typeid(p2).name(), typeid(Point).name());
	EXPECT_FLOAT_EQ(p2.getX(), 1.0);
	EXPECT_FLOAT_EQ(p2.getY(), 2.0);
	EXPECT_FLOAT_EQ(p2.getZ(), 0.0);
	EXPECT_FLOAT_EQ(p2.getW(), 1.0);

	Point p3(1.0, 2.0, 3.0);
	EXPECT_EQ(typeid(p3).name(), typeid(Point).name());
	EXPECT_FLOAT_EQ(p3.getX(), 1.0);
	EXPECT_FLOAT_EQ(p3.getY(), 2.0);
	EXPECT_FLOAT_EQ(p3.getZ(), 3.0);
	EXPECT_FLOAT_EQ(p3.getW(), 1.0);
}

TEST(PointTests, constructor_copy) {
	Point p1(1.0, 2.0, 3.0);
	Point p2(p1);
	EXPECT_EQ(typeid(p2).name(), typeid(Point).name());
	EXPECT_FLOAT_EQ(p2.getX(), 1.0);
	EXPECT_FLOAT_EQ(p2.getY(), 2.0);
	EXPECT_FLOAT_EQ(p2.getZ(), 3.0);
	EXPECT_FLOAT_EQ(p2.getW(), 1.0);
}

TEST(PointTests, constructor_moving) {
	Point p1;
	p1 = Point(1.0, 2.0, 3.0);
	EXPECT_EQ(typeid(p1).name(), typeid(Point).name());
	EXPECT_FLOAT_EQ(p1.getX(), 1.0);
	EXPECT_FLOAT_EQ(p1.getY(), 2.0);
	EXPECT_FLOAT_EQ(p1.getZ(), 3.0);
	EXPECT_FLOAT_EQ(p1.getW(), 1.0);
}

TEST(PointTests, assignment) {
	Point p1(1.0, 2.0, 3.0);
	Point p2 = p1;
	EXPECT_EQ(typeid(p2).name(), typeid(Point).name());
	EXPECT_FLOAT_EQ(p2.getX(), 1.0);
	EXPECT_FLOAT_EQ(p2.getY(), 2.0);
	EXPECT_FLOAT_EQ(p2.getZ(), 3.0);
	EXPECT_FLOAT_EQ(p2.getW(), 1.0);
}

TEST(PointTests, equality) {
	Point p1(1.0, 2.0, 3.0);
	Point p2(1.0, 2.0, 3.0);
	Point p3(3.0, 2.0, 1.0);

	EXPECT_TRUE(p1 == p1);
	EXPECT_FALSE(p1 != p1);
	EXPECT_TRUE(p1 == p2);
	EXPECT_FALSE(p1 != p2);
	EXPECT_TRUE(p1 != p3);
	EXPECT_FALSE(p1 == p3);
}

TEST(PointTests, add_vector_to_point) {
	Point p1(1, 2.5, 3);
	Vector v1(4, -2.5, 2);
	Point p2(5, 0, 5);
	p1 += v1;
	EXPECT_EQ(typeid(p1).name(), typeid(Point).name());
	EXPECT_TRUE(p1 == p2);

	Point p3(-7, 0, 3);
	Vector v2(2, -1, 8);
	Point p4(-5, -1, 11);
	Point p5 = p3 + v2;
	EXPECT_EQ(typeid(p5).name(), typeid(Point).name());
	EXPECT_TRUE(p4 == p5);
}

TEST(PointTests, add_point_to_vector) {
	Vector v1(2, -1, 8); 
	Point p1(-7, 0, 3);
	Point p2(-5, -1, 11);
	Point p3 = v1 + p1;
	EXPECT_EQ(typeid(p3).name(), typeid(Point).name());
	EXPECT_TRUE(p3 == p2);
}

TEST(PointTests, substract_vector_to_point) {
	Point p1(1, 2.5, 3);
	Vector v1(4, -2.5, 2);
	Point p2(-3, 5, 1);
	p1 -= v1;
	EXPECT_EQ(typeid(p1).name(), typeid(Point).name());
	EXPECT_TRUE(p1 == p2);

	Point p3(-7, 0, 3);
	Vector v2(2, -1, 8);
	Point p4(-9, 1, -5);
	Point p5 = p3 - v2;
	EXPECT_EQ(typeid(p5).name(), typeid(Point).name());
	EXPECT_TRUE(p4 == p5);
}

TEST(PointTests, substract_point_to_vector) {
	Vector v1(2, -1, 8);
	Point p1(-7, 0, 3);
	Point p2(9, -1, 5);
	Point p3 = v1 - p1;
	EXPECT_EQ(typeid(p3).name(), typeid(Point).name());
	EXPECT_TRUE(p3 == p2);
}

TEST(PointTests, negate_point) {
	Point p1(10, -5, -4);
	Point p2(-10, 5, 4);
	EXPECT_TRUE(p2 == -p1);
}

TEST(PointTests, scalar_multiplication) {
	double s1 = 2.0;
	double s2 = 0.25;
	Point p1(1.0, 2.0, 3.0);
	Point ref1(2.0, 4.0, 6.0);
	Point p2 = p1 * s1;
	EXPECT_EQ(typeid(p2).name(), typeid(Point).name());

	EXPECT_TRUE(p2 != ref1);
	EXPECT_FLOAT_EQ(p2.getX(), ref1.getX());
	EXPECT_FLOAT_EQ(p2.getY(), ref1.getY());
	EXPECT_FLOAT_EQ(p2.getZ(), ref1.getZ());
	EXPECT_FLOAT_EQ(p2.getW(), 2.0);

	Point p3 = p2 * s2;
	EXPECT_EQ(typeid(p3).name(), typeid(Point).name());
	Point ref2(0.5, 1.0, 1.5);
	EXPECT_TRUE(p3 != ref2);
	EXPECT_FLOAT_EQ(p3.getX(), ref2.getX());
	EXPECT_FLOAT_EQ(p3.getY(), ref2.getY());
	EXPECT_FLOAT_EQ(p3.getZ(), ref2.getZ());
	EXPECT_FLOAT_EQ(p3.getW(), 0.5);

	p1 *= s1;
	EXPECT_EQ(typeid(p1).name(), typeid(Point).name());
	EXPECT_TRUE(p1 != ref1);
	EXPECT_FLOAT_EQ(p1.getX(), ref1.getX());
	EXPECT_FLOAT_EQ(p1.getY(), ref1.getY());
	EXPECT_FLOAT_EQ(p1.getZ(), ref1.getZ());
	EXPECT_FLOAT_EQ(p1.getW(), 2.0);

	p2 *= s2;
	EXPECT_EQ(typeid(p2).name(), typeid(Point).name());
	EXPECT_TRUE(p2 != ref2);
	EXPECT_FLOAT_EQ(p2.getX(), ref2.getX());
	EXPECT_FLOAT_EQ(p2.getY(), ref2.getY());
	EXPECT_FLOAT_EQ(p2.getZ(), ref2.getZ());
	EXPECT_FLOAT_EQ(p2.getW(), 0.5);
}

TEST(PointTests, matrix_multiplication) {
	Mat4 m1(1, 2, 3, 4,
			2, 4, 4, 2,
			8, 6, 4, 1,
			0, 0, 0, 1);
	Point p1(1.0, 2.0, 3.0);
	Point ref1(18.0, 24.0, 33.0);
	Point p2 = m1 * p1;
	EXPECT_EQ(typeid(p2).name(), typeid(Point).name());
	EXPECT_TRUE(p2 == ref1);
	EXPECT_FLOAT_EQ(p2.getX(), ref1.getX());
	EXPECT_FLOAT_EQ(p2.getY(), ref1.getY());
	EXPECT_FLOAT_EQ(p2.getZ(), ref1.getZ());
	EXPECT_FLOAT_EQ(p2.getW(), ref1.getW());
}