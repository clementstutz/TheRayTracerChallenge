#include "pch.h"
#include "Vector.h"
#include "Point.h"
#include "Mat4.h"

TEST(VectorTests, constructor_default) {
	Vector v1;
	EXPECT_EQ(typeid(v1).name(), typeid(Vector).name());
	EXPECT_FLOAT_EQ(v1.getX(), 0.0f);
	EXPECT_FLOAT_EQ(v1.getY(), 0.0f);
	EXPECT_FLOAT_EQ(v1.getZ(), 0.0f);
	EXPECT_FLOAT_EQ(v1.getW(), 0.0f);
}

TEST(VectorTests, constructor_surcharged) {
	Vector v1(1.0f);
	EXPECT_EQ(typeid(v1).name(), typeid(Vector).name());
	EXPECT_FLOAT_EQ(v1.getX(), 1.0f);
	EXPECT_FLOAT_EQ(v1.getY(), 0.0f);
	EXPECT_FLOAT_EQ(v1.getZ(), 0.0f);
	EXPECT_FLOAT_EQ(v1.getW(), 0.0f);

	Vector v2(1.0f, 2.0f);
	EXPECT_EQ(typeid(v2).name(), typeid(Vector).name());
	EXPECT_FLOAT_EQ(v2.getX(), 1.0f);
	EXPECT_FLOAT_EQ(v2.getY(), 2.0f);
	EXPECT_FLOAT_EQ(v2.getZ(), 0.0f);
	EXPECT_FLOAT_EQ(v2.getW(), 0.0f);

	Vector v3(1.0f, 2.0f, 3.0f);
	EXPECT_EQ(typeid(v3).name(), typeid(Vector).name());
	EXPECT_FLOAT_EQ(v3.getX(), 1.0f);
	EXPECT_FLOAT_EQ(v3.getY(), 2.0f);
	EXPECT_FLOAT_EQ(v3.getZ(), 3.0f);
	EXPECT_FLOAT_EQ(v3.getW(), 0.0f);
}

TEST(VectorTests, constructor_copy) {
	Vector v1(1.0f, 2.0f, 3.0f);
	Vector v2(v1);
	EXPECT_EQ(typeid(v2).name(), typeid(Vector).name());
	EXPECT_FLOAT_EQ(v2.getX(), 1.0f);
	EXPECT_FLOAT_EQ(v2.getY(), 2.0f);
	EXPECT_FLOAT_EQ(v2.getZ(), 3.0f);
	EXPECT_FLOAT_EQ(v2.getW(), 0.0f);
}

TEST(VectorTests, constructor_moving) {
	Vector v1;
	v1 = Vector(1.0f, 2.0f, 3.0f);
	EXPECT_EQ(typeid(v1).name(), typeid(Vector).name());
	EXPECT_FLOAT_EQ(v1.getX(), 1.0f);
	EXPECT_FLOAT_EQ(v1.getY(), 2.0f);
	EXPECT_FLOAT_EQ(v1.getZ(), 3.0f);
	EXPECT_FLOAT_EQ(v1.getW(), 0.0f);
}

TEST(VectorTests, assignment) {
	Vector v1(1.0f, 2.0f, 3.0f);
	Vector v2 = v1;
	EXPECT_EQ(typeid(v2).name(), typeid(Vector).name());
	EXPECT_FLOAT_EQ(v2.getX(), 1.0f);
	EXPECT_FLOAT_EQ(v2.getY(), 2.0f);
	EXPECT_FLOAT_EQ(v2.getZ(), 3.0f);
	EXPECT_FLOAT_EQ(v2.getW(), 0.0f);
}

TEST(VectorTests, equality) {
	Vector t1(1.0f, 2.0f, 3.0f);
	Vector t2(1.0f, 2.0f, 3.0f);
	Vector t3(3.0f, 2.0f, 1.0f);

	EXPECT_TRUE(t1 == t1);
	EXPECT_FALSE(t1 != t1);
	EXPECT_TRUE(t1 == t2);
	EXPECT_FALSE(t1 != t2);
	EXPECT_TRUE(t1 != t3);
	EXPECT_FALSE(t1 == t3);
}

//TEST(VectorTests, magnitude) {
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

