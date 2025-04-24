#include "pch.h"
#include "Computations.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Pattern_for_Test.h"

TEST(ComputationsTests, Precomputations) {
    Scene scene;
    Light light(Point(0, 0, -5), Color(1, 1, 1));

    Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    // On the outside.
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

    std::vector<Intersection> intersections = scene.Intersections(ray);
    Intersection hit = scene.Hit(intersections);

    Computations c = Computations::Prepare(hit, ray);

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

    c = Computations::Prepare(hit, ray);

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

TEST(ComputationsTests, NonReflectiveSurface) {
    Scene scene;
    Light light(Point(0, 2, -5), Color(1, 1, 1));

    Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color::white, 1));

    // On the outside.
    Ray ray(Point(0, 0, 0), Vector(0, 0, 1));

    std::vector<Intersection> intersections = scene.Intersections(ray);
    Intersection hit = scene.Hit(intersections);

    Computations c = Computations::Prepare(hit, ray);

    Color color = scene.ReflectedColor(c);

    EXPECT_EQ(color, Color::black);
}

TEST(ComputationsTests, ReflectiveSurface) {
    Scene scene;
    scene.DefaultScene();

    Plane plane;
    plane.SetMaterial(Material(Color::white, 0.1, 0.9, 0.9, 200, 0.5));
    plane.SetMatrix(Mat4::TranslateMatrix(0, -1, 0));

    // On the outside.
    Ray ray(Point(0, 0, -3), Vector(0, -std::sqrt(2)/2.0, std::sqrt(2) / 2.0));

    std::vector<Intersection> intersections = scene.Intersections(ray);
    Intersection hit = scene.Hit(intersections);
    std::cout << hit << std::endl;

    Computations c = Computations::Prepare(hit, ray);

    Color color = scene.ReflectedColor(c);

    EXPECT_EQ(color, Color(0.19032, 0.2379, 0.14274));
}

TEST(ComputationsTests, UpdateShadeHit) {
    Scene scene;
    scene.DefaultScene();

    Plane plane;
    plane.SetMaterial(Material(Color::white, 0.1, 0.9, 0.9, 200, 0.5));
    plane.SetMatrix(Mat4::TranslateMatrix(0, -1, 0));

    // On the outside.
    Ray ray(Point(0, 0, -3), Vector(0, -std::sqrt(2)/2.0, std::sqrt(2) / 2.0));

    std::vector<Intersection> intersections = scene.Intersections(ray);
    Intersection hit = scene.Hit(intersections);
    std::cout << hit << std::endl;

    Computations c = Computations::Prepare(hit, ray);

    Color color = scene.ShadeHit(c);

    EXPECT_EQ(color, Color(0.87677, 0.92436, 0.82918));
}

TEST(ComputationsTests, AvoidInfinitRecursion) {
    Scene scene;
    Light light(Point(0, 0, 0), Color(1, 1, 1));

    Plane plane_lower;
    plane_lower.SetMaterial(Material(Color::white, 0.1, 0.9, 0.9, 200, 1));
    plane_lower.SetMatrix(Mat4::TranslateMatrix(0, -1, 0));

    Plane plane_upper;
    plane_upper.SetMaterial(Material(Color::white, 0.1, 0.9, 0.9, 200, 1));
    plane_upper.SetMatrix(Mat4::TranslateMatrix(0, 1, 0));

    // On the outside.
    Ray ray(Point(0, 0, 0), Vector(0, 1, 0));

    std::vector<Intersection> intersections = scene.Intersections(ray);
    Intersection hit = scene.Hit(intersections);
    std::cout << hit << std::endl;

    Computations c = Computations::Prepare(hit, ray);

    double factor_upper = plane_upper.GetMaterial().GetAmbient() + plane_upper.GetMaterial().GetDiffuse() + plane_upper.GetMaterial().GetSpecular();
    Color color_upper(plane_upper.GetMaterial().GetColor() * factor_upper);
    double factor_lower = plane_lower.GetMaterial().GetAmbient() + plane_lower.GetMaterial().GetDiffuse() + plane_lower.GetMaterial().GetSpecular();
    Color color_lower(plane_lower.GetMaterial().GetColor() * factor_lower);
    
    int recursion = 1;
    Color color_ref = color_upper * ((recursion + 2) / 2) + color_upper * ((recursion + 1) / 2);
    Color color = scene.ColorAt(ray, recursion);
    EXPECT_EQ(color, color_ref);

    recursion = 5;
    color_ref = color_upper * ((recursion + 2) / 2) + color_upper * ((recursion + 1) / 2);
    color = scene.ColorAt(ray, recursion);
    EXPECT_EQ(color, color_ref);
}

