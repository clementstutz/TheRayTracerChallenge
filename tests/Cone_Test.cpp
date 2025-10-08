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
    /*Ray ray(Point(5, 0.5, 0), Vector(-1, 0, 0));
    std::vector<Intersection> intersections = cone.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.8660254037, intersections[0].getLength());
    EXPECT_FLOAT_EQ(6.1339745963, intersections[1].getLength());*/

    //// Form the left
    //ray = Ray(Point(-5, 0.5, 0), Vector(1, 0, 0));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(2, intersections.size());
    //EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    //EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    //// Form the top
    //ray = Ray(Point(0.5, 5, 0), Vector(0, -1, 0));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(2, intersections.size());
    //EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    //EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    //// Form the bottom
    //ray = Ray(Point(0.5, -5, 0), Vector(0, 1, 0));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(2, intersections.size());
    //EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    //EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    //// Form the back
    //ray = Ray(Point(0.5, 0, 5), Vector(0, 0, -1));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(2, intersections.size());
    //EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    //EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    //// Form the front
    //ray = Ray(Point(0.5, 0, -5), Vector(0, 0, 1));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(2, intersections.size());
    //EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    //EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    //// Form the inside
    //ray = Ray(Point(0, 0.5, 0), Vector(0, 0, 1));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(2, intersections.size());
    //EXPECT_FLOAT_EQ(-1.0, intersections[0].getLength());
    //EXPECT_FLOAT_EQ(1.0, intersections[1].getLength());

    //// Tangent
    //ray = Ray(Point(0, 1, -5), Vector(0, 0, 1));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(2, intersections.size());
    //EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    //EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    //// Miss
    //ray = Ray(Point(-2, 0, 0), Vector(0.2673, 0.5345, 0.8018));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(0, intersections.size());

    //ray = Ray(Point(0, -2, 0), Vector(0.8018, 0.2673, 0.5345));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(0, intersections.size());

    //ray = Ray(Point(0, 0, -2), Vector(0.5345, 0.8018, 0.2673));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(0, intersections.size());

    //ray = Ray(Point(2, 0, 2), Vector(0, 0, -1));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(0, intersections.size());

    //ray = Ray(Point(0, 2, 2), Vector(0, -1, 0));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(0, intersections.size());

    //ray = Ray(Point(2, 2, 0), Vector(-1, 0, 0));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(0, intersections.size());

    //ray = Ray(Point(0, 3, -5), Vector(0, 0, 1));
    //intersections = cone.Intersect(ray);
    //EXPECT_EQ(0, intersections.size());
}

TEST(ConeTests, get_normal) {
    Cone cone;

    // Untransformed cone
    Vector normal = cone.GetNormal(Point(0, 0, 0), Intersection());
    //EXPECT_EQ(Vector(0, 0, 0), normal);

    normal = cone.GetNormal(Point(1, 1, 1), Intersection());
    EXPECT_EQ(Vector(1, -std::sqrt(2), 1).Normalize(), normal);

    normal = cone.GetNormal(Point(-1, -1, 0), Intersection());
    EXPECT_EQ(Vector(-1, 1, 0).Normalize(), normal);

    normal = cone.GetNormal(Point(-1, -1, -1), Intersection());
    EXPECT_EQ(Vector(-1, std::sqrt(2), -1).Normalize(), normal);

    // Transformed cone
    cone.SetMatrix(Mat4::TranslateMatrix(0, 1, 0) *
        Mat4::RotateZMatrix(Utils::GetPI() / 4.0));
    normal = cone.GetNormal(Point(-0.5, 0, 0), Intersection());
    EXPECT_EQ(Vector(-1, 0, 0), normal);

    cone.SetMatrix(Mat4::TranslateMatrix(0, 1, 0) *
        Mat4::RotateZMatrix(Utils::GetPI() / 4.0));
    normal = cone.GetNormal(Point(-0.5, 1, 0), Intersection());
    EXPECT_EQ(Vector(0, -1, 0), normal);
}
