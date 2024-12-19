#include "pch.h"
#include "RayObject_for_Test.h"
#include "Ray.h"

TEST(RayObject_for_TestTests, constructor_default) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    RayObject_for_Test rayObject;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(rayObject.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(rayObject.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(rayObject.GetMatrix(), Mat4());
    EXPECT_EQ(rayObject.GetInvertMatrix(), Mat4());
}

TEST(RayObject_for_TestTests, constructor_copy) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    RayObject_for_Test sphere_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);

    RayObject_for_Test sphere_2(sphere_1);
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetPosition(), sphere_1.GetPosition());
    EXPECT_EQ(sphere_2.GetMatrix(), sphere_1.GetMatrix());
    EXPECT_EQ(sphere_2.GetInvertMatrix(), sphere_1.GetInvertMatrix());

    RayObject_for_Test sphere_3 = sphere_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(sphere_3.GetId() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(sphere_3.GetPosition(), sphere_1.GetPosition());
    EXPECT_EQ(sphere_3.GetMatrix(), sphere_1.GetMatrix());
    EXPECT_EQ(sphere_3.GetInvertMatrix(), sphere_1.GetInvertMatrix());
}

TEST(RayObject_for_TestTests, constructor_move) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();
    std::cout << nbInstanceAlreadyExisting << std::endl;

    RayObject_for_Test sphere_1(std::move(RayObject_for_Test()));
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(sphere_1.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(sphere_1.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(sphere_1.GetMatrix(), Mat4());
    EXPECT_EQ(sphere_1.GetInvertMatrix(), Mat4());

    RayObject_for_Test sphere_2{ RayObject_for_Test() };
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(sphere_2.GetMatrix(), Mat4());
    EXPECT_EQ(sphere_2.GetInvertMatrix(), Mat4());
}

TEST(RayObject_for_TestTests, affectation_copy) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    RayObject_for_Test sphere_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);

    RayObject_for_Test sphere_2;
    sphere_2 = sphere_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);

    EXPECT_EQ(sphere_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(sphere_2.GetPosition(), sphere_1.GetPosition());
    EXPECT_EQ(sphere_2.GetMatrix(), sphere_1.GetMatrix());
    EXPECT_EQ(sphere_2.GetInvertMatrix(), sphere_1.GetInvertMatrix());
}

TEST(RayObject_for_TestTests, affectation_move) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    RayObject_for_Test rayObject;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(rayObject.GetId() - nbInstanceAlreadyExisting, 1);

    rayObject = RayObject_for_Test();
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(rayObject.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(rayObject.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(rayObject.GetMatrix(), Mat4());
    EXPECT_EQ(rayObject.GetInvertMatrix(), Mat4());
}

TEST(RayObject_for_TestTests, transformations) {
    RayObject_for_Test rayObject;
    rayObject.SetMatrix(Mat4::ScaleMatrix(2.0, 3.0, 4.0));
    Mat4 ref(2, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 4, 0,
        0, 0, 0, 1);
    EXPECT_EQ(rayObject.GetMatrix(), ref);

    Point position(4, 5, 6);
    rayObject.SetPosition(position);
    EXPECT_EQ(rayObject.GetPosition(), position);
    ref = Mat4(2, 0, 0, 4,
        0, 3, 0, 5,
        0, 0, 4, 6,
        0, 0, 0, 1);
    EXPECT_EQ(rayObject.GetMatrix(), ref);
}

TEST(RayObject_for_TestTests, intersect) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    RayObject_for_Test rayObject;
    std::vector<Intersection> intersections = rayObject.Intersect(ray);
    EXPECT_EQ(1, intersections.size());
    EXPECT_FLOAT_EQ(1.0, intersections[0].getLength());
}

TEST(RayObject_for_TestTests, get_normal) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    RayObject_for_Test rayObject;
    std::vector<Intersection> intersections = rayObject.Intersect(ray);

    Point worldPoint(1, 0, 0);
    Vector normal = rayObject.GetNormal(worldPoint, intersections[0]);
    EXPECT_EQ(normal, Vector(1, 2, 3));
}

TEST(RayObject_for_TestTests, material) {
    RayObject_for_Test rayObject;
    EXPECT_EQ(rayObject.GetMaterial(), Material());

    rayObject.SetMaterial(Material(Color::red, 1, 0.5, 12, 100, 0.75, 0.7, 0.2));
    EXPECT_EQ(rayObject.GetMaterial().GetColor(), Color::red);
    EXPECT_FLOAT_EQ(rayObject.GetMaterial().GetAmbient(), 1.0);
    EXPECT_FLOAT_EQ(rayObject.GetMaterial().GetDiffuse(), 0.5);
    EXPECT_FLOAT_EQ(rayObject.GetMaterial().GetSpecular(), 12.0);
    EXPECT_FLOAT_EQ(rayObject.GetMaterial().GetShininess(), 100.0);
    EXPECT_FLOAT_EQ(rayObject.GetMaterial().GetReflectivity(), 0.75);
    EXPECT_FLOAT_EQ(rayObject.GetMaterial().GetRefractiveIndex(), 0.7);
    EXPECT_FLOAT_EQ(rayObject.GetMaterial().GetTransparency(), 0.2);
}

TEST(RayObject_for_TestTests, lighting) {
    Material m;
    Point p(0, 0, 0);

    // Direct lighting
    Vector eye(0, 0, -1);
    Vector normal(0, 0, -1);
    Light light(Point(0, 0, -10), Color::white);
    RayObject_for_Test test;
    Color result = test.Lighting(p, light, eye, normal, false);
    EXPECT_EQ(Color(1.9, 1.9, 1.9), result);

    // Off angle lighting
    eye = Vector(0, sqrt(2) / 2, -sqrt(2) / 2);
    result = test.Lighting(p, light, eye, normal, false);
    EXPECT_EQ(Color(1, 1, 1), result);

    // Eye opposite surface, light offset 45
    eye = Vector(0, 0, -1);
    light.SetPosition(Point(0, 10, -10));
    result = test.Lighting(p, light, eye, normal, false);
    EXPECT_EQ(Color(0.736396, 0.736396, 0.736396), result);

    // Eye opposite refletion vector
    eye = Vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
    result = test.Lighting(p, light, eye, normal, false);
    EXPECT_EQ(Color(1.63639, 1.63639, 1.63639), result);

    // Lighting behind surface
    eye = Vector(0, 0, -1);
    light.SetPosition(Point(0, 0, 10));
    result = test.Lighting(p, light, eye, normal, false);
    EXPECT_EQ(Color(0.1, 0.1, 0.1), result);
}