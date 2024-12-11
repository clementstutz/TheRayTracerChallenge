#include "pch.h"
#include "Computations.h"
#include "Scene.h"
#include "Sphere.h"

TEST(ComputationsTests, Precomputations) {
    Scene scene;

    Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Light light(Point(0, 0, -5), Color(1, 1, 1));

    // On the outside.
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

    std::vector<Intersection> intersections = scene.Intersections(ray);
    Intersection hit = scene.Hit(intersections);

    Computations c = Computations::Prepare(hit, ray, nullptr);

    EXPECT_EQ(4, c.GetLength());
    EXPECT_EQ(hit.getObj(), c.GetRayObject());
    EXPECT_EQ(&hit.getObj(), c.GetRayObjectPtr());
    EXPECT_EQ(Point(0, 0, -1), c.GetPoint());
    EXPECT_EQ(Vector(0, 0, -1), c.GetEye());
    EXPECT_EQ(Vector(0, 0, -1), c.GetNormal());
    EXPECT_EQ(false, c.GetInside());
    EXPECT_EQ(Point(0, 0, -1) + Vector(0, 0, -1) * Utils::GetEpsilon(), c.GetOverPoint());
    EXPECT_EQ(Point(0, 0, -1) - Vector(0, 0, -1) * Utils::GetEpsilon(), c.GetUnderPoint());
    EXPECT_EQ(Vector(0, 0, -1), c.GetReflectVector());
    EXPECT_EQ(RefractiveIndex::Vacuum, c.GetN1());
    EXPECT_EQ(RefractiveIndex::Vacuum, c.GetN2());

    // On the inside.
    ray = Ray(Point(0, 0, 0), Vector(0, 0, 1));

    intersections = scene.Intersections(ray);
    hit = scene.Hit(intersections);

    c = Computations::Prepare(hit, ray, nullptr);

    EXPECT_EQ(0.5, c.GetLength());
    EXPECT_EQ(hit.getObj(), c.GetRayObject());
    EXPECT_EQ(&hit.getObj(), c.GetRayObjectPtr());
    EXPECT_EQ(Point(0, 0, 0.5), c.GetPoint());
    EXPECT_EQ(Vector(0, 0, -1), c.GetEye());
    EXPECT_EQ(Vector(0, 0, -1), c.GetNormal());
    EXPECT_EQ(true, c.GetInside());
    EXPECT_EQ(Point(0, 0, 0.5) + Vector(0, 0, -1) * Utils::GetEpsilon(), c.GetOverPoint());
    EXPECT_EQ(Point(0, 0, 0.5) - Vector(0, 0, -1) * Utils::GetEpsilon(), c.GetUnderPoint());
    EXPECT_EQ(Vector(0, 0, -1), c.GetReflectVector());
    EXPECT_EQ(RefractiveIndex::Vacuum, c.GetN1());
    EXPECT_EQ(RefractiveIndex::Vacuum, c.GetN2());
}