#include "pch.h"
#include "Camera.h"

TEST(CameraTests, constructor_default) {
}

TEST(CameraTests, constructor_values) {
}

TEST(CameraTests, TransformMatrixForDefaultOrientation) {
    Point from(0, 0, 0);
    Point to(0, 0, -1);
    Vector up(0, 1, 0);
    Camera camera;
    //Something... Transform(from, to, up);
    Mat4 viewTransform = camera.ViewTransform(from, to, up);
    EXPECT_EQ(Mat4(), viewTransform);
}

TEST(CameraTests, TransformMatrixLookingZDirection) {
    Point from(0, 0, 0);
    Point to(0, 0, 1);
    Vector up(0, 1, 0);
    Camera camera;
    Mat4 viewTransform = camera.ViewTransform(from, to, up);
    EXPECT_EQ(Mat4::ScaleMatrix(-1, 1, -1), viewTransform);
}

TEST(CameraTests, TransformMovesTheWorld) {
    Point from(0, 0, 8);
    Point to(0, 0, 0);
    Vector up(0, 1, 0);
    Camera camera;
    Mat4 viewTransform = camera.ViewTransform(from, to, up);
    EXPECT_EQ(Mat4::TranslateMatrix(0, 0, -8), viewTransform);
}

TEST(CameraTests, TransformArbitrary) {
    Point from(1, 3, 2);
    Point to(4, -2, 8);
    Vector up(1, 1, 0);
    Camera camera;
    Mat4 viewTransform = camera.ViewTransform(from, to, up);
    // this matrix works if we don't normalize all the vector in the ViewTransform() method
    // but it seems that we should definitly normalize them...!
    /*Mat4 mat(-0.50709, 0.50709, 0.67612, -2.36643,
             0.76772, 0.60609, 0.12122, -2.82843,
             -0.35857, 0.59761, -0.71714, 0,
             0.00000, 0.00000, 0.00000, 1.00000);*/
    Mat4 mat(-0.51450, 0.51450, 0.68599, -2.40098,
        0.77892, 0.61494, 0.12299, -2.86972,
        -0.35857, 0.59761, -0.71714, 0.00000,
        0.00000, 0.00000, 0.00000, 1.00000);
    EXPECT_EQ(mat, viewTransform);
}

TEST(CameraTests, ConstructingACamera) {
    int hSize = 160;
    int vSize = 120;
    float fieldOfView = Utils::PI / 2.0;
    Camera camera(hSize, vSize, fieldOfView);

    EXPECT_EQ(hSize, camera.GetHSize());
    EXPECT_EQ(vSize, camera.GetVSize());
    EXPECT_EQ(fieldOfView, camera.GetFov());
    EXPECT_EQ(Mat4(), camera.GetTransform());
}

TEST(CameraTests, PixelSize) {
    Camera camera_1(200, 125, Utils::PI / 2.0);
    EXPECT_TRUE(Utils::FE(0.01, camera_1.GetPixelSize()));

    Camera camera_2(125, 200, Utils::PI / 2.0);
    EXPECT_TRUE(Utils::FE(0.01, camera_2.GetPixelSize()));
}