#include "pch.h"
#include "Mat4.h"

TEST(Mat4Tests, constructor_default) {
    Mat4 m1;
    EXPECT_FLOAT_EQ(m1[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m1[0][1], 0.0f);
    EXPECT_FLOAT_EQ(m1[0][2], 0.0f);
    EXPECT_FLOAT_EQ(m1[0][3], 0.0f);

    EXPECT_FLOAT_EQ(m1[1][0], 0.0f);
    EXPECT_FLOAT_EQ(m1[1][1], 1.0f);
    EXPECT_FLOAT_EQ(m1[1][2], 0.0f);
    EXPECT_FLOAT_EQ(m1[1][3], 0.0f);

    EXPECT_FLOAT_EQ(m1[2][0], 0.0f);
    EXPECT_FLOAT_EQ(m1[2][1], 0.0f);
    EXPECT_FLOAT_EQ(m1[2][2], 1.0f);
    EXPECT_FLOAT_EQ(m1[2][3], 0.0f);

    EXPECT_FLOAT_EQ(m1[3][0], 0.0f);
    EXPECT_FLOAT_EQ(m1[3][1], 0.0f);
    EXPECT_FLOAT_EQ(m1[3][2], 0.0f);
    EXPECT_FLOAT_EQ(m1[3][3], 1.0f);
}

TEST(Mat4Tests, constructor_surcharged) {
    Mat4 m1(1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2);
    EXPECT_FLOAT_EQ(m1[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m1[0][1], 2.0f);
    EXPECT_FLOAT_EQ(m1[0][2], 3.0f);
    EXPECT_FLOAT_EQ(m1[0][3], 4.0f);

    EXPECT_FLOAT_EQ(m1[1][0], 5.0f);
    EXPECT_FLOAT_EQ(m1[1][1], 6.0f);
    EXPECT_FLOAT_EQ(m1[1][2], 7.0f);
    EXPECT_FLOAT_EQ(m1[1][3], 8.0f);

    EXPECT_FLOAT_EQ(m1[2][0], 9.0f);
    EXPECT_FLOAT_EQ(m1[2][1], 8.0f);
    EXPECT_FLOAT_EQ(m1[2][2], 7.0f);
    EXPECT_FLOAT_EQ(m1[2][3], 6.0f);

    EXPECT_FLOAT_EQ(m1[3][0], 5.0f);
    EXPECT_FLOAT_EQ(m1[3][1], 4.0f);
    EXPECT_FLOAT_EQ(m1[3][2], 3.0f);
    EXPECT_FLOAT_EQ(m1[3][3], 2.0f);
}

TEST(Mat4Tests, constructor_copy) {
    Mat4 m1(1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2);
    Mat4 m2(m1);
    EXPECT_FLOAT_EQ(m2[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m2[0][1], 2.0f);
    EXPECT_FLOAT_EQ(m2[0][2], 3.0f);
    EXPECT_FLOAT_EQ(m2[0][3], 4.0f);

    EXPECT_FLOAT_EQ(m2[1][0], 5.0f);
    EXPECT_FLOAT_EQ(m2[1][1], 6.0f);
    EXPECT_FLOAT_EQ(m2[1][2], 7.0f);
    EXPECT_FLOAT_EQ(m2[1][3], 8.0f);

    EXPECT_FLOAT_EQ(m2[2][0], 9.0f);
    EXPECT_FLOAT_EQ(m2[2][1], 8.0f);
    EXPECT_FLOAT_EQ(m2[2][2], 7.0f);
    EXPECT_FLOAT_EQ(m2[2][3], 6.0f);

    EXPECT_FLOAT_EQ(m2[3][0], 5.0f);
    EXPECT_FLOAT_EQ(m2[3][1], 4.0f);
    EXPECT_FLOAT_EQ(m2[3][2], 3.0f);
    EXPECT_FLOAT_EQ(m2[3][3], 2.0f);
}

TEST(Mat4Tests, stream_output) {
    // Configuration d'une matrice 2x2
    Mat4 mat(1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2);

    // Capturer la sortie dans un ostringstream
    std::ostringstream output;
    output << mat;

    // Chaîne attendue
    std::string expected = "[[1, 2, 3, 4], [5, 6, 7, 8], [9, 8, 7, 6], [5, 4, 3, 2]]";

    // Vérifier si la sortie correspond
    EXPECT_EQ(output.str(), expected);
}

TEST(Mat4Tests, operator_afectation) {
    Mat4 m1(1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2);
    Mat4 m2;
    m2 = m1;
    EXPECT_FLOAT_EQ(m2[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m2[0][1], 2.0f);
    EXPECT_FLOAT_EQ(m2[0][2], 3.0f);
    EXPECT_FLOAT_EQ(m2[0][3], 4.0f);

    EXPECT_FLOAT_EQ(m2[1][0], 5.0f);
    EXPECT_FLOAT_EQ(m2[1][1], 6.0f);
    EXPECT_FLOAT_EQ(m2[1][2], 7.0f);
    EXPECT_FLOAT_EQ(m2[1][3], 8.0f);

    EXPECT_FLOAT_EQ(m2[2][0], 9.0f);
    EXPECT_FLOAT_EQ(m2[2][1], 8.0f);
    EXPECT_FLOAT_EQ(m2[2][2], 7.0f);
    EXPECT_FLOAT_EQ(m2[2][3], 6.0f);

    EXPECT_FLOAT_EQ(m2[3][0], 5.0f);
    EXPECT_FLOAT_EQ(m2[3][1], 4.0f);
    EXPECT_FLOAT_EQ(m2[3][2], 3.0f);
    EXPECT_FLOAT_EQ(m2[3][3], 2.0f);

    m1[0][1] = 1.0f;
    m1[0][2] = 1.0f;
    m1[1][0] = 1.0f;
    m1[1][1] = 1.0f;
    EXPECT_FLOAT_EQ(m1[0][1], 1.0f);
    EXPECT_FLOAT_EQ(m1[0][2], 1.0f);
    EXPECT_FLOAT_EQ(m1[1][0], 1.0f);
    EXPECT_FLOAT_EQ(m1[1][1], 1.0f);

    EXPECT_FLOAT_EQ(m2[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m2[0][1], 2.0f);
    EXPECT_FLOAT_EQ(m2[0][2], 3.0f);
    EXPECT_FLOAT_EQ(m2[0][3], 4.0f);

    EXPECT_FLOAT_EQ(m2[1][0], 5.0f);
    EXPECT_FLOAT_EQ(m2[1][1], 6.0f);
    EXPECT_FLOAT_EQ(m2[1][2], 7.0f);
    EXPECT_FLOAT_EQ(m2[1][3], 8.0f);

    EXPECT_FLOAT_EQ(m2[2][0], 9.0f);
    EXPECT_FLOAT_EQ(m2[2][1], 8.0f);
    EXPECT_FLOAT_EQ(m2[2][2], 7.0f);
    EXPECT_FLOAT_EQ(m2[2][3], 6.0f);

    EXPECT_FLOAT_EQ(m2[3][0], 5.0f);
    EXPECT_FLOAT_EQ(m2[3][1], 4.0f);
    EXPECT_FLOAT_EQ(m2[3][2], 3.0f);
    EXPECT_FLOAT_EQ(m2[3][3], 2.0f);
}

TEST(Mat4Tests, equality) {
    Mat4 m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
    Mat4 m2(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
    Mat4 m3(2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    EXPECT_TRUE(m1 == m1);
    EXPECT_TRUE(m1 == m2);
    EXPECT_EQ(m1, m2);
    EXPECT_FALSE(m1 == m3);
}

TEST(Mat4Tests, transpose) {
    Mat4 m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
    m1.transpose();
    EXPECT_FLOAT_EQ(m1[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m1[0][1], 5.0f);
    EXPECT_FLOAT_EQ(m1[0][2], 9.0f);
    EXPECT_FLOAT_EQ(m1[0][3], 5.0f);

    EXPECT_FLOAT_EQ(m1[1][0], 2.0f);
    EXPECT_FLOAT_EQ(m1[1][1], 6.0f);
    EXPECT_FLOAT_EQ(m1[1][2], 8.0f);
    EXPECT_FLOAT_EQ(m1[1][3], 4.0f);

    EXPECT_FLOAT_EQ(m1[2][0], 3.0f);
    EXPECT_FLOAT_EQ(m1[2][1], 7.0f);
    EXPECT_FLOAT_EQ(m1[2][2], 7.0f);
    EXPECT_FLOAT_EQ(m1[2][3], 3.0f);

    EXPECT_FLOAT_EQ(m1[3][0], 4.0f);
    EXPECT_FLOAT_EQ(m1[3][1], 8.0f);
    EXPECT_FLOAT_EQ(m1[3][2], 6.0f);
    EXPECT_FLOAT_EQ(m1[3][3], 2.0f);
}

TEST(Mat4Tests, transposed) {
    Mat4 m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
    Mat4 m2;
    m2 = m1.transposed();
    //m1 hasen't changed
    EXPECT_FLOAT_EQ(m1[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m1[0][1], 2.0f);
    EXPECT_FLOAT_EQ(m1[0][2], 3.0f);
    EXPECT_FLOAT_EQ(m1[0][3], 4.0f);

    EXPECT_FLOAT_EQ(m1[1][0], 5.0f);
    EXPECT_FLOAT_EQ(m1[1][1], 6.0f);
    EXPECT_FLOAT_EQ(m1[1][2], 7.0f);
    EXPECT_FLOAT_EQ(m1[1][3], 8.0f);

    EXPECT_FLOAT_EQ(m1[2][0], 9.0f);
    EXPECT_FLOAT_EQ(m1[2][1], 8.0f);
    EXPECT_FLOAT_EQ(m1[2][2], 7.0f);
    EXPECT_FLOAT_EQ(m1[2][3], 6.0f);

    EXPECT_FLOAT_EQ(m1[3][0], 5.0f);
    EXPECT_FLOAT_EQ(m1[3][1], 4.0f);
    EXPECT_FLOAT_EQ(m1[3][2], 3.0f);
    EXPECT_FLOAT_EQ(m1[3][3], 2.0f);

    //m2 hase changed
    EXPECT_FLOAT_EQ(m2[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m2[0][1], 5.0f);
    EXPECT_FLOAT_EQ(m2[0][2], 9.0f);
    EXPECT_FLOAT_EQ(m2[0][3], 5.0f);

    EXPECT_FLOAT_EQ(m2[1][0], 2.0f);
    EXPECT_FLOAT_EQ(m2[1][1], 6.0f);
    EXPECT_FLOAT_EQ(m2[1][2], 8.0f);
    EXPECT_FLOAT_EQ(m2[1][3], 4.0f);

    EXPECT_FLOAT_EQ(m2[2][0], 3.0f);
    EXPECT_FLOAT_EQ(m2[2][1], 7.0f);
    EXPECT_FLOAT_EQ(m2[2][2], 7.0f);
    EXPECT_FLOAT_EQ(m2[2][3], 3.0f);

    EXPECT_FLOAT_EQ(m2[3][0], 4.0f);
    EXPECT_FLOAT_EQ(m2[3][1], 8.0f);
    EXPECT_FLOAT_EQ(m2[3][2], 6.0f);
    EXPECT_FLOAT_EQ(m2[3][3], 2.0f);
}

TEST(Mat4Tests, det) {
    Mat4 m1(-2, -8, 3, 5,
            -3, 1, 7, 3,
            1, 2, -9, 6,
            -6, 7, 7, -9);
    float det = m1.det();
    EXPECT_FLOAT_EQ(det, -4071.0f);
}

TEST(Mat4Tests, invert) {
    Mat4 m1(-5, 2, 6, -8,
            1, -5, 1, 8,
            7, 7, -6, -7,
            1, -3, 7, 4);

    float det = m1.det();
    EXPECT_FLOAT_EQ(det, 532.0f);

    m1.invert();

    EXPECT_NEAR(m1[0][0], 0.21805, 0.00001);
    EXPECT_NEAR(m1[0][1], 0.45113, 0.00001);
    EXPECT_NEAR(m1[0][2], 0.24060, 0.00001);
    EXPECT_NEAR(m1[0][3], -0.04511, 0.00001);

    EXPECT_NEAR(m1[1][0], -0.80827, 0.00001);
    EXPECT_NEAR(m1[1][1], -1.45677, 0.00001);
    EXPECT_NEAR(m1[1][2], -0.44361, 0.00001);
    EXPECT_NEAR(m1[1][3], 0.52068, 0.00001);

    EXPECT_NEAR(m1[2][0], -0.07895, 0.00001);
    EXPECT_NEAR(m1[2][1], -0.22368, 0.00001);
    EXPECT_NEAR(m1[2][2], -0.05263, 0.00001);
    EXPECT_NEAR(m1[2][3], 0.19737, 0.00001);

    EXPECT_NEAR(m1[3][0], -0.52256, 0.00001);
    EXPECT_NEAR(m1[3][1], -0.81391, 0.00001);
    EXPECT_NEAR(m1[3][2], -0.30075, 0.00001);
    EXPECT_NEAR(m1[3][3], 0.30639, 0.00001);
}

TEST(Mat4Tests, inverted) {
    Mat4 id;
    Mat4 m1(-5, 2, 6, -8,
            1, -5, 1, 8,
            7, 7, -6, -7,
            1, -3, 7, 4);
    Mat4 inv1 = m1.inverted();

    //m1 is still the same
    EXPECT_FLOAT_EQ(m1[0][0], -5.0f);
    EXPECT_FLOAT_EQ(m1[0][1], 2.0f);
    EXPECT_FLOAT_EQ(m1[0][2], 6.0f);
    EXPECT_FLOAT_EQ(m1[0][3], -8.0f);

    EXPECT_FLOAT_EQ(m1[1][0], 1.0f);
    EXPECT_FLOAT_EQ(m1[1][1], -5.0f);
    EXPECT_FLOAT_EQ(m1[1][2], 1.0f);
    EXPECT_FLOAT_EQ(m1[1][3], 8.0f);

    EXPECT_FLOAT_EQ(m1[2][0], 7.0f);
    EXPECT_FLOAT_EQ(m1[2][1], 7.0f);
    EXPECT_FLOAT_EQ(m1[2][2], -6.0f);
    EXPECT_FLOAT_EQ(m1[2][3], -7.0f);

    EXPECT_FLOAT_EQ(m1[3][0], 1.0f);
    EXPECT_FLOAT_EQ(m1[3][1], -3.0f);
    EXPECT_FLOAT_EQ(m1[3][2], 7.0f);
    EXPECT_FLOAT_EQ(m1[3][3], 4.0f);

    EXPECT_NEAR(inv1[0][0], 0.21805, 0.00001);
    EXPECT_NEAR(inv1[0][1], 0.45113, 0.00001);
    EXPECT_NEAR(inv1[0][2], 0.24060, 0.00001);
    EXPECT_NEAR(inv1[0][3], -0.04511, 0.00001);

    EXPECT_NEAR(inv1[1][0], -0.80827, 0.00001);
    EXPECT_NEAR(inv1[1][1], -1.45677, 0.00001);
    EXPECT_NEAR(inv1[1][2], -0.44361, 0.00001);
    EXPECT_NEAR(inv1[1][3], 0.52068, 0.00001);

    EXPECT_NEAR(inv1[2][0], -0.07895, 0.00001);
    EXPECT_NEAR(inv1[2][1], -0.22368, 0.00001);
    EXPECT_NEAR(inv1[2][2], -0.05263, 0.00001);
    EXPECT_NEAR(inv1[2][3], 0.19737, 0.00001);

    EXPECT_NEAR(inv1[3][0], -0.52256, 0.00001);
    EXPECT_NEAR(inv1[3][1], -0.81391, 0.00001);
    EXPECT_NEAR(inv1[3][2], -0.30075, 0.00001);
    EXPECT_NEAR(inv1[3][3], 0.30639, 0.00001);

    EXPECT_EQ(id, m1 * inv1);
    EXPECT_TRUE(id == m1 * inv1);
}