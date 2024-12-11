#include<cmath>
#include "pch.h"
#include "Mat4.h"
#include "Utils.h"

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

TEST(Mat4Tests, translate_matrix) {
    Mat4 trans = Mat4::TranslateMatrix(5, -3, 2);
    EXPECT_FLOAT_EQ(trans[0][3], 5.0f);
    EXPECT_FLOAT_EQ(trans[1][3], -3.0f);
    EXPECT_FLOAT_EQ(trans[2][3], 2.0f);

    Point pOrigine(-3, 4, 5);
    Point pOrigineTrans = trans * pOrigine;
    Point ref1(2, 1, 7);
    EXPECT_EQ(pOrigineTrans, ref1);
    EXPECT_FLOAT_EQ(pOrigineTrans.getX(), ref1.getX());
    EXPECT_FLOAT_EQ(pOrigineTrans.getY(), ref1.getY());
    EXPECT_FLOAT_EQ(pOrigineTrans.getZ(), ref1.getZ());
    EXPECT_FLOAT_EQ(pOrigineTrans.getW(), ref1.getW());

    Mat4 inverseTrans = trans.inverted();
    Point result = inverseTrans * pOrigineTrans;
    EXPECT_EQ(result, pOrigine);
    EXPECT_FLOAT_EQ(result.getX(), pOrigine.getX());
    EXPECT_FLOAT_EQ(result.getY(), pOrigine.getY());
    EXPECT_FLOAT_EQ(result.getZ(), pOrigine.getZ());
    EXPECT_FLOAT_EQ(result.getW(), pOrigine.getW());

    Vector vOrigine(-3, 4, 5);
    Vector vTrans = trans * vOrigine;
    EXPECT_EQ(vTrans, vOrigine);
    EXPECT_FLOAT_EQ(vTrans.getX(), vOrigine.getX());
    EXPECT_FLOAT_EQ(vTrans.getY(), vOrigine.getY());
    EXPECT_FLOAT_EQ(vTrans.getZ(), vOrigine.getZ());
    EXPECT_FLOAT_EQ(vTrans.getW(), vOrigine.getW());
}

TEST(Mat4Tests, scale_matrix) {
    Mat4 scaling = Mat4::ScaleMatrix(-1, 1, 2);
    EXPECT_FLOAT_EQ(scaling[0][0], -1.0f);
    EXPECT_FLOAT_EQ(scaling[1][1], 1.0f);
    EXPECT_FLOAT_EQ(scaling[2][2], 2.0f);

    Point pOrigine(2, 3, 4);
    Point pOrigineScaled = scaling * pOrigine;
    EXPECT_FLOAT_EQ(pOrigineScaled.getX(), -2.0f);
    EXPECT_FLOAT_EQ(pOrigineScaled.getY(), 3.0f);
    EXPECT_FLOAT_EQ(pOrigineScaled.getZ(), 8.0f);
    EXPECT_FLOAT_EQ(pOrigineScaled.getW(), 1.0f);

    Mat4 inverseScaling = scaling.inverted();
    Point result1 = inverseScaling * pOrigineScaled;
    EXPECT_EQ(result1, pOrigine);
    EXPECT_FLOAT_EQ(result1.getX(), pOrigine.getX());
    EXPECT_FLOAT_EQ(result1.getY(), pOrigine.getY());
    EXPECT_FLOAT_EQ(result1.getZ(), pOrigine.getZ());
    EXPECT_FLOAT_EQ(result1.getW(), pOrigine.getW());

    Vector vOrigine(-4, 6, 8);
    Vector vOrigineScaled = scaling * vOrigine;
    Vector ref1(4, 6, 16);
    EXPECT_EQ(vOrigineScaled, ref1);
    EXPECT_FLOAT_EQ(vOrigineScaled.getX(), ref1.getX());
    EXPECT_FLOAT_EQ(vOrigineScaled.getY(), ref1.getY());
    EXPECT_FLOAT_EQ(vOrigineScaled.getZ(), ref1.getZ());
    EXPECT_FLOAT_EQ(vOrigineScaled.getW(), ref1.getW());

    Vector result2 = inverseScaling * vOrigineScaled;
    EXPECT_EQ(result2, vOrigine);
    EXPECT_FLOAT_EQ(result2.getX(), vOrigine.getX());
    EXPECT_FLOAT_EQ(result2.getY(), vOrigine.getY());
    EXPECT_FLOAT_EQ(result2.getZ(), vOrigine.getZ());
    EXPECT_FLOAT_EQ(result2.getW(), vOrigine.getW());
}

