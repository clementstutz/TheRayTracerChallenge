#include "pch.h"
#include "BlendPattern.h"
#include "SolidColorPattern.h"
#include "StripePattern.h""
#include "Sphere.h"
#include "Utils.h"

TEST(BlendPatternTests, constructor_default) {
    BlendPattern pattern;
    EXPECT_EQ(pattern.GetMatrix(), Mat4());
    EXPECT_EQ(pattern.GetMixingValue(), 0.5);
}

TEST(BlendPatternTests, SetMatrix) {
    BlendPattern pattern;
    pattern.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));
    EXPECT_EQ(pattern.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
}

TEST(BlendPatternTests, constructor_values) {
    //patterns already existing
    BlendPattern p1;
    BlendPattern p2;

    BlendPattern pattern_1(p1, p2, 0.3);
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4());
    EXPECT_EQ(pattern_1.GetMixingValue(), 0.3);

    //patterns created on the fly
    BlendPattern pattern_2(BlendPattern{}, BlendPattern{});
    EXPECT_EQ(pattern_2.GetMatrix(), Mat4());
    EXPECT_EQ(pattern_2.GetMixingValue(), 0.5);

    BlendPattern pattern_3{ BlendPattern(), BlendPattern() , -0.5};
    EXPECT_EQ(pattern_3.GetMatrix(), Mat4());
    EXPECT_EQ(pattern_3.GetMixingValue(), -0.5);

    BlendPattern pattern_4((BlendPattern{ BlendPattern(), BlendPattern() }), (BlendPattern{ BlendPattern(), BlendPattern() }));
    EXPECT_EQ(pattern_4.GetMatrix(), Mat4());
    EXPECT_EQ(pattern_4.GetMixingValue(), 0.5);

    BlendPattern pattern_5 = BlendPattern(BlendPattern(), BlendPattern(), 0.6);
    EXPECT_EQ(pattern_5.GetMatrix(), Mat4());
    EXPECT_EQ(pattern_5.GetMixingValue(), 0.6);
}

TEST(BlendPatternTests, constructor_copy) {
    BlendPattern p1;
    BlendPattern p2;
    BlendPattern pattern_1(p1, p2, 0.3);
    pattern_1.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    BlendPattern pattern_2(pattern_1);
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(pattern_1.GetMixingValue(), 0.3);
    EXPECT_EQ(pattern_2.GetMatrix(), pattern_1.GetMatrix());
    EXPECT_EQ(pattern_2.GetMixingValue(), pattern_1.GetMixingValue());

    BlendPattern pattern_3 = pattern_1;
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(pattern_1.GetMixingValue(), 0.3);
    EXPECT_EQ(pattern_3.GetMatrix(), pattern_1.GetMatrix());
    EXPECT_EQ(pattern_3.GetMixingValue(), pattern_1.GetMixingValue());

}

TEST(BlendPatternTests, constructor_move) {
    BlendPattern p1;
    BlendPattern p2;
    BlendPattern pattern_1(p1, p2, 0.3);
    pattern_1.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    BlendPattern pattern_2(std::move(pattern_1));
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4());
    EXPECT_EQ(pattern_1.GetMixingValue(), 0.0);
    EXPECT_EQ(pattern_2.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(pattern_2.GetMixingValue(), 0.3);

    BlendPattern pattern_3(std::move(BlendPattern()));
    EXPECT_EQ(pattern_3.GetMatrix(), Mat4());
    EXPECT_EQ(pattern_3.GetMixingValue(), 0.5);

    //Does it use the copy constructor instead of the moving one ?
    BlendPattern pattern_4{ BlendPattern() };
    EXPECT_EQ(pattern_4.GetMatrix(), Mat4());
    EXPECT_EQ(pattern_4.GetMixingValue(), 0.5);
}

