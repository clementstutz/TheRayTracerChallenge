#include "pch.h"
#include "Point.h"
#include "Vector.h"

TEST(PointTests, constructor_default) {
	Point p1;
	EXPECT_FLOAT_EQ(p1.getX(), 0.0f);
	EXPECT_FLOAT_EQ(p1.getY(), 0.0f);
	EXPECT_FLOAT_EQ(p1.getZ(), 0.0f);
	EXPECT_FLOAT_EQ(p1.getW(), 1.0f);
}

TEST(PointTests, constructor_surcharged) {
	Point p1(1.0f);
	EXPECT_FLOAT_EQ(p1.getX(), 1.0f);
	EXPECT_FLOAT_EQ(p1.getY(), 0.0f);
	EXPECT_FLOAT_EQ(p1.getZ(), 0.0f);
	EXPECT_FLOAT_EQ(p1.getW(), 1.0f);

	Point p2(1.0f, 2.0f);
	EXPECT_FLOAT_EQ(p2.getX(), 1.0f);
	EXPECT_FLOAT_EQ(p2.getY(), 2.0f);
	EXPECT_FLOAT_EQ(p2.getZ(), 0.0f);
	EXPECT_FLOAT_EQ(p2.getW(), 1.0f);

	Point p3(1.0f, 2.0f, 3.0f);
	EXPECT_FLOAT_EQ(p3.getX(), 1.0f);
	EXPECT_FLOAT_EQ(p3.getY(), 2.0f);
	EXPECT_FLOAT_EQ(p3.getZ(), 3.0f);
	EXPECT_FLOAT_EQ(p3.getW(), 1.0f);
}

TEST(PointTests, constructor_copie) {
	Point p1(1.0f, 2.0f, 3.0f);
	Point p2(p1);
	EXPECT_FLOAT_EQ(p2.getX(), 1.0f);
	EXPECT_FLOAT_EQ(p2.getY(), 2.0f);
	EXPECT_FLOAT_EQ(p2.getZ(), 3.0f);
	EXPECT_FLOAT_EQ(p2.getW(), 1.0f);
}

TEST(PointTests, constructor_affectation) {
	Point p1(1.0f, 2.0f, 3.0f);
	Point p2 = p1;
	EXPECT_FLOAT_EQ(p2.getX(), 1.0f);
	EXPECT_FLOAT_EQ(p2.getY(), 2.0f);
	EXPECT_FLOAT_EQ(p2.getZ(), 3.0f);
	EXPECT_FLOAT_EQ(p2.getW(), 1.0f);
}

//TEST(PointTests, equality) {
//	Vector t1(1.0f, 2.0f, 3.0f);
//	Vector t2(1.0f, 2.0f, 3.0f);
//	Vector t3(3.0f, 2.0f, 1.0f);
//
//	EXPECT_TRUE(t1 == t1);
//	EXPECT_FALSE(t1 != t1);
//	EXPECT_TRUE(t1 == t2);
//	EXPECT_FALSE(t1 != t2);
//	EXPECT_TRUE(t1 != t3);
//	EXPECT_FALSE(t1 == t3);
//}

//TEST(PointTests, magnitude) {
//	Tuple t1;
//	Tuple t2(1.0f);
//	Tuple t3(2.0f);
//	Tuple t4(1.0f, 1.0f, 1.0f);
//	Tuple t5(1.0f, 2.0f, 3.0f);
//
//	EXPECT_FLOAT_EQ(t1.Magnitude(), 0);
//	EXPECT_FLOAT_EQ(t2.Magnitude(), 1.0f);
//	EXPECT_FLOAT_EQ(t3.Magnitude(), 2.0f);
//	EXPECT_FLOAT_EQ(t4.Magnitude(), 1.7320508f);
//	EXPECT_FLOAT_EQ(t5.Magnitude(), 3.7416573f);
//}

//TEST(TupleTests, sqrtMagnitude) {
//	Tuple t1;
//	Tuple t2(1.0f);
//	Tuple t3(2.0f);
//	Tuple t4(1.0f, 1.0f, 1.0f);
//	Tuple t5(1.0f, 2.0f, 3.0f);
//	EXPECT_FLOAT_EQ(t1.SqrtMagnitude(), 0);
//	EXPECT_FLOAT_EQ(t2.SqrtMagnitude(), 1.0f);
//	EXPECT_FLOAT_EQ(t3.SqrtMagnitude(), 4.0f);
//	EXPECT_FLOAT_EQ(t4.SqrtMagnitude(), 3.0f);
//	EXPECT_FLOAT_EQ(t5.SqrtMagnitude(), 14.0f);
//}

TEST(PointTests, add_vector_to_point) {
	Point p1(1, 2.5, 3);
	Vector v1(4, -2.5, 2);
	Point p2(5, 0, 5);
	p1 += v1;
	EXPECT_TRUE(p1 == p2);

	Point p3(-7, 0, 3);
	Vector v2(2, -1, 8);
	Point p4(-5, -1, 11);
	Point p5 = p3 + v2;
	EXPECT_TRUE(p4 == p5);
}