TEST(Mat4Tests, rotate_X_matrix) {
    Mat4 halfQuarter = Mat4::RotateXMatrix(Utils::PI / 4.0f);
    EXPECT_FLOAT_EQ(halfQuarter[1][1], cos(Utils::PI / 4.0f));
    EXPECT_FLOAT_EQ(halfQuarter[1][2], -sin(Utils::PI / 4.0f));
    EXPECT_FLOAT_EQ(halfQuarter[2][1], sin(Utils::PI / 4.0f));
    EXPECT_FLOAT_EQ(halfQuarter[2][2], cos(Utils::PI / 4.0f));

    Mat4 fullQuarter = Mat4::RotateXMatrix(Utils::PI / 2.0f);
    EXPECT_FLOAT_EQ(fullQuarter[1][1], cos(Utils::PI / 2.0f));
    EXPECT_FLOAT_EQ(fullQuarter[1][2], -sin(Utils::PI / 2.0f));
    EXPECT_FLOAT_EQ(fullQuarter[2][1], sin(Utils::PI / 2.0f));
    EXPECT_FLOAT_EQ(fullQuarter[2][2], cos(Utils::PI / 2.0f));
    
    // Points
    // Rotate a point by pi/4
    Point pOrigine(0, 1, 0);
    Point pRotateX_half = halfQuarter * pOrigine;
    Point ref1(0, sqrt(2) / 2.0f, sqrt(2) / 2.0f);
    EXPECT_EQ(pRotateX_half, ref1);
    EXPECT_FLOAT_EQ(pRotateX_half.getX(), ref1.getX());
    EXPECT_FLOAT_EQ(pRotateX_half.getY(), ref1.getY());
    EXPECT_FLOAT_EQ(pRotateX_half.getZ(), ref1.getZ());
    EXPECT_FLOAT_EQ(pRotateX_half.getW(), ref1.getW());

    // Rotate a point by pi/2
    Point pRotateX_full = fullQuarter * pOrigine;
    Point ref2(0, 0, 1);
    EXPECT_EQ(pRotateX_full, ref2);
    EXPECT_FLOAT_EQ(pRotateX_full.getX(), ref2.getX());
    EXPECT_NEAR(pRotateX_full.getY(), ref2.getY(), Utils::EPSILON);
    EXPECT_FLOAT_EQ(pRotateX_full.getZ(), ref2.getZ());
    EXPECT_FLOAT_EQ(pRotateX_full.getW(), ref2.getW());

    // Invert the rotation of a point
    Mat4 inverse_half = halfQuarter.inverted();
    Mat4 inverse_full = fullQuarter.inverted();
    EXPECT_EQ(pOrigine, inverse_half * pRotateX_half);
    EXPECT_EQ(pOrigine, inverse_full * pRotateX_full);

    // Vectors
    // Rotate a vector by pi/4
    Vector vOrigine(0, 1, 0);
    Vector vRotateX_half = halfQuarter * vOrigine;
    Vector ref3(0, sqrt(2) / 2.0f, sqrt(2) / 2.0f);
    EXPECT_EQ(vRotateX_half, ref3);
    EXPECT_FLOAT_EQ(vRotateX_half.getX(), ref3.getX());
    EXPECT_FLOAT_EQ(vRotateX_half.getY(), ref3.getY());
    EXPECT_FLOAT_EQ(vRotateX_half.getZ(), ref3.getZ());
    EXPECT_FLOAT_EQ(vRotateX_half.getW(), ref3.getW());

    // Rotate a vector by pi/2
    Vector vRotateX_full = fullQuarter * vOrigine;
    Vector ref4(0, 0, 1);
    EXPECT_EQ(vRotateX_full, ref4);
    EXPECT_FLOAT_EQ(vRotateX_full.getX(), ref4.getX());
    EXPECT_NEAR(vRotateX_full.getY(), ref4.getY(), Utils::EPSILON);
    EXPECT_FLOAT_EQ(vRotateX_full.getZ(), ref4.getZ());
    EXPECT_FLOAT_EQ(vRotateX_full.getW(), ref4.getW());

    // Invert the rotation of a vector
    EXPECT_EQ(vOrigine, inverse_half * vRotateX_half);
    EXPECT_EQ(vOrigine, inverse_full * vRotateX_full);
}