TEST(ComputationsTests, LimitRecursion) {
    Scene scene;
    scene.DefaultScene();

    Plane plane;
    plane.SetMaterial(Material(Color::white, 0.1, 0.9, 0.9, 200, 0.5));
    plane.SetMatrix(Mat4::TranslateMatrix(0, -1, 0));

    // On the outside.
    Ray ray(Point(0, 0, -3), Vector(0, -std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));

    std::vector<Intersection> intersections = scene.Intersections(ray);
    Intersection hit = scene.Hit(intersections);

    Computations c = Computations::Prepare(hit, ray);

    Color color = scene.ReflectedColor(c, 0);

    EXPECT_EQ(Color(0, 0, 0), color);
}

TEST(ComputationsTests, NIntersections) {
    Scene scene;

    Sphere a;
    a.SetMatrix(Mat4::ScaleMatrix(2, 2, 2));
    Material m;
    m.SetTransparency(1);
    m.SetRefractiveIndex(1.5);
    a.SetMaterial(m);

    Sphere b;
    b.SetMatrix(Mat4::TranslateMatrix(0, 0, -0.25));
    m.SetTransparency(1);
    m.SetRefractiveIndex(2);
    b.SetMaterial(m);

    Sphere c;
    c.SetMatrix(Mat4::TranslateMatrix(0, 0, 0.25));
    m.SetTransparency(1);
    m.SetRefractiveIndex(2.5);
    c.SetMaterial(m);

    Ray ray(Point(0, 0, -4), Vector(0, 0, 1));

    std::vector<Intersection> i = scene.Intersections(ray);
    
    Computations comp = Computations::Prepare(i[0], ray, &i);
    EXPECT_FLOAT_EQ(1.0, comp.GetN1());
    EXPECT_FLOAT_EQ(1.5, comp.GetN2());

    comp = Computations::Prepare(i[1], ray, &i);
    EXPECT_FLOAT_EQ(1.5, comp.GetN1());
    EXPECT_FLOAT_EQ(2.0, comp.GetN2());

    comp = Computations::Prepare(i[2], ray, &i);
    EXPECT_FLOAT_EQ(2.0, comp.GetN1());
    EXPECT_FLOAT_EQ(2.5, comp.GetN2());

    comp = Computations::Prepare(i[3], ray, &i);
    EXPECT_FLOAT_EQ(2.5, comp.GetN1());
    EXPECT_FLOAT_EQ(2.5, comp.GetN2());

    comp = Computations::Prepare(i[4], ray, &i);
    EXPECT_FLOAT_EQ(2.5, comp.GetN1());
    EXPECT_FLOAT_EQ(1.5, comp.GetN2());

    comp = Computations::Prepare(i[5], ray, &i);
    EXPECT_FLOAT_EQ(1.5, comp.GetN1());
    EXPECT_FLOAT_EQ(1.0, comp.GetN2());
}

