#include <cmath>

#include "pch.h"
#include "Cylinder.h"
#include "Ray.h"
#include "Utils.h"

TEST(CylinderTests, constructor_default) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Cylinder cylinder;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cylinder.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cylinder.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cylinder.GetMatrix(), Mat4());
    EXPECT_EQ(cylinder.GetInvertMatrix(), Mat4());
}

TEST(CylinderTests, constructor_values) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Cylinder cylinder(-1, 1);
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cylinder.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cylinder.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cylinder.GetMatrix(), Mat4());
    EXPECT_EQ(cylinder.GetInvertMatrix(), Mat4());
}

TEST(CylinderTests, constructor_copy) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Cylinder cylinder_1;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Cylinder cylinder_2(cylinder_1);
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cylinder_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cylinder_2.GetPosition(), cylinder_1.GetPosition());
    EXPECT_EQ(cylinder_2.GetMatrix(), cylinder_1.GetMatrix());
    EXPECT_EQ(cylinder_2.GetInvertMatrix(), cylinder_1.GetInvertMatrix());

    Cylinder cylinder_3 = cylinder_1;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(cylinder_3.GetId() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(cylinder_3.GetPosition(), cylinder_1.GetPosition());
    EXPECT_EQ(cylinder_3.GetMatrix(), cylinder_1.GetMatrix());
    EXPECT_EQ(cylinder_3.GetInvertMatrix(), cylinder_1.GetInvertMatrix());
}

TEST(CylinderTests, constructor_move) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();
    std::cout << nbInstanceAlreadyExisting << std::endl;

    Cylinder cylinder_1(std::move(Cylinder()));
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cylinder_1.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cylinder_1.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cylinder_1.GetMatrix(), Mat4());
    EXPECT_EQ(cylinder_1.GetInvertMatrix(), Mat4());

    Cylinder cylinder_2{ Cylinder() };
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cylinder_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cylinder_2.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cylinder_2.GetMatrix(), Mat4());
    EXPECT_EQ(cylinder_2.GetInvertMatrix(), Mat4());
}

TEST(CylinderTests, affectation_copy) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Cylinder cylinder_1;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Cylinder cylinder_2;
    cylinder_2 = cylinder_1;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 2);

    EXPECT_EQ(cylinder_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cylinder_2.GetPosition(), cylinder_1.GetPosition());
    EXPECT_EQ(cylinder_2.GetMatrix(), cylinder_1.GetMatrix());
    EXPECT_EQ(cylinder_2.GetInvertMatrix(), cylinder_1.GetInvertMatrix());
}

TEST(CylinderTests, affectation_move) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Cylinder cylinder;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cylinder.GetId() - nbInstanceAlreadyExisting, 1);

    cylinder = Cylinder();
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cylinder.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cylinder.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cylinder.GetMatrix(), Mat4());
    EXPECT_EQ(cylinder.GetInvertMatrix(), Mat4());
}

TEST(CylinderTests, transformations) {
    Cylinder cylinder;
    cylinder.SetMatrix(Mat4::ScaleMatrix(2.0, 3.0, 4.0));
    Mat4 ref(2, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 4, 0,
        0, 0, 0, 1);
    EXPECT_EQ(cylinder.GetMatrix(), ref);

    Point position(4, 5, 6);
    cylinder.SetPosition(position);
    EXPECT_EQ(cylinder.GetPosition(), position);
    ref = Mat4(2, 0, 0, 4,
        0, 3, 0, 5,
        0, 0, 4, 6,
        0, 0, 0, 1);
    EXPECT_EQ(cylinder.GetMatrix(), ref);
}