TEST(Mat4Tests, rotate_Y_matrix) {
    Mat4 halfQuarter = Mat4::RotateYMatrix(Utils::PI / 4.0f);
    EXPECT_FLOAT_EQ(halfQuarter[0][0], cos(Utils::PI / 4.0f));
    EXPECT_FLOAT_EQ(halfQuarter[0][2], sin(Utils::PI / 4.0f));
    EXPECT_FLOAT_EQ(halfQuarter[2][0], -sin(Utils::PI / 4.0f));
    EXPECT_FLOAT_EQ(halfQuarter[2][2], cos(Utils::PI / 4.0f));

    Mat4 fullQuarter = Mat4::RotateYMatrix(Utils::PI / 2.0f);
    EXPECT_FLOAT_EQ(fullQuarter[0][0], cos(Utils::PI / 2.0f));
    EXPECT_FLOAT_EQ(fullQuarter[0][2], sin(Utils::PI / 2.0f));
    EXPECT_FLOAT_EQ(fullQuarter[2][0], -sin(Utils::PI / 2.0f));
    EXPECT_FLOAT_EQ(fullQuarter[2][2], cos(Utils::PI / 2.0f));

    // Points
    // Rotate a point by pi/4
    Point pOrigine(0, 0, 1);
    Point pRotateY_half = halfQuarter * pOrigine;
    Point ref1(sqrt(2) / 2.0f, 0, sqrt(2) / 2.0f);
    EXPECT_EQ(pRotateY_half, ref1);
    EXPECT_FLOAT_EQ(pRotateY_half.getX(), ref1.getX());
    EXPECT_FLOAT_EQ(pRotateY_half.getY(), ref1.getY());
    EXPECT_FLOAT_EQ(pRotateY_half.getZ(), ref1.getZ());
    EXPECT_FLOAT_EQ(pRotateY_half.getW(), ref1.getW());

    // Rotate a point by pi/2
    Point pRotateY_full = fullQuarter * pOrigine;
    Point ref2(1, 0, 0);
    EXPECT_EQ(pRotateY_full, ref2);
    EXPECT_FLOAT_EQ(pRotateY_full.getX(), ref2.getX());
    EXPECT_FLOAT_EQ(pRotateY_full.getY(), ref2.getY());
    EXPECT_NEAR(pRotateY_full.getZ(), ref2.getZ(), Utils::EPSILON);
    EXPECT_FLOAT_EQ(pRotateY_full.getW(), ref2.getW());

    // Invert the rotation of a point
    Mat4 inverse_half = halfQuarter.inverted();
    Mat4 inverse_full = fullQuarter.inverted();
    EXPECT_EQ(pOrigine, inverse_half * pRotateY_half);
    EXPECT_EQ(pOrigine, inverse_full * pRotateY_full);

    // Vectors
    // Rotate a vector by pi/4
    Vector vOrigine(0, 0, 1);
    Vector vRotateY_half = halfQuarter * vOrigine;
    Vector ref3(sqrt(2) / 2.0f, 0, sqrt(2) / 2.0f);
    EXPECT_EQ(vRotateY_half, ref3);
    EXPECT_FLOAT_EQ(vRotateY_half.getX(), ref3.getX());
    EXPECT_FLOAT_EQ(vRotateY_half.getY(), ref3.getY());
    EXPECT_FLOAT_EQ(vRotateY_half.getZ(), ref3.getZ());
    EXPECT_FLOAT_EQ(vRotateY_half.getW(), ref3.getW());

    // Rotate a vector by pi/2
    Vector vRotateY_full = fullQuarter * vOrigine;
    Vector ref4(1, 0, 0);
    EXPECT_EQ(vRotateY_full, ref4);
    EXPECT_FLOAT_EQ(vRotateY_full.getX(), ref4.getX());
    EXPECT_FLOAT_EQ(vRotateY_full.getY(), ref4.getY());
    EXPECT_NEAR(vRotateY_full.getZ(), ref4.getZ(), Utils::EPSILON);
    EXPECT_FLOAT_EQ(vRotateY_full.getW(), ref4.getW());

    // Invert the rotation of a vector
    EXPECT_EQ(vOrigine, inverse_half * vRotateY_half);
    EXPECT_EQ(vOrigine, inverse_full * vRotateY_full);
}

