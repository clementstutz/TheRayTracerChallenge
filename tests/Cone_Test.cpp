#include <cmath>

#include "pch.h"
#include "Cone.h"
#include "Ray.h"
#include "Utils.h"

TEST(ConeTests, constructor_default) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Cone cone;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cone.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cone.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cone.GetMatrix(), Mat4());
    EXPECT_EQ(cone.GetInvertMatrix(), Mat4());
}

TEST(ConeTests, constructor_values) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Cone cone(-1, 1);
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cone.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cone.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cone.GetMatrix(), Mat4());
    EXPECT_EQ(cone.GetInvertMatrix(), Mat4());
}

TEST(ConeTests, constructor_copy) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Cone cone_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Cone cone_2(cone_1);
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cone_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cone_2.GetPosition(), cone_1.GetPosition());
    EXPECT_EQ(cone_2.GetMatrix(), cone_1.GetMatrix());
    EXPECT_EQ(cone_2.GetInvertMatrix(), cone_1.GetInvertMatrix());

    Cone cone_3 = cone_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(cone_3.GetId() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(cone_3.GetPosition(), cone_1.GetPosition());
    EXPECT_EQ(cone_3.GetMatrix(), cone_1.GetMatrix());
    EXPECT_EQ(cone_3.GetInvertMatrix(), cone_1.GetInvertMatrix());
}

TEST(ConeTests, constructor_move) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();
    std::cout << nbInstanceAlreadyExisting << std::endl;

    Cone cone_1(std::move(Cone()));
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cone_1.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cone_1.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cone_1.GetMatrix(), Mat4());
    EXPECT_EQ(cone_1.GetInvertMatrix(), Mat4());

    Cone cone_2{ Cone() };
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cone_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cone_2.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cone_2.GetMatrix(), Mat4());
    EXPECT_EQ(cone_2.GetInvertMatrix(), Mat4());
}

TEST(ConeTests, affectation_copy) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Cone cone_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Cone cone_2;
    cone_2 = cone_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);

    EXPECT_EQ(cone_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cone_2.GetPosition(), cone_1.GetPosition());
    EXPECT_EQ(cone_2.GetMatrix(), cone_1.GetMatrix());
    EXPECT_EQ(cone_2.GetInvertMatrix(), cone_1.GetInvertMatrix());
}

TEST(ConeTests, affectation_move) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Cone cone;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cone.GetId() - nbInstanceAlreadyExisting, 1);

    cone = Cone();
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cone.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cone.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cone.GetMatrix(), Mat4());
    EXPECT_EQ(cone.GetInvertMatrix(), Mat4());
}

TEST(ConeTests, transformations) {
    Cone cone;
    cone.SetMatrix(Mat4::ScaleMatrix(2.0, 3.0, 4.0));
    Mat4 ref(2, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 4, 0,
        0, 0, 0, 1);
    EXPECT_EQ(cone.GetMatrix(), ref);

    Point position(4, 5, 6);
    cone.SetPosition(position);
    EXPECT_EQ(cone.GetPosition(), position);
    ref = Mat4(2, 0, 0, 4,
        0, 3, 0, 5,
        0, 0, 4, 6,
        0, 0, 0, 1);
    EXPECT_EQ(cone.GetMatrix(), ref);
}