TEST(PointTests, add_point_to_vector) {
	Vector v1(2, -1, 8); 
	Point p1(-7, 0, 3);
	Point p2(-5, -1, 11);
	Point p3 = v1 + p1;
	EXPECT_TRUE(p3 == p2);
}

TEST(PointTests, substract_vector_to_point) {
	Point p1(1, 2.5, 3);
	Vector v1(4, -2.5, 2);
	Point p2(-3, 5, 1);
	p1 -= v1;
	EXPECT_TRUE(p1 == p2);

	Point p3(-7, 0, 3);
	Vector v2(2, -1, 8);
	Point p4(-9, 1, -5);
	Point p5 = p3 - v2;
	EXPECT_TRUE(p4 == p5);
}

TEST(PointTests, substract_point_to_vector) {
	Vector v1(2, -1, 8);
	Point p1(-7, 0, 3);
	Point p2(9, -1, 5);
	Point p3 = v1 - p1;
	EXPECT_TRUE(p3 == p2);
}

TEST(PointTests, negate_point) {
	Point p1(10, -5, -4);
	Point p2(-10, 5, 4);
	EXPECT_TRUE(p2 == -p1);
}

TEST(PointTests, scalar_multiplication) {
	float s1 = 2.0f;
	float s2 = 0.25f;
	Point p1(1.0f, 2.0f, 3.0f);
	Point ref1(2.0f, 4.0f, 6.0f);
	Point p2 = p1 * s1;

	EXPECT_TRUE(p2 != ref1);
	EXPECT_FLOAT_EQ(p2.getX(), ref1.getX());
	EXPECT_FLOAT_EQ(p2.getY(), ref1.getY());
	EXPECT_FLOAT_EQ(p2.getZ(), ref1.getZ());
	EXPECT_FLOAT_EQ(p2.getW(), 2.0f);

	Point p3 = p2 * s2;
	Point ref2(0.5f, 1.0f, 1.5f);
	EXPECT_TRUE(p3 != ref2);
	EXPECT_FLOAT_EQ(p3.getX(), ref2.getX());
	EXPECT_FLOAT_EQ(p3.getY(), ref2.getY());
	EXPECT_FLOAT_EQ(p3.getZ(), ref2.getZ());
	EXPECT_FLOAT_EQ(p3.getW(), 0.5f);

	p1 *= s1;
	EXPECT_TRUE(p1 != ref1);
	EXPECT_FLOAT_EQ(p1.getX(), ref1.getX());
	EXPECT_FLOAT_EQ(p1.getY(), ref1.getY());
	EXPECT_FLOAT_EQ(p1.getZ(), ref1.getZ());
	EXPECT_FLOAT_EQ(p1.getW(), 2.0f);

	p2 *= s2;
	EXPECT_TRUE(p2 != ref2);
	EXPECT_FLOAT_EQ(p2.getX(), ref2.getX());
	EXPECT_FLOAT_EQ(p2.getY(), ref2.getY());
	EXPECT_FLOAT_EQ(p2.getZ(), ref2.getZ());
	EXPECT_FLOAT_EQ(p2.getW(), 0.5f);
}


//TEST(PointTests, scalar_multiplication) {
//	float s1 = 2.0f;
//	float s2 = 0.25f;
//	Point p1(1.0f, 2.0f, 3.0f);
//	Point ref1(2.0f, 4.0f, 6.0f);
//	Point p2 = p1 * s1;
//
//	EXPECT_TRUE(p2 == ref1);
//	EXPECT_FLOAT_EQ(p2.getX(), ref1.getX());
//	EXPECT_FLOAT_EQ(p2.getY(), ref1.getY());
//	EXPECT_FLOAT_EQ(p2.getZ(), ref1.getZ());
//	EXPECT_FLOAT_EQ(p2.getW(), 2.0f);
//
//	p1 *= s1;
//	EXPECT_TRUE(p1 == ref1);
//	EXPECT_FLOAT_EQ(p1.getX(), ref1.getX());
//	EXPECT_FLOAT_EQ(p1.getY(), ref1.getY());
//	EXPECT_FLOAT_EQ(p1.getZ(), ref1.getZ());
//	EXPECT_FLOAT_EQ(p1.getW(), 2.0f);
//}






//TEST(PointTests, Scale) {
//	float s1 = 2.0f;
//	float s2 = 0.25f;
//	Point p1(1.0f, 2.0f, 3.0f);
//	Point p2(2.0f, 4.0f, 6.0f);
//	Point p3(0.5f, 1.0f, 1.5f);
//
//	EXPECT_TRUE(p1.Scale(s1) == p2);
//	EXPECT_TRUE(p2.Scale(s2) == p3);
//}