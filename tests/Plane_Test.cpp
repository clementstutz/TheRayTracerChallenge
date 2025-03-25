#include "pch.h"
#include "Plane.h"
#include "Ray.h"
#include "Utils.h"

TEST(PlaneTest, constructor_default) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Plane plane;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(plane.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(plane.GetMatrix(), Mat4());
    EXPECT_EQ(plane.GetInvertMatrix(), Mat4());
    EXPECT_EQ(plane.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(plane.GetMaterial(), Material());
    EXPECT_EQ(plane.CanReceiveShadows(), true);
    EXPECT_EQ(plane.CanCastShadows(), true);
    EXPECT_EQ(plane.GetNormal(Point(0, 0, 0), Intersection()), Vector(0, 1, 0));
    
}

TEST(PlaneTest, constructor_copy) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Plane plane_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Plane plane_2(plane_1);
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(plane_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(plane_2.GetMatrix(), plane_1.GetMatrix());
    EXPECT_EQ(plane_2.GetInvertMatrix(), plane_1.GetInvertMatrix());
    EXPECT_EQ(plane_2.GetPosition(), plane_1.GetPosition());
    EXPECT_EQ(plane_2.GetMaterial(), plane_1.GetMaterial());
    EXPECT_EQ(plane_2.CanReceiveShadows(), plane_1.CanReceiveShadows());
    EXPECT_EQ(plane_2.CanCastShadows(), plane_1.CanCastShadows());
    EXPECT_EQ(plane_2.GetNormal(Point(0, 0, 0), Intersection()), plane_1.GetNormal(Point(0, 0, 0), Intersection()));

    Plane plane_3 = plane_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(plane_3.GetId() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(plane_3.GetMatrix(), plane_1.GetMatrix());
    EXPECT_EQ(plane_3.GetInvertMatrix(), plane_1.GetInvertMatrix());
    EXPECT_EQ(plane_3.GetPosition(), plane_1.GetPosition());
    EXPECT_EQ(plane_3.GetMaterial(), plane_1.GetMaterial());
    EXPECT_EQ(plane_3.CanReceiveShadows(), plane_1.CanReceiveShadows());
    EXPECT_EQ(plane_3.CanCastShadows(), plane_1.CanCastShadows());
    EXPECT_EQ(plane_3.GetNormal(Point(0, 0, 0), Intersection()), plane_1.GetNormal(Point(0, 0, 0), Intersection()));
}

TEST(PlaneTest, constructor_move) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();
    std::cout << nbInstanceAlreadyExisting << std::endl;

    Plane plane_1(std::move(Plane()));
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(plane_1.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(plane_1.GetMatrix(), Mat4());
    EXPECT_EQ(plane_1.GetInvertMatrix(), Mat4());
    EXPECT_EQ(plane_1.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(plane_1.GetMaterial(), Material());
    EXPECT_EQ(plane_1.CanReceiveShadows(), true);
    EXPECT_EQ(plane_1.CanCastShadows(), true);
    EXPECT_EQ(plane_1.GetNormal(Point(0, 0, 0), Intersection()), Vector(0, 1, 0));

    Plane plane_2{ Plane() };
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(plane_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(plane_2.GetMatrix(), Mat4());
    EXPECT_EQ(plane_2.GetInvertMatrix(), Mat4());
    EXPECT_EQ(plane_2.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(plane_2.GetMaterial(), Material());
    EXPECT_EQ(plane_2.CanReceiveShadows(), true);
    EXPECT_EQ(plane_2.CanCastShadows(), true);
    EXPECT_EQ(plane_2.GetNormal(Point(0, 0, 0), Intersection()), Vector(0, 1, 0));
}

TEST(PlaneTest, affectation_copy) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Plane plane_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Plane plane_2;
    plane_2 = plane_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);

    EXPECT_EQ(plane_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(plane_2.GetMatrix(), plane_1.GetMatrix());
    EXPECT_EQ(plane_2.GetInvertMatrix(), plane_1.GetInvertMatrix());
    EXPECT_EQ(plane_2.GetPosition(), plane_1.GetPosition());
    EXPECT_EQ(plane_2.GetMaterial(), plane_1.GetMaterial());
    EXPECT_EQ(plane_2.CanReceiveShadows(), plane_1.CanReceiveShadows());
    EXPECT_EQ(plane_2.CanCastShadows(), plane_1.CanCastShadows());
    EXPECT_EQ(plane_2.GetNormal(Point(0, 0, 0), Intersection()), plane_1.GetNormal(Point(0, 0, 0), Intersection()));
}

TEST(PlaneTest, affectation_move) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Plane plane;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(plane.GetId() - nbInstanceAlreadyExisting, 1);

    plane = Plane();
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(plane.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(plane.GetMatrix(), Mat4());
    EXPECT_EQ(plane.GetInvertMatrix(), Mat4());
    EXPECT_EQ(plane.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(plane.GetMaterial(), Material());
    EXPECT_EQ(plane.CanReceiveShadows(), true);
    EXPECT_EQ(plane.CanCastShadows(), true);
    EXPECT_EQ(plane.GetNormal(Point(0, 0, 0), Intersection()), Vector(0, 1, 0));
}

TEST(PlaneTest, transformations) {
    Plane plane;
    plane.SetMatrix(Mat4::ScaleMatrix(2.0, 3.0, 4.0));
    Mat4 ref(2, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 4, 0,
        0, 0, 0, 1);
    EXPECT_EQ(plane.GetMatrix(), ref);

    Point position(4, 5, 6);
    plane.SetPosition(position);
    EXPECT_EQ(plane.GetPosition(), position);
    ref = Mat4(2, 0, 0, 4,
        0, 3, 0, 5,
        0, 0, 4, 6,
        0, 0, 0, 1);
    EXPECT_EQ(plane.GetMatrix(), ref);
}

TEST(PlaneTest, normalOfPlane) {
    // Above untransformed plane
    Plane plane;
    Ray ray(Point(0, 2, 0), Vector(0, -1, 1));
    std::vector<Intersection> intersections = plane.Intersect(ray);

    Point worldPoint(1, 0, 0);
    Vector normal = plane.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(0, 1, 0));

    worldPoint = Point(0, 1, 0);
    normal = plane.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(0, 1, 0));

    worldPoint = Point(0, 0, 1);
    normal = plane.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(0, 1, 0));

    worldPoint = Point(10, 10, -10);
    normal = plane.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(0, 1, 0));

    worldPoint = Point(2, 3, 4);
    normal = plane.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(0, 1, 0));

    // Under untransformed plane
    worldPoint = Point(-5, -3, 10);
    normal = plane.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(0, 1, 0));

    // Transformed plane
    plane.SetMatrix(Mat4::TranslateMatrix(0, 1, 0));
    worldPoint = Point(0.0, 1.7, -0.7);
    normal = plane.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(0, 1, 0));

    Plane plane_2;
    plane_2.SetMatrix(Mat4::RotateZMatrix(Utils::GetPI() / 5.0));
    worldPoint = Point(0.0, sqrt(2) / 2.0, -sqrt(2) / 2.0);
    normal = plane_2.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(-sin(Utils::GetPI() / 5.0), cos(Utils::GetPI() / 5.0), 0));

    Plane plane_3;
    plane_3.SetMatrix(Mat4::ScaleMatrix(0.5, 1, 1) * Mat4::RotateZMatrix(Utils::GetPI() / 5.0));
    worldPoint = Point(0.0, sqrt(2) / 2.0, -sqrt(2) / 2.0);
    normal = plane_3.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(-sin(Utils::GetPI() / 5.0) * 2, cos(Utils::GetPI() / 5.0), 0).Normalize());
}