TEST(ConeTests, intersect) {
    Cone cone;
    Cone cone_open(-5, 5);
    Cone cone_close(-5, 5, true);

    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    std::vector<Intersection> intersections = cone.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(5, intersections[0].getLength());
    EXPECT_FLOAT_EQ(5, intersections[1].getLength());

    ray = Ray(Point(0, 0, -5), Vector(1, 1, 1).Normalize());
    intersections = cone.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(8.660254, intersections[0].getLength());
    EXPECT_FLOAT_EQ(8.660254, intersections[1].getLength());

    ray = Ray(Point(1, 1, -5), Vector(-0.5, -1, 1).Normalize());
    intersections = cone.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.550055, intersections[0].getLength());
    EXPECT_FLOAT_EQ(49.44994, intersections[1].getLength());

    // Form the right
    ray = Ray(Point(5, 0.5, 0), Vector(-1, 0, 0));
    intersections = cone.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.5, intersections[0].getLength());
    EXPECT_FLOAT_EQ(5.5, intersections[1].getLength());

    // Form the left
    ray = Ray(Point(-5, 0.5, 0), Vector(1, 0, 0));
    intersections = cone.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.5, intersections[0].getLength());
    EXPECT_FLOAT_EQ(5.5, intersections[1].getLength());

    // Form the top
    ray = Ray(Point(10, 11, 0), Vector(0, -1, 0));
    intersections = cone.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(1, intersections[0].getLength());
    EXPECT_FLOAT_EQ(21, intersections[1].getLength());

    ray = Ray(Point(0.5, 10, 0), Vector(0, -1, 0));
    intersections = cone_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(9.5, intersections[0].getLength());
    EXPECT_FLOAT_EQ(10.5, intersections[1].getLength());

    intersections = cone_close.Intersect(ray);
    EXPECT_EQ(4, intersections.size());
    EXPECT_FLOAT_EQ(5.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(9.5, intersections[1].getLength());
    EXPECT_FLOAT_EQ(10.5, intersections[2].getLength());
    EXPECT_FLOAT_EQ(15.0, intersections[3].getLength());

    // Form the bottom
    ray = Ray(Point(0.5, -10, 0), Vector(0, 1, 0));
    intersections = cone_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(9.5, intersections[0].getLength());
    EXPECT_FLOAT_EQ(10.5, intersections[1].getLength());

    intersections = cone_close.Intersect(ray);
    EXPECT_EQ(4, intersections.size());
    EXPECT_FLOAT_EQ(5.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(9.5, intersections[1].getLength());
    EXPECT_FLOAT_EQ(10.5, intersections[2].getLength());
    EXPECT_FLOAT_EQ(15.0, intersections[3].getLength());

    // Form the back
    ray = Ray(Point(0, 1, 5), Vector(0, 0, -1));
    intersections = cone.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    // Form the front
    ray = Ray(Point(0, 1, -5), Vector(0, 0, 1));
    intersections = cone.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    // Form the inside
    ray = Ray(Point(0, 0.5, 0), Vector(0, 0, 1));
    intersections = cone_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(-0.5, intersections[0].getLength());
    EXPECT_FLOAT_EQ(0.5, intersections[1].getLength());

    ray = Ray(Point(0, 0.5, 0), Vector(0, 1, 0));
    intersections = cone_open.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(-0.5, intersections[0].getLength());
    EXPECT_FLOAT_EQ(-0.5, intersections[1].getLength());

    intersections = cone_close.Intersect(ray);
    EXPECT_EQ(4, intersections.size());
    EXPECT_FLOAT_EQ(-5.5, intersections[0].getLength());
    EXPECT_FLOAT_EQ(-0.5, intersections[1].getLength());
    EXPECT_FLOAT_EQ(-0.5, intersections[2].getLength());
    EXPECT_FLOAT_EQ(4.5, intersections[3].getLength());

    // Tangent
    ray = Ray(Point(1, 1, -5), Vector(0, 0, 1));
    intersections = cone.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(5.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(5.0, intersections[1].getLength());

    // Miss
    ray = Ray(Point(-1, 0.5, 0), Vector(0, 0, 1));
    intersections = cone.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    ray = Ray(Point(0, 10, 0), Vector(0, 0, 1));
    intersections = cone_open.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    ray = Ray(Point(10, 10, 0), Vector(0, -1, 0));
    intersections = cone_open.Intersect(ray);
    EXPECT_EQ(0, intersections.size());
}

TEST(ConeTests, get_normal) {
    Cone cone_open;
    Cone cone_close(-1, 1, true);

    // Untransformed cone
    Vector normal = cone_open.GetNormal(Point(0, 0, 0), Intersection());
    //EXPECT_EQ(Vector(0, 0, 0), normal);

    normal = cone_open.GetNormal(Point(1, 1, 0), Intersection());
    EXPECT_EQ(Vector(1, -1, 0).Normalize(), normal);

    normal = cone_open.GetNormal(Point(-1, -1, 0), Intersection());
    EXPECT_EQ(Vector(-1, 1, 0).Normalize(), normal);

    normal = cone_open.GetNormal(Point(1, 1, 1), Intersection());
    EXPECT_EQ(Vector(1, -std::sqrt(2), 1).Normalize(), normal);

    normal = cone_open.GetNormal(Point(-1, -1, -1), Intersection());
    EXPECT_EQ(Vector(-1, std::sqrt(2), -1).Normalize(), normal);

    normal = cone_close.GetNormal(Point(0.5, 1, 0.2), Intersection());
    EXPECT_EQ(Vector(0, 1, 0).Normalize(), normal);

    normal = cone_close.GetNormal(Point(0.5, 2, 0.2), Intersection());
    EXPECT_EQ(Vector(0, 1, 0).Normalize(), normal);

    normal = cone_close.GetNormal(Point(0.5, -1, 0.2), Intersection());
    EXPECT_EQ(Vector(0, -1, 0).Normalize(), normal);

    // Transformed cone
    cone_open.SetMatrix(Mat4::TranslateMatrix(0, 1, 0) *
        Mat4::RotateZMatrix(Utils::GetPI() / 4.0));
    normal = cone_open.GetNormal(Point(-0.5, 0, 0), Intersection());
    EXPECT_EQ(Vector(-1, 0, 0), normal);

    cone_open.SetMatrix(Mat4::TranslateMatrix(0, 1, 0) *
        Mat4::RotateZMatrix(Utils::GetPI() / 4.0));
    normal = cone_open.GetNormal(Point(-0.5, 1, 0), Intersection());
    EXPECT_EQ(Vector(0, -1, 0), normal);
}