TEST(Mat4Tests, rotate_Z_matrix) {
    Mat4 halfQuarter = Mat4::RotateZMatrix(Utils::PI / 4.0f);
    EXPECT_FLOAT_EQ(halfQuarter[0][0], cos(Utils::PI / 4.0f));
    EXPECT_FLOAT_EQ(halfQuarter[0][1], -sin(Utils::PI / 4.0f));
    EXPECT_FLOAT_EQ(halfQuarter[1][0], sin(Utils::PI / 4.0f));
    EXPECT_FLOAT_EQ(halfQuarter[1][1], cos(Utils::PI / 4.0f));

    Mat4 fullQuarter = Mat4::RotateZMatrix(Utils::PI / 2.0f);
    EXPECT_FLOAT_EQ(fullQuarter[0][0], cos(Utils::PI / 2.0f));
    EXPECT_FLOAT_EQ(fullQuarter[0][1], -sin(Utils::PI / 2.0f));
    EXPECT_FLOAT_EQ(fullQuarter[1][0], sin(Utils::PI / 2.0f));
    EXPECT_FLOAT_EQ(fullQuarter[1][1], cos(Utils::PI / 2.0f));

    // Points
    // Rotate a point by pi/4
    Point pOrigine(1, 0, 0);
    Point pRotateZ_half = halfQuarter * pOrigine;
    Point ref1(sqrt(2) / 2.0f, sqrt(2) / 2.0f, 0);
    EXPECT_EQ(pRotateZ_half, ref1);
    EXPECT_FLOAT_EQ(pRotateZ_half.getX(), ref1.getX());
    EXPECT_FLOAT_EQ(pRotateZ_half.getY(), ref1.getY());
    EXPECT_FLOAT_EQ(pRotateZ_half.getZ(), ref1.getZ());
    EXPECT_FLOAT_EQ(pRotateZ_half.getW(), ref1.getW());

    // Rotate a point by pi/2
    Point pRotateZ_full = fullQuarter * pOrigine;
    Point ref2(0, 1, 0);
    EXPECT_EQ(pRotateZ_full, ref2);
    EXPECT_NEAR(pRotateZ_full.getX(), ref2.getX(), Utils::EPSILON);
    EXPECT_FLOAT_EQ(pRotateZ_full.getY(), ref2.getY());
    EXPECT_FLOAT_EQ(pRotateZ_full.getZ(), ref2.getZ());
    EXPECT_FLOAT_EQ(pRotateZ_full.getW(), ref2.getW());

    // Invert the rotation of a point
    Mat4 inverse_half = halfQuarter.inverted();
    Mat4 inverse_full = fullQuarter.inverted();
    EXPECT_EQ(pOrigine, inverse_half * pRotateZ_half);
    EXPECT_EQ(pOrigine, inverse_full * pRotateZ_full);

    // Vectors
    // Rotate a vector by pi/4
    Vector vOrigine(1, 0, 0);
    Vector vRotateZ_half = halfQuarter * vOrigine;
    Vector ref3(sqrt(2) / 2.0f, sqrt(2) / 2.0f, 0);
    EXPECT_EQ(vRotateZ_half, ref3);
    EXPECT_FLOAT_EQ(vRotateZ_half.getX(), ref3.getX());
    EXPECT_FLOAT_EQ(vRotateZ_half.getY(), ref3.getY());
    EXPECT_FLOAT_EQ(vRotateZ_half.getZ(), ref3.getZ());
    EXPECT_FLOAT_EQ(vRotateZ_half.getW(), ref3.getW());

    // Rotate a vector by pi/2
    Vector vRotateZ_full = fullQuarter * vOrigine;
    Vector ref4(0, 1, 0);
    EXPECT_EQ(vRotateZ_full, ref4);
    EXPECT_NEAR(vRotateZ_full.getX(), ref4.getX(), Utils::EPSILON);
    EXPECT_FLOAT_EQ(vRotateZ_full.getY(), ref4.getY());
    EXPECT_FLOAT_EQ(vRotateZ_full.getZ(), ref4.getZ());
    EXPECT_FLOAT_EQ(vRotateZ_full.getW(), ref4.getW());

    // Invert the rotation of a vector
    EXPECT_EQ(vOrigine, inverse_half * vRotateZ_half);
    EXPECT_EQ(vOrigine, inverse_full * vRotateZ_full);
}

