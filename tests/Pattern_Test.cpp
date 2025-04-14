#include "pch.h"
#include "Pattern_for_Test.h"
#include "SolidColorPattern.h"
#include "Sphere.h"

TEST(Pattern_for_TestTests, constructor_default) {
    Pattern_for_Test pattern;
    EXPECT_EQ(pattern.GetMatrix(), Mat4());
    EXPECT_TRUE(typeid(decltype(pattern.m_patternA)) == typeid(std::shared_ptr<Pattern>));
    EXPECT_TRUE(typeid(decltype(pattern.m_patternB)) == typeid(std::shared_ptr<Pattern>));
    EXPECT_TRUE(typeid(*pattern.m_patternA) == typeid(SolidColorPattern));
    EXPECT_TRUE(typeid(*pattern.m_patternB) == typeid(SolidColorPattern));
    EXPECT_EQ(pattern.m_patternA->patternAt(Point(0,0,0)), Color::white);
    EXPECT_EQ(pattern.m_patternB->patternAt(Point(0, 0, 0)), Color::black);
}

TEST(Pattern_for_TestTests, SetMatrix) {
    Pattern_for_Test pattern;
    pattern.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));
    EXPECT_EQ(pattern.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
}

TEST(Pattern_for_TestTests, constructor_values) {
    //patterns already existing
    Pattern_for_Test p1;
    Pattern_for_Test p2;

    Pattern_for_Test pattern_1(p1, p2);
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4());
    EXPECT_EQ(*pattern_1.m_patternA, p1);
    EXPECT_EQ(*pattern_1.m_patternB, p2);

    //patterns created on the fly
    Pattern_for_Test pattern_2( Pattern_for_Test{}, Pattern_for_Test{});
    EXPECT_EQ(pattern_2.GetMatrix(), Mat4());
    EXPECT_EQ(*pattern_2.m_patternA, Pattern_for_Test());
    EXPECT_EQ(*pattern_2.m_patternB, Pattern_for_Test());

    Pattern_for_Test pattern_3{ Pattern_for_Test(), Pattern_for_Test() };
    EXPECT_EQ(pattern_3.GetMatrix(), Mat4());
    EXPECT_EQ(*pattern_3.m_patternA, Pattern_for_Test());
    EXPECT_EQ(*pattern_3.m_patternB, Pattern_for_Test());

    Pattern_for_Test pattern_4((Pattern_for_Test{ Pattern_for_Test(), Pattern_for_Test() }), (Pattern_for_Test{ Pattern_for_Test(), Pattern_for_Test() }));
    EXPECT_EQ(pattern_4.GetMatrix(), Mat4());
    EXPECT_EQ(*pattern_4.m_patternA, Pattern_for_Test(Pattern_for_Test(), Pattern_for_Test()));
    EXPECT_EQ(*pattern_4.m_patternB, Pattern_for_Test(Pattern_for_Test(), Pattern_for_Test()));

    Pattern_for_Test pattern_5 = Pattern_for_Test(Pattern_for_Test(), Pattern_for_Test());
    EXPECT_EQ(pattern_5.GetMatrix(), Mat4());
    EXPECT_EQ(*pattern_5.m_patternA, Pattern_for_Test());
    EXPECT_EQ(*pattern_5.m_patternB, Pattern_for_Test());
}

TEST(Pattern_for_TestTests, constructor_copy) {
    Pattern_for_Test p1;
    Pattern_for_Test p2;
    Pattern_for_Test pattern_1(p1, p2);
    pattern_1.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    Pattern_for_Test pattern_2(pattern_1);
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(*pattern_1.m_patternA, p1);
    EXPECT_EQ(*pattern_1.m_patternB, p2);
    EXPECT_EQ(pattern_2.GetMatrix(), pattern_1.GetMatrix());
    EXPECT_EQ(*pattern_2.m_patternA, p1);
    EXPECT_EQ(*pattern_2.m_patternB, p2);
    
    Pattern_for_Test pattern_3 = pattern_1;
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(*pattern_1.m_patternA, p1);
    EXPECT_EQ(*pattern_1.m_patternB, p2);
    EXPECT_EQ(pattern_3.GetMatrix(), pattern_1.GetMatrix());
    EXPECT_EQ(*pattern_3.m_patternA, p1);
    EXPECT_EQ(*pattern_3.m_patternB, p2);
    
}

TEST(Pattern_for_TestTests, constructor_move) {
    Pattern_for_Test p1;
    Pattern_for_Test p2;
    Pattern_for_Test pattern_1(p1, p2);
    pattern_1.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    Pattern_for_Test pattern_2(std::move(pattern_1));
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4());
    EXPECT_EQ(*pattern_1.m_patternA, *Pattern_for_Test().m_patternA);
    EXPECT_EQ(*pattern_1.m_patternB, *Pattern_for_Test().m_patternB);
    EXPECT_EQ(pattern_2.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(*pattern_2.m_patternA, p1);
    EXPECT_EQ(*pattern_2.m_patternB, p2);

    Pattern_for_Test pattern_3(std::move(Pattern_for_Test()));
    EXPECT_EQ(pattern_3.GetMatrix(), Mat4());
    EXPECT_EQ(*pattern_3.m_patternA, *Pattern_for_Test().m_patternA);
    EXPECT_EQ(*pattern_3.m_patternB, *Pattern_for_Test().m_patternB);

    //Does it use the copy constructor instead of the moving one ?
    Pattern_for_Test pattern_4{ Pattern_for_Test() };
    EXPECT_EQ(pattern_4.GetMatrix(), Mat4());
    EXPECT_EQ(*pattern_4.m_patternA, *Pattern_for_Test().m_patternA);
    EXPECT_EQ(*pattern_4.m_patternB, *Pattern_for_Test().m_patternB);
}