TEST(PlaneTest, intersect) {
    // Straight on from above
    Plane plane;
    Ray ray(Point(1, 2, 3), Vector(0, -1, 0));
    std::vector<Intersection> intersections = plane.Intersect(ray);
    EXPECT_EQ(1, intersections.size());
    EXPECT_FLOAT_EQ(2.0, intersections[0].getLength());

    // Straight on from below
    ray = Ray(Point(1, -2, 3), Vector(0, 1, 0));
    intersections = plane.Intersect(ray);
    EXPECT_EQ(1, intersections.size());
    EXPECT_FLOAT_EQ(2.0, intersections[0].getLength());

    // At an angle
    ray = Ray(Point(0, 1, 0), Vector(0, -1, 1));
    intersections = plane.Intersect(ray);
    EXPECT_EQ(1, intersections.size());
    EXPECT_FLOAT_EQ(sqrt(2), intersections[0].getLength());
    
    // Parallel
    ray = Ray(Point(1, 2, 3), Vector(0, 0, 1));
    intersections = plane.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    // Coplanar
    ray = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    intersections = plane.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    // On the plane
    ray = Ray(Point(0, 0, 0), Vector(0, -1, 1));
    intersections = plane.Intersect(ray);
    EXPECT_EQ(1, intersections.size());
    EXPECT_FLOAT_EQ(0, intersections[0].getLength());

    // Behind
    ray = Ray(Point(0, 0, 0), Vector(0, 1, 1));
    intersections = plane.Intersect(ray);
    EXPECT_EQ(1, intersections.size());
    EXPECT_FLOAT_EQ(0, intersections[0].getLength());
}