TEST(Mat4Tests, shearing_matrix) {
    Mat4 shearMatrix = Mat4::ShearMatrix(1, 0, 0, 0, 0, 0);
    EXPECT_FLOAT_EQ(shearMatrix[0][1], 1);
    EXPECT_FLOAT_EQ(shearMatrix[0][2], 0);
    EXPECT_FLOAT_EQ(shearMatrix[1][0], 0);
    EXPECT_FLOAT_EQ(shearMatrix[1][2], 0);
    EXPECT_FLOAT_EQ(shearMatrix[2][0], 0);
    EXPECT_FLOAT_EQ(shearMatrix[2][1], 0);

    // Shearing a Point
    Point pOrigine(2, 3, 4);
    Point shearedPoint = shearMatrix * pOrigine;
    Point ref1(5, 3, 4);
    EXPECT_EQ(ref1, shearedPoint);
    Mat4 inverseShear = shearMatrix.inverted();
    Point invShearedPoint = inverseShear * shearedPoint;
    EXPECT_EQ(pOrigine, invShearedPoint);

    shearMatrix = Mat4::ShearMatrix(0, 1, 0, 0, 0, 0);
    shearedPoint = shearMatrix * pOrigine;
    ref1.set(6, 3, 4);
    EXPECT_EQ(ref1, shearedPoint);
    inverseShear = shearMatrix.inverted();
    invShearedPoint = inverseShear * shearedPoint;
    EXPECT_EQ(pOrigine, invShearedPoint);

    shearMatrix = Mat4::ShearMatrix(0, 0, 1, 0, 0, 0);
    shearedPoint = shearMatrix * pOrigine;
    ref1.set(2, 5, 4);
    EXPECT_EQ(ref1, shearedPoint);
    inverseShear = shearMatrix.inverted();
    invShearedPoint = inverseShear * shearedPoint;
    EXPECT_EQ(pOrigine, invShearedPoint);

    shearMatrix = Mat4::ShearMatrix(0, 0, 0, 1, 0, 0);
    shearedPoint = shearMatrix * pOrigine;
    ref1.set(2, 7, 4);
    EXPECT_EQ(ref1, shearedPoint);
    inverseShear = shearMatrix.inverted();
    invShearedPoint = inverseShear * shearedPoint;
    EXPECT_EQ(pOrigine, invShearedPoint);

    shearMatrix = Mat4::ShearMatrix(0, 0, 0, 0, 1, 0);
    shearedPoint = shearMatrix * pOrigine;
    ref1.set(2, 3, 6);
    EXPECT_EQ(ref1, shearedPoint);
    inverseShear = shearMatrix.inverted();
    invShearedPoint = inverseShear * shearedPoint;
    EXPECT_EQ(pOrigine, invShearedPoint);

    shearMatrix = Mat4::ShearMatrix(0, 0, 0, 0, 0, 1);
    shearedPoint = shearMatrix * pOrigine;
    ref1.set(2, 3, 7);
    EXPECT_EQ(ref1, shearedPoint);
    inverseShear = shearMatrix.inverted();
    invShearedPoint = inverseShear * shearedPoint;
    EXPECT_EQ(pOrigine, invShearedPoint);

    // Shearing a Vector
    shearMatrix = Mat4::ShearMatrix(1, 0, 0, 0, 0, 0);
    Vector vOrigine(2, 3, 4);
    Vector shearedVector = shearMatrix * vOrigine;
    Vector ref2(5, 3, 4);
    EXPECT_EQ(ref2, shearedVector);
    inverseShear = shearMatrix.inverted();
    Vector invShearedVector = inverseShear * shearedVector;
    EXPECT_EQ(vOrigine, invShearedVector);

    shearMatrix = Mat4::ShearMatrix(0, 1, 0, 0, 0, 0);
    shearedVector = shearMatrix * vOrigine;
    ref2.set(6, 3, 4);
    EXPECT_EQ(ref2, shearedVector);
    inverseShear = shearMatrix.inverted();
    invShearedVector = inverseShear * shearedVector;
    EXPECT_EQ(vOrigine, invShearedVector);

    shearMatrix = Mat4::ShearMatrix(0, 0, 1, 0, 0, 0);
    shearedVector = shearMatrix * vOrigine;
    ref2.set(2, 5, 4);
    EXPECT_EQ(ref2, shearedVector);
    inverseShear = shearMatrix.inverted();
    invShearedVector = inverseShear * shearedVector;
    EXPECT_EQ(vOrigine, invShearedVector);

    shearMatrix = Mat4::ShearMatrix(0, 0, 0, 1, 0, 0);
    shearedVector = shearMatrix * vOrigine;
    ref2.set(2, 7, 4);
    EXPECT_EQ(ref2, shearedVector);
    inverseShear = shearMatrix.inverted();
    invShearedVector = inverseShear * shearedVector;
    EXPECT_EQ(vOrigine, invShearedVector);

    shearMatrix = Mat4::ShearMatrix(0, 0, 0, 0, 1, 0);
    shearedVector = shearMatrix * vOrigine;
    ref2.set(2, 3, 6);
    EXPECT_EQ(ref2, shearedVector);
    inverseShear = shearMatrix.inverted();
    invShearedVector = inverseShear * shearedVector;
    EXPECT_EQ(vOrigine, invShearedVector);

    shearMatrix = Mat4::ShearMatrix(0, 0, 0, 0, 0, 1);
    shearedVector = shearMatrix * vOrigine;
    ref2.set(2, 3, 7);
    EXPECT_EQ(ref2, shearedVector);
    inverseShear = shearMatrix.inverted();
    invShearedVector = inverseShear * shearedVector;
    EXPECT_EQ(vOrigine, invShearedVector);
}

