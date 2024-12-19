#include "pch.h"
#include "Ray.h"
#include "Mat4.h"
#include "Utils.h"

TEST(RayTests, constructor_surcharged) {
    Point ori(1, 2, 3);
    Vector dir(3, 4, 0);
    Ray ray(ori, dir);
    EXPECT_EQ(ray.getOrigin(), ori);
    EXPECT_EQ(ray.getDirection(), dir);
}

TEST(RayTests, constructor_copy) {
    Point ori(1, 2, 3);
    Vector dir(3, 4, 0);
    Ray ref(ori, dir);
    Ray ray(ref);
    EXPECT_EQ(ray, ref);
    EXPECT_EQ(ray.getOrigin(), ori);
    EXPECT_EQ(ray.getDirection(), dir);
}

TEST(RayTests, position) {
    Point ori(1, 2, 3);
    Vector dir(3, 4, 0);
    Ray ray(ori, dir);

    Point ref1(4, 6, 3);
    Point ref2(-2, -2, 3);
    Point ref3(8.5, 12, 3);
    EXPECT_EQ(ray.position(0.0), ori);
    EXPECT_EQ(ray.position(1.0), ref1);
    EXPECT_EQ(ray.position(-1.0), ref2);
    EXPECT_EQ(ray.position(2.5), ref3);
}

TEST(RayTests, transform_TranslateMatrix) {
    Ray ray(Point(1, 2, 3), Vector(0, 1, 0));
    Mat4 transMat = Mat4::TranslateMatrix(3, 4, 5);
    Ray result = transMat * ray;

    EXPECT_EQ(result.getOrigin(), Point(4, 6, 8));
    EXPECT_EQ(result.getDirection(), Vector(0, 1, 0));
}

TEST(RayTests, transform_ScaleMatrix) {
    Ray ray(Point(1, 2, 3), Vector(0, 1, 0));
    Mat4 transMat = Mat4::ScaleMatrix(2, 3, 4);
    Ray result = transMat * ray;

    EXPECT_EQ(result.getOrigin(), Point(2, 6, 12));
    EXPECT_EQ(result.getDirection(), Vector(0, 3, 0));
}

TEST(RayTests, transform_RotateMatrix) {
    Ray ray(Point(1, 2, 3), Vector(0, 1, 0));
    Mat4 transMat = Mat4::RotateMatrix(Utils::GetPI()/2.0, Utils::GetPI() / 2.0, Utils::GetPI() / 2.0);
    Ray result = transMat * ray;

    EXPECT_EQ(result.getOrigin(), Point(3, 2, -1));
    EXPECT_EQ(result.getDirection(), Vector(0, 1, 0));
}