TEST(ComputationsTests, UnderPoint) {
    Scene scene;

    Sphere sphere;
    sphere.SetMaterial(Material(Color::white, 0.1, 0, 0.9, 200, 0, 1.52, 1));
    sphere.SetMatrix(Mat4::TranslateMatrix(0, 0, 1));

    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

    std::vector<Intersection> intersections = scene.Intersections(ray);
    Intersection hit = scene.Hit(intersections);

    Computations c = Computations::Prepare(hit, ray, &intersections);

    EXPECT_TRUE(c.GetUnderPoint().getZ() > Utils::GetEpsilon() / 2.0);
    EXPECT_TRUE(c.GetUnderPoint().getZ() < Utils::GetEpsilon() * 2.0);
    EXPECT_TRUE(c.GetPoint().getZ() < c.GetUnderPoint().getZ());
}

TEST(ComputationsTests, RefractedColorOfOpaque) {
    Scene scene;
    Light light(Point(-10, 10, -10), Color::white);

    Sphere s;
    s.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));

    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

    std::vector<Intersection> hits = scene.Intersections(ray);

    Computations c = Computations::Prepare(hits[0], ray, &hits);
    Color color = scene.RefractedColor(c, 5);
    EXPECT_EQ(Color::black, color);
}

TEST(ComputationsTests, RefractedColorAtMaxRecusionDepth) {
    Scene scene;
    Light light(Point(-10, 10, -10), Color::white);

    Sphere s;
    s.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200, 0, 1.5, 1.0));

    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

    std::vector<Intersection> hits = scene.Intersections(ray);

    Computations c = Computations::Prepare(hits[0], ray, &hits);
    Color color = scene.RefractedColor(c, 0);
    EXPECT_EQ(Color::black, color);
}

TEST(ComputationsTests, TotalinternalReflection) {
    Scene scene;
    Light light(Point(-10, 10, -10), Color::white);

    Sphere s;
    s.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200, 0, 1.5, 1.0));

    Ray ray(Point(0, 0, std::sqrt(2)/2.0), Vector(0, 1, 0));

    std::vector<Intersection> hits = scene.Intersections(ray);

    Computations c = Computations::Prepare(hits[0], ray, &hits);
    Color color = scene.RefractedColor(c, 0);
    EXPECT_EQ(Color::black, color);
}

TEST(ComputationsTests, FindRefractedColor) {
    Scene scene;
    Light light(Point(-10, 10, -10), Color::white);

    Pattern_for_Test pattern;
    Material m_1(Color(0.8, 1.0, 0.6), 1.0, 0.7, 0.2);
    m_1.SetPattern(pattern);
    Sphere s_1;
    s_1.SetMaterial(m_1);

    Material m_2;
    m_2.SetTransparency(1.0);
    m_2.SetRefractiveIndex(1.5);
    Sphere s_2;
    s_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));
    s_2.SetMaterial(m_2);

    Ray ray(Point(0, 0, 0.1), Vector(0, 1, 0));

    std::vector<Intersection> hits = scene.Intersections(ray);
    for (int i = 0; i < hits.size(); i++) {
        std::cout << hits[i] << std::endl;
    }

    Computations c = Computations::Prepare(hits[2], ray, &hits);
    Color color = scene.RefractedColor(c, 5);
    EXPECT_EQ(Color(0, 0.99888, 0.04725), color);
}

TEST(ComputationsTests, HandingRefractionInShadeHit) {
    Scene scene;
    scene.DefaultScene();

    Plane plane;
    plane.SetMatrix(Mat4::TranslateMatrix(0, -1, 0));
    Material m_1;
    m_1.SetTransparency(0.5);
    m_1.SetRefractiveIndex(1.5);
    plane.SetMaterial(m_1);

    Material m_2;
    m_2.SetColor(Color::red);
    m_2.SetAmbient(0.5);
    Sphere ball;
    ball.SetMatrix(Mat4::TranslateMatrix(0, -3.5, -0.5));
    ball.SetMaterial(m_2);

    Ray ray(Point(0, 0, -3.0), Vector(0, -std::sqrt(2)/2.0, std::sqrt(2) / 2.0));

    std::vector<Intersection> hits = scene.Intersections(ray);
    for (int i = 0; i < hits.size(); i++) {
        std::cout << hits[i] << std::endl;
    }

    Computations c = Computations::Prepare(hits[0], ray, &hits);
    Color color = scene.ShadeHit(c, 5);
    EXPECT_EQ(Color(0.93642, 0.68642, 0.68642), color);
}

