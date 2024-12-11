#include "pch.h"
#include "Sphere.h"
#include "Ray.h"
#include "Utils.h"

TEST(SphereTests, constructor_default) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Sphere sphere;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(sphere.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(sphere.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(sphere.GetMatrix(), Mat4());
    EXPECT_EQ(sphere.GetInvertMatrix(), Mat4());
}

TEST(SphereTests, constructor_copy) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Sphere sphere_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Sphere sphere_2(sphere_1);
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetPosition(), sphere_1.GetPosition());
    EXPECT_EQ(sphere_2.GetMatrix(), sphere_1.GetMatrix());
    EXPECT_EQ(sphere_2.GetInvertMatrix(), sphere_1.GetInvertMatrix());

    Sphere sphere_3 = sphere_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(sphere_3.GetId() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(sphere_3.GetPosition(), sphere_1.GetPosition());
    EXPECT_EQ(sphere_3.GetMatrix(), sphere_1.GetMatrix());
    EXPECT_EQ(sphere_3.GetInvertMatrix(), sphere_1.GetInvertMatrix());
}

TEST(SphereTests, constructor_move) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();
    std::cout << nbInstanceAlreadyExisting << std::endl;

    Sphere sphere_1(std::move(Sphere()));
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(sphere_1.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(sphere_1.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(sphere_1.GetMatrix(), Mat4());
    EXPECT_EQ(sphere_1.GetInvertMatrix(), Mat4());

    Sphere sphere_2{Sphere()};
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(sphere_2.GetMatrix(), Mat4());
    EXPECT_EQ(sphere_2.GetInvertMatrix(), Mat4());
}

TEST(SphereTests, affectation_copy) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Sphere sphere_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Sphere sphere_2;
    sphere_2 = sphere_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);

    EXPECT_EQ(sphere_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetPosition(), sphere_1.GetPosition());
    EXPECT_EQ(sphere_2.GetMatrix(), sphere_1.GetMatrix());
    EXPECT_EQ(sphere_2.GetInvertMatrix(), sphere_1.GetInvertMatrix());
}

TEST(SphereTests, affectation_move) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Sphere sphere;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(sphere.GetId() - nbInstanceAlreadyExisting, 1);

    sphere = Sphere();
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(sphere.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(sphere.GetMatrix(), Mat4());
    EXPECT_EQ(sphere.GetInvertMatrix(), Mat4());
}

TEST(SphereTests, transformations) {
    Sphere sphere;
    sphere.SetMatrix(Mat4::ScaleMatrix(2.0, 3.0, 4.0));
    Mat4 ref(2, 0, 0, 0,
             0, 3, 0, 0,
             0, 0, 4, 0,
             0, 0, 0, 1);
    EXPECT_EQ(sphere.GetMatrix(), ref);

    Point position(4, 5, 6);
    sphere.SetPosition(position);
    EXPECT_EQ(sphere.GetPosition(), position);
    ref = Mat4(2, 0, 0, 4,
               0, 3, 0, 5,
               0, 0, 4, 6,
               0, 0, 0, 1);
    EXPECT_EQ(sphere.GetMatrix(), ref);
}

TEST(SphereTests, intersect) {
    // Straight On
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere sphere;
    sphere.SetMatrix(Mat4::ScaleMatrix(2.0, 2.0, 2.0));
    std::vector<Intersection> intersections = sphere.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(3.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(7.0, intersections[1].getLength());

    // Tangent
    ray = Ray(Point(0, 2, -5), Vector(0, 0, 1));
    intersections = sphere.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(5.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(5.0, intersections[1].getLength());

    // Miss
    ray = Ray(Point(0, 3, -5), Vector(0, 0, 1));
    intersections = sphere.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    // Inside
    ray = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    intersections = sphere.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(-2.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(2.0, intersections[1].getLength());

    // Behind
    ray = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    intersections = sphere.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(-7.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(-3.0, intersections[1].getLength());
}

TEST(SphereTests, get_normal) {
    // Untransformed sphere
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere sphere;
    std::vector<Intersection> intersections = sphere.Intersect(ray);

    Point worldPoint(1, 0, 0);
    Vector normal = sphere.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(1, 0, 0));

    worldPoint = Point(0, 1, 0);
    normal = sphere.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(0, 1, 0));

    worldPoint = Point(0, 0, 1);
    normal = sphere.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(0, 0, 1));

    worldPoint = Point(sqrt(3) / 3.0f, sqrt(3) / 3.0f, sqrt(3) / 3.0f);
    normal = sphere.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(sqrt(3) / 3.0f, sqrt(3) / 3.0f, sqrt(3) / 3.0f));

    // Transformed sphere
    sphere.SetMatrix(Mat4::TranslateMatrix(0, 1, 0));
    worldPoint = Point(0.0f, 1.70710678f, -0.70710678f);
    normal = sphere.GetNormal(worldPoint, intersections[0]);
    Vector ref(0, 0.70710678, -0.70710678);
    EXPECT_EQ(normal, ref);

    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::ScaleMatrix(1, 0.5, 1) * Mat4::RotateZMatrix(Utils::PI / 5.0f));
    worldPoint = Point(0.0f, sqrt(2) / 2.0f, -sqrt(2) / 2.0f);
    normal = sphere_2.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(0, 0.9701425, -0.2425356));
}
