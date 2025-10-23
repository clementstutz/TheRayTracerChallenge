#include <cmath>

#include "pch.h"
#include "Group.h"
#include "Sphere.h"
#include "Utils.h"

TEST(GroupTests, constructor_default) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Group group;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(group.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(group.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(group.GetMatrix(), Mat4());
    EXPECT_EQ(group.GetInvertMatrix(), Mat4());
    EXPECT_EQ(group.GetMaterial(), Material());
    EXPECT_EQ(group.GetParent(), nullptr);
    EXPECT_EQ(group.GetChildrens(), std::vector<Shape*>());
}

TEST(GroupTests, affectation_copy) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Group group_1;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);
    Sphere s;
    group_1.AddChildren(s);

    Group group_2;
    group_2 = group_1;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 3);

    EXPECT_EQ(group_2.GetId() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(group_2.GetPosition(), group_1.GetPosition());
    EXPECT_EQ(group_2.GetMatrix(), group_1.GetMatrix());
    EXPECT_EQ(group_2.GetInvertMatrix(), group_1.GetInvertMatrix());
    EXPECT_EQ(group_2.GetMaterial(), group_1.GetMaterial());
    EXPECT_EQ(group_2.GetParent(), group_1.GetParent());
    EXPECT_EQ(group_2.GetChildrens(), group_1.GetChildrens());
}

TEST(GroupTests, affectation_move) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Group group;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(group.GetId() - nbInstanceAlreadyExisting, 1);
    Sphere s;
    group.AddChildren(s);

    group = Group();
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(group.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(group.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(group.GetMatrix(), Mat4());
    EXPECT_EQ(group.GetInvertMatrix(), Mat4());
    EXPECT_EQ(group.GetMaterial(), Material());
    EXPECT_EQ(group.GetParent(), nullptr);
    EXPECT_EQ(group.GetChildrens(), std::vector<Shape*>{});
}

TEST(GroupTests, AddChildren) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Group group;
    Sphere s;
    group.AddChildren(s);
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(group.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(s.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(group.GetChildrens()[0], &s);
    EXPECT_EQ(s.GetParent(), &group);
}

TEST(GroupTests, intersect) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

    Group group;
    std::vector<Intersection> intersections = group.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    Sphere sphere_1;
    Sphere sphere_2;
    sphere_2.SetPosition(Point(0, 0, -3));
    Sphere sphere_3;
    sphere_3.SetPosition(Point(5, 0, 0));
    group.AddChildren(sphere_1);
    group.AddChildren(sphere_2);
    group.AddChildren(sphere_3);
    intersections = group.Intersect(ray);
    EXPECT_EQ(4, intersections.size());
    EXPECT_EQ(sphere_2, intersections[0].getObj());
    EXPECT_FLOAT_EQ(1.0, intersections[0].getLength());
    EXPECT_EQ(sphere_2, intersections[1].getObj());
    EXPECT_FLOAT_EQ(3.0, intersections[1].getLength());
    EXPECT_EQ(sphere_1, intersections[2].getObj());
    EXPECT_FLOAT_EQ(4.0, intersections[2].getLength());
    EXPECT_EQ(sphere_1, intersections[3].getObj());
    EXPECT_FLOAT_EQ(6.0, intersections[3].getLength());
}

TEST(GroupTests, transformations) {
    Group group;
    group.SetMatrix(Mat4::ScaleMatrix(2, 2, 2));
    Mat4 ref(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1);
    EXPECT_EQ(group.GetMatrix(), ref);

    Sphere sphere;
    sphere.SetMatrix(Mat4::TranslateMatrix(5, 0, 0));
    group.AddChildren(sphere);

    Ray ray(Point(10, 0, -10), Vector(0, 0, 1));

    std::vector<Intersection> intersections = group.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(8.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(12.0, intersections[1].getLength());

    Point position(4, 5, 6);
    group.SetPosition(position);
    EXPECT_EQ(group.GetPosition(), position);
    ref = Mat4(2, 0, 0, 4,
        0, 2, 0, 5,
        0, 0, 2, 6,
        0, 0, 0, 1);
    EXPECT_EQ(group.GetMatrix(), ref);
}

TEST(GroupTests, Converting_a_point_from_world_to_object_space) {
    Group group_1;
    group_1.SetMatrix(Mat4::RotateYMatrix(Utils::GetPI() / 2.0));

    Group group_2;
    group_2.SetMatrix(Mat4::ScaleMatrix(2, 2, 2));
    group_1.AddChildren(group_2);

    Sphere sphere;
    sphere.SetMatrix(Mat4::TranslateMatrix(5, 0, 0));
    group_2.AddChildren(sphere);

    Point worldPoint(-2, 0, -10);
    Point objectPoint = sphere.WorldToObject(worldPoint);
    EXPECT_EQ(objectPoint, Point(0, 0, -1));
}

TEST(GroupTests, Converting_a_normal_from_object_to_world_space) {
    Group group_1;
    group_1.SetMatrix(Mat4::RotateYMatrix(Utils::GetPI() / 2.0));

    Group group_2;
    group_2.SetMatrix(Mat4::ScaleMatrix(1, 2, 3));
    group_1.AddChildren(group_2);

    Sphere sphere;
    sphere.SetMatrix(Mat4::TranslateMatrix(5, 0, 0));
    group_2.AddChildren(sphere);

    //Point worldPoint(1.7321, 1.1547, -5.5774);
    Vector localNormal(std::sqrt(3) / 3.0, std::sqrt(3) / 3.0, std::sqrt(3) / 3.0);
    Vector normal = sphere.NormalToWorld(localNormal);
    EXPECT_EQ(normal, Vector(0.2857, 0.4286, -0.8571));
}

TEST(GroupTests, get_normal) {
    Group group_1;
    group_1.SetMatrix(Mat4::RotateYMatrix(Utils::GetPI() / 2.0));

    Group group_2;
    group_2.SetMatrix(Mat4::ScaleMatrix(1, 2, 3));
    group_1.AddChildren(group_2);

    Sphere sphere;
    sphere.SetMatrix(Mat4::TranslateMatrix(5, 0, 0));
    group_2.AddChildren(sphere);

    Point worldPoint(1.7321, 1.1547, -5.5774);
    Vector normal = sphere.GetNormal(worldPoint, Intersection());
    EXPECT_EQ(normal, Vector(0.2857, 0.4286, -0.8571));
}