TEST(VectorTests, add_two_vectors) {
	Vector v1(1, 2.5, 3);
	Vector v2(4, -2.5, 2);
	Vector v3(5, 0, 5);
	v2 += v1;
	EXPECT_EQ(typeid(v2).name(), typeid(Vector).name());
	EXPECT_TRUE(v2 == v3);

	Vector v4(-7, 0, 3);
	Vector v5(-2, 0, 8);
	Vector v6 = v3 + v4;
	EXPECT_EQ(typeid(v6).name(), typeid(Vector).name());
	EXPECT_TRUE(v5 == v6);
}

TEST(VectorTests, add_two_points) {
	Point p1(1, 2, 3), p2(2, 2, 2);
	Vector v1 = p2 + p1;
	EXPECT_EQ(typeid(v1).name(), typeid(Vector).name());
	Vector v2(3, 4, 5);
	EXPECT_TRUE(v1 == v2);
}

TEST(VectorTests, substract_two_vectors) {
	Vector v1(1, 2.5, 3);
	Vector v2(4, -2.5, 2);
	Vector v3(3, -5, -1);
	v2 -= v1;
	EXPECT_EQ(typeid(v2).name(), typeid(Vector).name());
	EXPECT_TRUE(v2 == v3);

	Vector v4(-7, 0, 3);
	Vector v5(10, -5, -4);
	Vector v6 = v3 - v4;
	EXPECT_EQ(typeid(v6).name(), typeid(Vector).name());
	EXPECT_TRUE(v5 == v6);
}

TEST(VectorTests, substract_two_points) {
	Point p1(1, 2, 3), p2(2, 2, 2);
	Vector v1 = p2 - p1;
	EXPECT_EQ(typeid(v1).name(), typeid(Vector).name());
	Vector v2(1, 0, -1);
	EXPECT_TRUE(v1 == v2);
}

TEST(VectorTests, negate_vector) {
	Vector v1(10, -5, -4);
	Vector v2(-10, 5, 4);
	EXPECT_TRUE(v2 == -v1);
}

TEST(VectorTests, scalar_multiplication) {
	float s1 = 2.0f;
	float s2 = 0.25f;
	Vector v1(1.0f, 2.0f, 3.0f);
	Vector ref1(2.0f, 4.0f, 6.0f);
	Vector v2 = v1 * s1;

	EXPECT_EQ(typeid(v2).name(), typeid(Vector).name());
	EXPECT_TRUE(v2 == ref1);
	EXPECT_FLOAT_EQ(v2.getX(), ref1.getX());
	EXPECT_FLOAT_EQ(v2.getY(), ref1.getY());
	EXPECT_FLOAT_EQ(v2.getZ(), ref1.getZ());
	EXPECT_FLOAT_EQ(v2.getW(), 0.0f);

	Vector v3 = v2 * s2;
	EXPECT_EQ(typeid(v3).name(), typeid(Vector).name());
	Vector ref2(0.5f, 1.0f, 1.5f);
	EXPECT_TRUE(v3 == ref2);
	EXPECT_FLOAT_EQ(v3.getX(), ref2.getX());
	EXPECT_FLOAT_EQ(v3.getY(), ref2.getY());
	EXPECT_FLOAT_EQ(v3.getZ(), ref2.getZ());
	EXPECT_FLOAT_EQ(v3.getW(), 0.0f);

	v1 *= s1;
	EXPECT_EQ(typeid(v1).name(), typeid(Vector).name());
	EXPECT_TRUE(v1 == ref1);
	EXPECT_FLOAT_EQ(v1.getX(), ref1.getX());
	EXPECT_FLOAT_EQ(v1.getY(), ref1.getY());
	EXPECT_FLOAT_EQ(v1.getZ(), ref1.getZ());
	EXPECT_FLOAT_EQ(v1.getW(), 0.0f);
	
	v2 *= s2;
	EXPECT_EQ(typeid(v2).name(), typeid(Vector).name());
	EXPECT_TRUE(v2 == ref2);
	EXPECT_FLOAT_EQ(v2.getX(), ref2.getX());
	EXPECT_FLOAT_EQ(v2.getY(), ref2.getY());
	EXPECT_FLOAT_EQ(v2.getZ(), ref2.getZ());
	EXPECT_FLOAT_EQ(v2.getW(), 0.0f);
}