TEST(CylinderTests, intersect) {
    Cylinder cylinder_open(-10, 10);
    Cylinder cylinder_close(-10, 10, true);

    // Form the right
    Ray ray(Point(2, 2, 0), Vector(-1, 0, 0));
    std::vector<Intersection> intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(1.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(3.0, intersections[1].getLength());

    // Form the left
    ray = Ray(Point(-2, 2, 0), Vector(1, 0, 0));
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(1.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(3.0, intersections[1].getLength());

    // Form the back
    ray = Ray(Point(0, 2, 2), Vector(0, 0, -1));
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(1.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(3.0, intersections[1].getLength());

    // Form the front
    ray = Ray(Point(0, 3, -5), Vector(0, 0, 1));
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    // Form the top
    ray = Ray(Point(0.5, 11, 0), Vector(0, -1, 0));
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    intersections = cylinder_close.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(1.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(21.0, intersections[1].getLength());

    // Form the bottom
    ray = Ray(Point(0.5, -11, 0), Vector(0, 1, 0));
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    intersections = cylinder_close.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(1.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(21.0, intersections[1].getLength());

    // Form the inside
    ray = Ray(Point(0.5, 0.5, 0), Vector(1, 0, 0));
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(-1.5, intersections[0].getLength());
    EXPECT_FLOAT_EQ(0.5, intersections[1].getLength());

    ray = Ray(Point(0.5, 0.5, 0), Vector(0, 1, 0));
    intersections = cylinder_close.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(-10.5, intersections[0].getLength());
    EXPECT_FLOAT_EQ(9.5, intersections[1].getLength());

    // From an angle
    ray = Ray(Point(0, 0, -2), Vector(0, 1, 1).Normalize());
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(std::sqrt(2), intersections[0].getLength());
    EXPECT_FLOAT_EQ(3*std::sqrt(2), intersections[1].getLength());

    ray = Ray(Point(2, 0, -2), Vector(-1, 0, 1).Normalize());
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(2.0 * std::sqrt(2) - 1, intersections[0].getLength());
    EXPECT_FLOAT_EQ(2.0 * std::sqrt(2) + 1, intersections[1].getLength());

    // Tangent
    ray = Ray(Point(1, 0, -5), Vector(0, 0, 1));
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(5, intersections[0].getLength());
    EXPECT_FLOAT_EQ(5, intersections[1].getLength());

    ray = Ray(Point(1, 2, 0), Vector(0, 0, 1));
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(0.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(0.0, intersections[1].getLength());

    // Coplanar
    ray = Ray(Point(1, 0, 0), Vector(0, 1, 0));
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    intersections = cylinder_close.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(-10, intersections[0].getLength());
    EXPECT_FLOAT_EQ(10, intersections[1].getLength());

    // Miss
    ray = Ray(Point(0, 0, 0), Vector(0, 1, 0));
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    ray = Ray(Point(2, 0, 2), Vector(0, 0, -1));
    intersections = cylinder_open.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    ray = Ray(Point(1, 11, 0), Vector(-1, 0, 0));
    intersections = cylinder_close.Intersect(ray);
    EXPECT_EQ(0, intersections.size());
}

TEST(CylinderTests, get_normal) {
    Cylinder cylinder_open;
    Cylinder cylinder_close(-1, 1, true);

    // Untransformed cylinder
    Vector normal = cylinder_open.GetNormal(Point(1, 0, 0), Intersection());
    EXPECT_EQ(Vector(1, 0, 0), normal);

    normal = cylinder_open.GetNormal(Point(0, 5, -1), Intersection());
    EXPECT_EQ(Vector(0, 0, -1), normal);

    normal = cylinder_open.GetNormal(Point(0, -2, 1), Intersection());
    EXPECT_EQ(Vector(0, 0, 1), normal);

    normal = cylinder_open.GetNormal(Point(-1, 1, 0), Intersection());
    EXPECT_EQ(Vector(-1, 0, 0), normal);

    normal = cylinder_open.GetNormal(Point(1, 0, -1), Intersection());
    EXPECT_EQ(Vector(std::sqrt(2)/2, 0, -std::sqrt(2)/2), normal);

    normal = cylinder_open.GetNormal(Point(1, 1, 1), Intersection());
    EXPECT_EQ(Vector(std::sqrt(2) / 2, 0, std::sqrt(2) / 2), normal);

    normal = cylinder_open.GetNormal(Point(-1, -1, -1), Intersection());
    EXPECT_EQ(Vector(-std::sqrt(2) / 2, 0, -std::sqrt(2) / 2), normal);

    normal = cylinder_close.GetNormal(Point(0.5, 2, 0.2), Intersection());
    EXPECT_EQ(Vector(0, 1, 0), normal);

    normal = cylinder_close.GetNormal(Point(0.5, -2, 0.2), Intersection());
    EXPECT_EQ(Vector(0, -1, 0), normal);

    // Transformed cylinder
    cylinder_open.SetMatrix(Mat4::TranslateMatrix(0, 1, 0) *
        Mat4::RotateZMatrix(Utils::GetPI() / 4.0));
    normal = cylinder_open.GetNormal(Point(-1, 0, 0), Intersection());
    EXPECT_EQ(Vector(-1, -1, 0).Normalize(), normal);

    cylinder_open.SetMatrix(Mat4::TranslateMatrix(0, 1, 0) *
        Mat4::RotateZMatrix(Utils::GetPI() / 2.0));
    normal = cylinder_open.GetNormal(Point(0, 3, -1), Intersection());
    EXPECT_EQ(Vector(0, 2, -1).Normalize(), normal);

    cylinder_open.SetMatrix(Mat4::RotateZMatrix(Utils::GetPI() / 2.0) *
        Mat4::RotateYMatrix(Utils::GetPI() / 2.0) *
        Mat4::RotateXMatrix(Utils::GetPI() / 2.0));
    normal = cylinder_open.GetNormal(Point(0.5, 0, -1.5), Intersection());
    EXPECT_EQ(Vector(1, 0, -3).Normalize(), normal);

    cylinder_close.SetMatrix(Mat4::TranslateMatrix(0, 1, 0) *
        Mat4::RotateZMatrix(Utils::GetPI() / 2.0));
    normal = cylinder_close.GetNormal(Point(1.5, 1, -0.5), Intersection());
    EXPECT_EQ(Vector(1, 0, 0), normal);
}
