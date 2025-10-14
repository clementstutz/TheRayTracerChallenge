#include <cmath>

#include "pch.h"
#include "Shape_for_Test.h"
#include "Ray.h"

TEST(Shape_for_TestTests, constructor_default) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Shape_for_Test shape;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(shape.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(shape.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(shape.GetMatrix(), Mat4());
    EXPECT_EQ(shape.GetInvertMatrix(), Mat4());
}

TEST(Shape_for_TestTests, constructor_copy) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Shape_for_Test sphere_1;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Shape_for_Test sphere_2(sphere_1);
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetPosition(), sphere_1.GetPosition());
    EXPECT_EQ(sphere_2.GetMatrix(), sphere_1.GetMatrix());
    EXPECT_EQ(sphere_2.GetInvertMatrix(), sphere_1.GetInvertMatrix());

    Shape_for_Test sphere_3 = sphere_1;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(sphere_3.GetId() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(sphere_3.GetPosition(), sphere_1.GetPosition());
    EXPECT_EQ(sphere_3.GetMatrix(), sphere_1.GetMatrix());
    EXPECT_EQ(sphere_3.GetInvertMatrix(), sphere_1.GetInvertMatrix());
}

TEST(Shape_for_TestTests, constructor_move) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();
    std::cout << nbInstanceAlreadyExisting << std::endl;

    Shape_for_Test sphere_1(std::move(Shape_for_Test()));
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(sphere_1.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(sphere_1.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(sphere_1.GetMatrix(), Mat4());
    EXPECT_EQ(sphere_1.GetInvertMatrix(), Mat4());

    Shape_for_Test sphere_2{ Shape_for_Test() };
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(sphere_2.GetMatrix(), Mat4());
    EXPECT_EQ(sphere_2.GetInvertMatrix(), Mat4());
}

TEST(Shape_for_TestTests, affectation_copy) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Shape_for_Test sphere_1;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Shape_for_Test sphere_2;
    sphere_2 = sphere_1;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 2);

    EXPECT_EQ(sphere_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetPosition(), sphere_1.GetPosition());
    EXPECT_EQ(sphere_2.GetMatrix(), sphere_1.GetMatrix());
    EXPECT_EQ(sphere_2.GetInvertMatrix(), sphere_1.GetInvertMatrix());
}

TEST(Shape_for_TestTests, affectation_move) {
    int nbInstanceAlreadyExisting = Shape::getNbInstances();

    Shape_for_Test shape;
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(shape.GetId() - nbInstanceAlreadyExisting, 1);

    shape = Shape_for_Test();
    EXPECT_EQ(Shape::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(shape.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(shape.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(shape.GetMatrix(), Mat4());
    EXPECT_EQ(shape.GetInvertMatrix(), Mat4());
}

TEST(Shape_for_TestTests, transformations) {
    Shape_for_Test shape;
    shape.SetMatrix(Mat4::ScaleMatrix(2.0, 3.0, 4.0));
    Mat4 ref(2, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 4, 0,
        0, 0, 0, 1);
    EXPECT_EQ(shape.GetMatrix(), ref);

    Point position(4, 5, 6);
    shape.SetPosition(position);
    EXPECT_EQ(shape.GetPosition(), position);
    ref = Mat4(2, 0, 0, 4,
        0, 3, 0, 5,
        0, 0, 4, 6,
        0, 0, 0, 1);
    EXPECT_EQ(shape.GetMatrix(), ref);
}

TEST(Shape_for_TestTests, intersect) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Shape_for_Test shape;
    std::vector<Intersection> intersections = shape.Intersect(ray);
    EXPECT_EQ(1, intersections.size());
    EXPECT_FLOAT_EQ(1.0, intersections[0].getLength());
}

TEST(Shape_for_TestTests, get_normal) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Shape_for_Test shape;
    std::vector<Intersection> intersections = shape.Intersect(ray);

    Point worldPoint(1, 0, 0);
    Vector normal = shape.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(1, 2, 3));
}

TEST(Shape_for_TestTests, material) {
    Shape_for_Test shape;
    EXPECT_EQ(shape.GetMaterial(), Material());

    shape.SetMaterial(Material(Color::red, 1, 0.5, 12, 100, 0.75, 0.7, 0.2));
    EXPECT_EQ(shape.GetMaterial().GetColor(), Color::red);
    EXPECT_FLOAT_EQ(shape.GetMaterial().GetAmbient(), 1.0);
    EXPECT_FLOAT_EQ(shape.GetMaterial().GetDiffuse(), 0.5);
    EXPECT_FLOAT_EQ(shape.GetMaterial().GetSpecular(), 12.0);
    EXPECT_FLOAT_EQ(shape.GetMaterial().GetShininess(), 100.0);
    EXPECT_FLOAT_EQ(shape.GetMaterial().GetReflectivity(), 0.75);
    EXPECT_FLOAT_EQ(shape.GetMaterial().GetRefractiveIndex(), 0.7);
    EXPECT_FLOAT_EQ(shape.GetMaterial().GetTransparency(), 0.2);
    EXPECT_EQ(shape.GetMaterial().GetPattern(), nullptr);
}

TEST(Shape_for_TestTests, lighting) {
    Material m;
    Point p(0, 0, 0);

    // Direct lighting
    Vector eye(0, 0, -1);
    Vector normal(0, 0, -1);
    Light light(Point(0, 0, -10), Color::white);
    Shape_for_Test test;
    Color result = test.Lighting(p, light, eye, normal, false);
    EXPECT_EQ(Color(1.9, 1.9, 1.9), result);

    // Off angle lighting
    eye = Vector(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
    result = test.Lighting(p, light, eye, normal, false);
    EXPECT_EQ(Color(1, 1, 1), result);

    // Eye opposite surface, light offset 45
    eye = Vector(0, 0, -1);
    light.SetPosition(Point(0, 10, -10));
    result = test.Lighting(p, light, eye, normal, false);
    EXPECT_EQ(Color(0.736396, 0.736396, 0.736396), result);

    // Eye opposite refletion vector
    eye = Vector(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
    result = test.Lighting(p, light, eye, normal, false);
    EXPECT_EQ(Color(1.63639, 1.63639, 1.63639), result);

    // Lighting behind surface
    eye = Vector(0, 0, -1);
    light.SetPosition(Point(0, 0, 10));
    result = test.Lighting(p, light, eye, normal, false);
    EXPECT_EQ(Color(0.1, 0.1, 0.1), result);
}
