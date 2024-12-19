#include "pch.h"
#include "Tuple.h"

TEST(TupleTests, constructor_default) {
	Tuple t;
	EXPECT_FLOAT_EQ(t.getX(), 0.0);
	EXPECT_FLOAT_EQ(t.getY(), 0.0);
	EXPECT_FLOAT_EQ(t.getZ(), 0.0);
	EXPECT_FLOAT_EQ(t.getW(), 0.0);
}

TEST(TupleTests, constructor_surcharged) {
	Tuple t1(1.0);
	EXPECT_FLOAT_EQ(t1.getX(), 1.0);
	EXPECT_FLOAT_EQ(t1.getY(), 0.0);
	EXPECT_FLOAT_EQ(t1.getZ(), 0.0);
	EXPECT_FLOAT_EQ(t1.getW(), 0.0);

	Tuple t2(1.0, 2.0);
	EXPECT_FLOAT_EQ(t2.getX(), 1.0);
	EXPECT_FLOAT_EQ(t2.getY(), 2.0);
	EXPECT_FLOAT_EQ(t2.getZ(), 0.0);
	EXPECT_FLOAT_EQ(t2.getW(), 0.0);

	Tuple t3(1.0, 2.0, 3.0);
	EXPECT_FLOAT_EQ(t3.getX(), 1.0);
	EXPECT_FLOAT_EQ(t3.getY(), 2.0);
	EXPECT_FLOAT_EQ(t3.getZ(), 3.0);
	EXPECT_FLOAT_EQ(t3.getW(), 0.0);

	Tuple t4(1.0, 2.0, 3.0, 4.0);
	EXPECT_FLOAT_EQ(t4.getX(), 1.0);
	EXPECT_FLOAT_EQ(t4.getY(), 2.0);
	EXPECT_FLOAT_EQ(t4.getZ(), 3.0);
	EXPECT_FLOAT_EQ(t4.getW(), 4.0);
}

TEST(TupleTests, constructor_copy) {
	Tuple t1(1.0, 2.0, 3.0, 4.0);
	Tuple t2(t1);
	EXPECT_FLOAT_EQ(t2.getX(), 1.0);
	EXPECT_FLOAT_EQ(t2.getY(), 2.0);
	EXPECT_FLOAT_EQ(t2.getZ(), 3.0);
	EXPECT_FLOAT_EQ(t2.getW(), 4.0);
}

TEST(TupleTests, constructor_moving) {
	Tuple t1;
	t1 = Tuple(1.0, 2.0, 3.0, 4.0);
	EXPECT_FLOAT_EQ(t1.getX(), 1.0);
	EXPECT_FLOAT_EQ(t1.getY(), 2.0);
	EXPECT_FLOAT_EQ(t1.getZ(), 3.0);
	EXPECT_FLOAT_EQ(t1.getW(), 4.0);
}

TEST(TupleTests, assignment) {
	Tuple t1(1.0, 2.0, 3.0, 4.0);
	Tuple t2 = t1;
	EXPECT_FLOAT_EQ(t2.getX(), 1.0);
	EXPECT_FLOAT_EQ(t2.getY(), 2.0);
	EXPECT_FLOAT_EQ(t2.getZ(), 3.0);
	EXPECT_FLOAT_EQ(t2.getW(), 4.0);
}

TEST(TupleTests, equality) {
	Tuple t1(1.0, 2.0, 3.0, 4.0);
	Tuple t2(1.0, 2.0, 3.0, 4.0);
	Tuple t3(4.0, 3.0, 2.0, 1.0);

	EXPECT_TRUE(t1 == t1);
	EXPECT_FALSE(t1 != t1);
	EXPECT_TRUE(t1 == t2);
	EXPECT_FALSE(t1 != t2);
	EXPECT_TRUE(t1 != t3);
	EXPECT_FALSE(t1 == t3);
}

TEST(TupleTests, scalar_multiplication) {
	double s1 = 2.0;
	double s2 = 0.25;
	Tuple t1(1.0, 2.0, 3.0, 4.0);
	Tuple t2(2.0, 4.0, 6.0, 8.0);
	Tuple t3(0.5, 1.0, 1.5, 2.0);

	Tuple t1_s1 = t1 * s1;
	EXPECT_TRUE(t1_s1 == t2);
	EXPECT_TRUE(t1 != t2);

	Tuple t2_s2 = t2 * s2;
	EXPECT_TRUE(t2_s2 == t3);
	EXPECT_TRUE(t2 != t3);

	t1 *= s1;
	EXPECT_TRUE(t1 == t2);

	t2 *= s2;
	EXPECT_TRUE(t2 == t3);
}

TEST(TupleTests, magnitude) {
	Tuple t1;
	Tuple t2(1.0);
	Tuple t3(2.0);
	Tuple t4(1.0, 1.0, 1.0);
	Tuple t5(1.0, 2.0, 3.0);

	EXPECT_FLOAT_EQ(t1.Magnitude(), 0);
	EXPECT_FLOAT_EQ(t2.Magnitude(), 1.0);
	EXPECT_FLOAT_EQ(t3.Magnitude(), 2.0);
	EXPECT_FLOAT_EQ(t4.Magnitude(), 1.7320508);
	EXPECT_FLOAT_EQ(t5.Magnitude(), 3.7416573);
}

TEST(TupleTests, sqrtMagnitude) {
	Tuple t1;
	Tuple t2(1.0);
	Tuple t3(2.0);
	Tuple t4(1.0, 1.0, 1.0);
	Tuple t5(1.0, 2.0, 3.0);

	EXPECT_FLOAT_EQ(t1.SqrtMagnitude(), 0);
	EXPECT_FLOAT_EQ(t2.SqrtMagnitude(), 1.0);
	EXPECT_FLOAT_EQ(t3.SqrtMagnitude(), 4.0);
	EXPECT_FLOAT_EQ(t4.SqrtMagnitude(), 3.0);
	EXPECT_FLOAT_EQ(t5.SqrtMagnitude(), 14.0);
}