TEST(Mat4Tests, chaining_transforms_1) {
    Point p(1, 0, 1);
    Mat4 rot = Mat4::RotateXMatrix(Utils::PI / 2.0);
    Mat4 sca = Mat4::ScaleMatrix(5, 5, 5);
    Mat4 tra = Mat4::TranslateMatrix(10, 5, 7);

    Point p2 = rot * p;
    Point ref(1, -1, 0);
    EXPECT_EQ(ref, p2);

    Point p3 = sca * p2;
    ref.set(5, -5, 0);
    EXPECT_EQ(ref, p3);

    Point p4 = tra * p3;
    ref.set(15, 0, 7);
    EXPECT_EQ(ref, p4);

    Mat4 trans = tra * sca * rot;
    EXPECT_EQ(ref, trans * p);

    trans = sca.Translate(5, 5, 5);
    p = trans * p;
    ref.set(30, 25, 30);
    EXPECT_EQ(ref, p);

    // check if inverse of transpose is the same as transpose of the inverse.
    Mat4 mat(2, 2, 0, 5,
             7, 1.5, 0, 1,
             3, -0.5, 2, -2,
             0, 0, 0, 1);
    Mat4 invert(-0.136364, 0.181818, -0, 0.5,
                0.636364, -0.181818, 0, -3,
                0.363636, -0.318182, 0.5, -0.5,
                0, -0, 0, 1);
    Mat4 res1 = mat.inverted();
    std::cout << "invert = " << invert << std::endl;
    std::cout << "res1   = " << res1 << std::endl;
    std::cout << "invert[0][2] = " << invert[0][2] << std::endl;
    std::cout << "res1[0][2]   = " << res1[0][2] << std::endl;
    std::cout << "invert[3][1] = " << invert[3][1] << std::endl;
    std::cout << "res1[3][1]   = " << res1[3][1] << std::endl;
    EXPECT_EQ(invert, res1);

    res1.transpose();
    Mat4 res2 = mat.inverted().transposed();
    Mat4 res3 = mat.transposed();
    res3.invert();
    EXPECT_EQ(res2, res1);
    EXPECT_EQ(res2, res3);
    EXPECT_EQ(res1, res1);
}

TEST(Mat4Tests, chaining_transforms_2) {
    Mat4 mat;
    mat = Mat4::TranslateMatrix(1.5, 0.5, -0.5) * Mat4::ScaleMatrix(0.5, 0.5, 0.5);
    Mat4 ref(0.5, 0, 0, 1.5, 
        0, 0.5, 0, 0.5,
        0, 0, 0.5, -0.5,
        0, 0, 0, 1);
    
    EXPECT_EQ(ref, mat);
}