TEST(Pattern_for_TestTests, affectation_copy) {
    Pattern_for_Test p1;
    Pattern_for_Test p2;
    Pattern_for_Test pattern_1(p1, p2);
    pattern_1.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    Pattern_for_Test pattern_2;
    pattern_2 = pattern_1;
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(*pattern_1.m_patternA, p1);
    EXPECT_EQ(*pattern_1.m_patternB, p2);
    EXPECT_EQ(pattern_2.GetMatrix(), pattern_1.GetMatrix());
    EXPECT_EQ(*pattern_2.m_patternA, p1);
    EXPECT_EQ(*pattern_2.m_patternB, p2);
}

TEST(Pattern_for_TestTests, affectation_move) {
    Pattern_for_Test p1;
    Pattern_for_Test p2;
    Pattern_for_Test pattern_1(p1, p2);
    pattern_1.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    Pattern_for_Test pattern_2;
    pattern_2 = std::move(pattern_1);
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4());
    EXPECT_EQ(*pattern_1.m_patternA, *Pattern_for_Test().m_patternA);
    EXPECT_EQ(*pattern_1.m_patternB, *Pattern_for_Test().m_patternB);
    EXPECT_EQ(pattern_2.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(*pattern_2.m_patternA, p1);
    EXPECT_EQ(*pattern_2.m_patternB, p2);

    Pattern_for_Test pattern_3(p1, p2);;
    pattern_3.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    Pattern_for_Test pattern_4 = std::move(pattern_3);
    EXPECT_EQ(pattern_3.GetMatrix(), Mat4());
    EXPECT_EQ(*pattern_3.m_patternA, *Pattern_for_Test().m_patternA);
    EXPECT_EQ(*pattern_3.m_patternB, *Pattern_for_Test().m_patternB);
    EXPECT_EQ(pattern_4.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(*pattern_4.m_patternA, p1);
    EXPECT_EQ(*pattern_4.m_patternB, p2);
}

TEST(Pattern_for_TestTests, equality) {
    Pattern_for_Test p1;
    Pattern_for_Test p2;
    Pattern_for_Test pattern_1(p1, p2);
    pattern_1.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    Pattern_for_Test pattern_2(p1, p2);
    pattern_2.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));
    EXPECT_EQ(pattern_1, pattern_2);
    EXPECT_TRUE(pattern_1.equals(pattern_2));
    EXPECT_TRUE(pattern_1 == pattern_2);
    EXPECT_FALSE(pattern_1 != pattern_2);
    
    Pattern_for_Test pattern_3(p1, p2);
    EXPECT_NE(pattern_1, pattern_3);
    EXPECT_FALSE(pattern_1.equals(pattern_3));
    EXPECT_FALSE(pattern_1 == pattern_3);
    EXPECT_TRUE(pattern_1 != pattern_3);
}

TEST(Pattern_for_TestTests, patternAt) {
    Pattern_for_Test pattern;
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 0)), Color::black);
    EXPECT_EQ(pattern.patternAt(Point(1, 1, 1)), Color::white);
    EXPECT_EQ(pattern.patternAt(Point(1, 2, 3)), Color(1, 2, 3));
}

TEST(Pattern_for_TestTests, clone) {
    Pattern_for_Test pattern;
    std::shared_ptr<Pattern> ptr;
    ptr = pattern.clone();
    EXPECT_EQ(*ptr, pattern);
}

TEST(Pattern_for_TestTests, integration) {
    Sphere s;
    Pattern_for_Test pattern;
    Material material;
    material.SetAmbient(1);
    material.SetDiffuse(0);
    material.SetSpecular(0);
    material.SetPattern(pattern);
    s.SetMaterial(material);
    Light light(Point(0, 0, -10), Color(1, 1, 1));
    Vector eye(0, 0, -1);
    Vector normal(0, 0, -1);
    Color c1 = s.Lighting(Point(0.9, 0, 0), light, eye, normal, false);
    Color c2 = s.Lighting(Point(1.1, 0, 0), light, eye, normal, false);

    EXPECT_EQ(c1, Color(0.9, 0, 0));
    EXPECT_EQ(c2, Color(1.1, 0, 0));
}

TEST(Pattern_for_TestTests, transformation) {
    Pattern_for_Test pattern;
    Material material;
    material.SetPattern(pattern);
    Sphere s;
    s.SetMaterial(material);

    //sphere * 2 but pattern * 1
    s.SetMatrix(Mat4::ScaleMatrix(2, 2, 2));
    EXPECT_EQ(s.GetMaterial().GetPattern()->PatternAtObject(s.WorldToObject(Point(2, 3, 4))), Color(1, 1.5, 2));
    
    //sphere * 1 but pattern * 2
    s.SetMatrix(Mat4());
    pattern.SetMatrix(Mat4::ScaleMatrix(2, 2, 2));
    material.SetPattern(pattern);
    s.SetMaterial(material);
    EXPECT_EQ(s.GetMaterial().GetPattern()->PatternAtObject(s.WorldToObject(Point(2, 3, 4))), Color(1, 1.5, 2));
    
    //sphere * 2 but pattern translated
    s.SetMatrix(Mat4::ScaleMatrix(2, 2, 2));
    pattern.SetMatrix(Mat4::TranslateMatrix(0.5, 1, 1.5));
    material.SetPattern(pattern);
    s.SetMaterial(material);
    EXPECT_EQ(s.GetMaterial().GetPattern()->PatternAtObject(s.WorldToObject(Point(2.5, 3, 3.5))), Color(0.75, 0.5, 0.25));
}