TEST(ComputationsTests, ReflectanceUnderTotalInternalReflection) {
    Scene scene;

    Material m;
    m.SetRefractiveIndex(1.5);
    m.SetTransparency(1.0);
    m.SetDiffuse(0);
    Sphere ball;
    ball.SetMaterial(m);

    Ray ray(Point(0, 0, std::sqrt(2) / 2.0), Vector(0, 1, 0));

    std::vector<Intersection> hits = scene.Intersections(ray);
    for (int i = 0; i < hits.size(); i++) {
        std::cout << hits[i] << std::endl;
    }

    Computations c = Computations::Prepare(hits[1], ray, &hits);
    double reflectance = scene.Schlick(c);
    EXPECT_FLOAT_EQ(1.0, reflectance);
}

TEST(ComputationsTests, ReflectanceOfPerpRay) {
    Scene scene;

    Material m;
    m.SetRefractiveIndex(1.5);
    m.SetTransparency(1.0);
    Sphere ball;
    ball.SetMaterial(m);

    Ray ray(Point(0, 0, 0), Vector(0, 1, 0));

    std::vector<Intersection> hits = scene.Intersections(ray);
    for (int i = 0; i < hits.size(); i++) {
        std::cout << hits[i] << std::endl;
    }

    Computations c = Computations::Prepare(hits[1], ray, &hits);
    double reflectance = scene.Schlick(c);
    EXPECT_FLOAT_EQ(0.04, reflectance);
}

TEST(ComputationsTests, ReflectanceN2GreaterN1) {
    Scene scene;

    Material m;
    m.SetRefractiveIndex(1.5);
    m.SetTransparency(1.0);
    Sphere ball;
    ball.SetMaterial(m);

    Ray ray(Point(0, 0.99, -2), Vector(0, 0, 1));

    std::vector<Intersection> hits = scene.Intersections(ray);
    for (int i = 0; i < hits.size(); i++) {
        std::cout << hits[i] << std::endl;
    }

    Computations c = Computations::Prepare(hits[0], ray, &hits);
    double reflectance = scene.Schlick(c);
    EXPECT_FLOAT_EQ(0.4888143, reflectance);
}

TEST(ComputationsTests, CombiningReflectionAndRefraction) {
    Scene scene;
    Light light(Point(-10, 10, -10), Color::white);
    Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Material m_1;
    m_1.SetReflectivity(0.5);
    m_1.SetTransparency(0.5);
    m_1.SetRefractiveIndex(1.5);
    Plane plane;
    plane.SetMaterial(m_1);
    plane.SetMatrix(Mat4::TranslateMatrix(0, -1, 0));

    Material m_2;
    m_2.SetColor(Color::red);
    m_2.SetAmbient(0.5);
    Sphere ball;
    ball.SetMaterial(m_2);
    ball.SetMatrix(Mat4::TranslateMatrix(0, -3.5, -0.5));

    Ray ray(Point(0, 0, -3), Vector(0, -std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));

    //std::vector<Intersection> hits = scene.Intersections(ray);
    std::vector<Intersection> hits;
    hits.push_back(Intersection(plane, std::sqrt(2)));
    for (int i = 0; i < hits.size(); i++) {
        std::cout << hits[i] << std::endl;
    }

    Computations c = Computations::Prepare(hits[0], ray, &hits);
    Color color = scene.ShadeHit(c, 5);
    EXPECT_EQ(Color(0.93391, 0.69643, 0.69243), color);
}