TEST(BlendPatternTests, affectation_copy) {
    BlendPattern p1;
    BlendPattern p2;
    BlendPattern pattern_1(p1, p2);
    pattern_1.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    BlendPattern pattern_2;
    pattern_2 = pattern_1;
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(pattern_1.GetMixingValue(), 0.5);
    EXPECT_EQ(pattern_2.GetMatrix(), pattern_1.GetMatrix());
    EXPECT_EQ(pattern_2.GetMixingValue(), pattern_1.GetMixingValue());
}

TEST(BlendPatternTests, affectation_move) {
    BlendPattern p1;
    BlendPattern p2;
    BlendPattern pattern_1(p1, p2, 0.3);
    pattern_1.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    BlendPattern pattern_2;
    pattern_2 = std::move(pattern_1);
    EXPECT_EQ(pattern_1.GetMatrix(), Mat4());
    EXPECT_EQ(pattern_1.GetMixingValue(), 0.0);
    EXPECT_EQ(pattern_2.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(pattern_2.GetMixingValue(), 0.3);

    BlendPattern pattern_3(p1, p2, 0.3);;
    pattern_3.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    BlendPattern pattern_4 = std::move(pattern_3);
    EXPECT_EQ(pattern_3.GetMatrix(), Mat4());
    EXPECT_EQ(pattern_3.GetMixingValue(), 0.0);
    EXPECT_EQ(pattern_4.GetMatrix(), Mat4(2, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 2, 0,
        0, 0, 0, 1));
    EXPECT_EQ(pattern_4.GetMixingValue(), 0.3);
}

TEST(BlendPatternTests, equality) {
    BlendPattern p1;
    BlendPattern p2;
    BlendPattern pattern_1(p1, p2);
    pattern_1.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));

    BlendPattern pattern_2(p1, p2);
    pattern_2.SetMatrix(Mat4::ScaleMatrix(Vector(2, 2, 2)));
    EXPECT_EQ(pattern_1, pattern_2);
    EXPECT_TRUE(pattern_1.equals(pattern_2));
    EXPECT_TRUE(pattern_1 == pattern_2);
    EXPECT_FALSE(pattern_1 != pattern_2);

    BlendPattern pattern_3(p1, p2);
    EXPECT_NE(pattern_1, pattern_3);
    EXPECT_FALSE(pattern_1.equals(pattern_3));
    EXPECT_FALSE(pattern_1 == pattern_3);
    EXPECT_TRUE(pattern_1 != pattern_3);
}

TEST(BlendPatternTests, patternAt) {
    BlendPattern pattern;
    EXPECT_EQ(pattern.patternAt(Point(-1.1, 0, 0)), Color::grey);
    EXPECT_EQ(pattern.patternAt(Point(-0.1, 0, 0)), Color::grey);
    EXPECT_EQ(pattern.patternAt(Point(0, 0, 0)), Color::grey);
    EXPECT_EQ(pattern.patternAt(Point(0, 1, 0)), Color::grey);
    EXPECT_EQ(pattern.patternAt(Point(0, 2, 3)), Color::grey);
    EXPECT_EQ(pattern.patternAt(Point(0.9, 0, 0)), Color::grey);
    EXPECT_EQ(pattern.patternAt(Point(1, 0, 0)), Color::grey);
    EXPECT_EQ(pattern.patternAt(Point(2, 0, -3)), Color::grey);

    BlendPattern pattern_2(SolidColorPattern(Color(1, 0, 0)), SolidColorPattern(Color(0, 1, 0)));
    EXPECT_EQ(pattern_2.patternAt(Point(0, 0, 0)), Color(0.5, 0.5, 0));
    EXPECT_EQ(pattern_2.patternAt(Point(1, 0, 0)), Color(0.5, 0.5, 0));

    BlendPattern pattern_3(SolidColorPattern(Color(1, 0, 0)), SolidColorPattern(Color(0, 1, 0)));
    EXPECT_EQ(pattern_3.patternAt(Point(0, 0, 0)), Color(0.5, 0.5, 0));
    EXPECT_EQ(pattern_3.patternAt(Point(1, 0, 0)), Color(0.5, 0.5, 0));
}