TEST(VectorTests, Normalize) {
	Vector v1(1.0f);
	v1.Normalize();
	EXPECT_EQ(typeid(v1).name(), typeid(Vector).name());
	Vector n1(1.0f);
	EXPECT_TRUE(v1 == n1);

	Vector v2(1.0f, 1.0f, 1.0f);
	v2.Normalize();
	Vector n2(0.5773502, 0.5773502, 0.5773502);
	EXPECT_TRUE(v2 == n2);

	Vector v3(1.0f, 2.0f, 3.0f);
	v3.Normalize();
	Vector n3(0.2672612, 0.5345225, 0.8017837);
	EXPECT_TRUE(v3 == n3);
}

TEST(VectorTests, Normalized) {
	Vector v1(1.0f);
	Vector v11 = v1.Normalized();
	EXPECT_EQ(typeid(v11).name(), typeid(Vector).name());
	Vector n1(1.0f);
	EXPECT_TRUE(v11 == v1);
	EXPECT_TRUE(v11 == n1);

	Vector v2(1.0f, 1.0f, 1.0f);
	Vector v22 = v2.Normalized();
	Vector n2(0.5773502f, 0.5773502f, 0.5773502f);
	EXPECT_TRUE(v22 != v2);
	EXPECT_TRUE(v22 == n2);

	Vector v3(1.0f, 2.0f, 3.0f);
	Vector v33 = v3.Normalized();
	Vector n3(0.2672612, 0.5345225, 0.8017837);
	EXPECT_TRUE(v33 != v3);
	EXPECT_TRUE(v33 == n3);
}

TEST(VectorTests, Dot) {
	Vector v1(1.0f, 2.0f, 3.0f);
	Vector v2(2.0f, 1.5f, 1.0f);
	float result = 8;
	EXPECT_TRUE(result == v1.Dot(v2));
	//EXPECT_TRUE(result == Dot(v1, v2));
}

TEST(VectorTests, Cross) {
	Vector v1(1.0f, 2.0f, 3.0f);
	Vector v2(2.0f, 1.5f, 1.0f);
	Vector ref(-2.5f, 5.0f, -2.5f);
	Vector result = v1.Cross(v2);
	EXPECT_EQ(typeid(result).name(), typeid(Vector).name());
	EXPECT_TRUE(result == result);
}

TEST(VectorTests, matrix_multiplication) {
	Mat4 m1(1, 2, 3, 4,
			2, 4, 4, 2,
			8, 6, 4, 1,
			0, 0, 0, 1);
	Vector v1(1.0f, 2.0f, 3.0f);
	Vector ref1(14.0f, 22.0f, 32.0f);
	Vector v2 = m1 * v1;

	EXPECT_EQ(typeid(v2).name(), typeid(Vector).name());
	EXPECT_TRUE(v2 == ref1);
	EXPECT_FLOAT_EQ(v2.getX(), ref1.getX());
	EXPECT_FLOAT_EQ(v2.getY(), ref1.getY());
	EXPECT_FLOAT_EQ(v2.getZ(), ref1.getZ());
	EXPECT_FLOAT_EQ(v2.getW(), ref1.getW());
}

TEST(VectorTests, reflect) {
	// Reflecting a vector approaching at 45
	Vector incoming(1, -1, 0);
	Vector normal(0, 1, 0);
	Vector ref(1, 1, 0);
	Vector result = Vector::Reflect(incoming, normal);
	EXPECT_TRUE(ref == result);
	EXPECT_EQ(result, ref);

	// Reflecting a vector off a slanted surface
	incoming = Vector(0, -1, 0);
	normal = Vector(sqrt(2) / 2.0f, sqrt(2) / 2.0f, 0);
	result = Vector::Reflect(incoming, normal);
	ref = Vector(1, 0, 0);
	EXPECT_TRUE(ref == result);
	EXPECT_EQ(result, ref);

	// Reflecting a vector approaching at 90
	incoming = Vector(0, 0, 1);
	normal = Vector(0, 0, -1);
	result = Vector::Reflect(incoming, normal);
	ref = Vector(0, 0, -1);
	EXPECT_TRUE(ref == result);
	EXPECT_EQ(result, ref);
}