TEST(BlendPatternTests, clone) {
    BlendPattern pattern;
    std::shared_ptr<Pattern> ptr;
    ptr = pattern.clone();
    EXPECT_EQ(*ptr, pattern);
}

TEST(BlendPatternTests, integration) {
    Sphere s;
    StripePattern s1{ SolidColorPattern(Color::white), SolidColorPattern(Color::green) };
    StripePattern s2{ SolidColorPattern(Color::red), SolidColorPattern(Color::blue) };
    s2.SetMatrix(Mat4::RotateZMatrix(Utils::GetPI() / 2));
    BlendPattern pattern(s1, s2);

    Material material;
    material.SetAmbient(1);
    material.SetDiffuse(0);
    material.SetSpecular(0);
    material.SetPattern(pattern);
    s.SetMaterial(material);
    Light light(Point(0, 0, -10), Color(1, 1, 1));
    Vector eye(0, 0, -1);
    Vector normal(0, 0, -1);
    Color c1 = s.Lighting(Point(0.5, 0.5, 0), light, eye, normal, false);
    Color c2 = s.Lighting(Point(1.5, 0.5, 0), light, eye, normal, false);
    Color c3 = s.Lighting(Point(1.5, 1.5, 0), light, eye, normal, false);
    Color c4 = s.Lighting(Point(0.5, 1.5, 0), light, eye, normal, false);

    EXPECT_EQ(c1, Color(1, 0.5, 0.5));
    EXPECT_EQ(c2, Color(0.5, 0.5, 0));
    EXPECT_EQ(c3, Color(0, 0.5, 0.5));
    EXPECT_EQ(c4, Color(0.5, 0.5, 1));

    Color c5 = s.Lighting(Point(-0.5, -0.5, 0), light, eye, normal, false);
    Color c6 = s.Lighting(Point(-1.5, -0.5, 0), light, eye, normal, false);
    Color c7 = s.Lighting(Point(-1.5, -1.5, 0), light, eye, normal, false);
    Color c8 = s.Lighting(Point(-0.5, -1.5, 0), light, eye, normal, false);

    EXPECT_EQ(c5, Color(0, 0.5, 0.5));
    EXPECT_EQ(c6, Color(0.5, 0.5, 1));
    EXPECT_EQ(c7, Color(1, 0.5, 0.5));
    EXPECT_EQ(c8, Color(0.5, 0.5, 0));
    
}

TEST(BlendPatternTests, transformation) {
    BlendPattern pattern;
    Material material;
    material.SetPattern(pattern);
    Sphere s;
    s.SetMaterial(material);

    //sphere * 2 but pattern * 1
    s.SetMatrix(Mat4::ScaleMatrix(2, 2, 2));
    EXPECT_EQ(s.GetMaterial().GetPattern()->PatternAtObject(s.WorldToObject(Point(2, 3, 4))), Color(0.5, 0.5, 0.5));

    //sphere * 1 but pattern * 2
    s.SetMatrix(Mat4());
    pattern.SetMatrix(Mat4::ScaleMatrix(2, 2, 2));
    material.SetPattern(pattern);
    s.SetMaterial(material);
    EXPECT_EQ(s.GetMaterial().GetPattern()->PatternAtObject(s.WorldToObject(Point(2, 3, 4))), Color(0.5, 0.5, 0.5));

    //sphere * 2 but pattern translated
    s.SetMatrix(Mat4::ScaleMatrix(2, 2, 2));
    pattern.SetMatrix(Mat4::TranslateMatrix(0.5, 1, 1.5));
    material.SetPattern(pattern);
    s.SetMaterial(material);
    EXPECT_EQ(s.GetMaterial().GetPattern()->PatternAtObject(s.WorldToObject(Point(2.5, 3, 3.5))), Color(0.5, 0.5, 0.5));
}
