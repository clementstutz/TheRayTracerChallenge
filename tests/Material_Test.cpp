#include "pch.h"
#include "Material.h"
#include "Pattern_for_Test.h"

TEST(MaterialTests, constructor_default) {
	Material material_1;
	EXPECT_EQ(typeid(material_1).name(), typeid(Material).name());
	EXPECT_EQ(material_1.GetColor(), Color::white);
	EXPECT_FLOAT_EQ(material_1.GetAmbient(), 0.1);
	EXPECT_FLOAT_EQ(material_1.GetDiffuse(), 0.9);
	EXPECT_FLOAT_EQ(material_1.GetSpecular(), 0.9);
	EXPECT_FLOAT_EQ(material_1.GetShininess(), 200.0);
	EXPECT_FLOAT_EQ(material_1.GetReflectivity(), 0.0);
	EXPECT_FLOAT_EQ(material_1.GetRefractiveIndex(), 1.0);
	EXPECT_FLOAT_EQ(material_1.GetTransparency(), 0.0);
	EXPECT_EQ(material_1.GetPattern(), nullptr);
}

TEST(MaterialTests, constructor_values) {
	Pattern_for_Test pattern;
	std::shared_ptr<Pattern_for_Test> ptr(std::make_shared<Pattern_for_Test>(pattern));
	Material material_1(Color::red, 0.2, 0.8, 0.7, 150, 0.1, 0.6, 0.3, ptr);
	EXPECT_EQ(typeid(material_1).name(), typeid(Material).name());
	EXPECT_EQ(material_1.GetColor(), Color::red);
	EXPECT_FLOAT_EQ(material_1.GetAmbient(), 0.2);
	EXPECT_FLOAT_EQ(material_1.GetDiffuse(), 0.8);
	EXPECT_FLOAT_EQ(material_1.GetSpecular(), 0.7);
	EXPECT_FLOAT_EQ(material_1.GetShininess(), 150.0);
	EXPECT_FLOAT_EQ(material_1.GetReflectivity(), 0.1);
	EXPECT_FLOAT_EQ(material_1.GetRefractiveIndex(), 0.6);
	EXPECT_FLOAT_EQ(material_1.GetTransparency(), 0.3);
	EXPECT_EQ(material_1.GetPattern(), ptr);
}

TEST(MaterialTests, constructor_copy) {
    Pattern_for_Test pattern;
    std::shared_ptr<Pattern_for_Test> ptr(std::make_shared<Pattern_for_Test>(pattern));
    Material material_1(Color::red, 0.2, 0.8, 0.7, 150, 0.1, 0.6, 0.3, ptr);

    Material material_2(material_1);
    EXPECT_EQ(material_1.GetColor(), Color::red);
    EXPECT_FLOAT_EQ(material_1.GetAmbient(), 0.2);
    EXPECT_FLOAT_EQ(material_1.GetDiffuse(), 0.8);
    EXPECT_FLOAT_EQ(material_1.GetSpecular(), 0.7);
    EXPECT_FLOAT_EQ(material_1.GetShininess(), 150.0);
    EXPECT_FLOAT_EQ(material_1.GetReflectivity(), 0.1);
    EXPECT_FLOAT_EQ(material_1.GetRefractiveIndex(), 0.6);
    EXPECT_FLOAT_EQ(material_1.GetTransparency(), 0.3);
    EXPECT_EQ(material_1.GetPattern(), ptr);

    EXPECT_EQ(material_2.GetColor(), Color::red);
    EXPECT_FLOAT_EQ(material_2.GetAmbient(), 0.2);
    EXPECT_FLOAT_EQ(material_2.GetDiffuse(), 0.8);
    EXPECT_FLOAT_EQ(material_2.GetSpecular(), 0.7);
    EXPECT_FLOAT_EQ(material_2.GetShininess(), 150.0);
    EXPECT_FLOAT_EQ(material_2.GetReflectivity(), 0.1);
    EXPECT_FLOAT_EQ(material_2.GetRefractiveIndex(), 0.6);
    EXPECT_FLOAT_EQ(material_2.GetTransparency(), 0.3);
    EXPECT_EQ(material_2.GetPattern(), ptr);

    Material material_3 = material_1;
    EXPECT_EQ(material_1.GetColor(), Color::red);
    EXPECT_FLOAT_EQ(material_1.GetAmbient(), 0.2);
    EXPECT_FLOAT_EQ(material_1.GetDiffuse(), 0.8);
    EXPECT_FLOAT_EQ(material_1.GetSpecular(), 0.7);
    EXPECT_FLOAT_EQ(material_1.GetShininess(), 150.0);
    EXPECT_FLOAT_EQ(material_1.GetReflectivity(), 0.1);
    EXPECT_FLOAT_EQ(material_1.GetRefractiveIndex(), 0.6);
    EXPECT_FLOAT_EQ(material_1.GetTransparency(), 0.3);
    EXPECT_EQ(material_1.GetPattern(), ptr);
    
    EXPECT_EQ(material_3.GetColor(), Color::red);
    EXPECT_FLOAT_EQ(material_3.GetAmbient(), 0.2);
    EXPECT_FLOAT_EQ(material_3.GetDiffuse(), 0.8);
    EXPECT_FLOAT_EQ(material_3.GetSpecular(), 0.7);
    EXPECT_FLOAT_EQ(material_3.GetShininess(), 150.0);
    EXPECT_FLOAT_EQ(material_3.GetReflectivity(), 0.1);
    EXPECT_FLOAT_EQ(material_3.GetRefractiveIndex(), 0.6);
    EXPECT_FLOAT_EQ(material_3.GetTransparency(), 0.3);
    EXPECT_EQ(material_3.GetPattern(), ptr);
}

TEST(MaterialTests, constructor_move) {
    Pattern_for_Test pattern;
    std::shared_ptr<Pattern_for_Test> ptr(std::make_shared<Pattern_for_Test>(pattern));
    Material material_1(Color::red, 0.2, 0.8, 0.7, 150, 0.1, 0.6, 0.3, ptr);

    Material material_2(std::move(material_1));
    EXPECT_EQ(material_1.GetColor(), Color::black);
    EXPECT_FLOAT_EQ(material_1.GetAmbient(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetDiffuse(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetSpecular(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetShininess(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetReflectivity(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetRefractiveIndex(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetTransparency(), 0.0);
    EXPECT_EQ(material_1.GetPattern(), nullptr);

    EXPECT_EQ(material_2.GetColor(), Color::red);
    EXPECT_FLOAT_EQ(material_2.GetAmbient(), 0.2);
    EXPECT_FLOAT_EQ(material_2.GetDiffuse(), 0.8);
    EXPECT_FLOAT_EQ(material_2.GetSpecular(), 0.7);
    EXPECT_FLOAT_EQ(material_2.GetShininess(), 150.0);
    EXPECT_FLOAT_EQ(material_2.GetReflectivity(), 0.1);
    EXPECT_FLOAT_EQ(material_2.GetRefractiveIndex(), 0.6);
    EXPECT_FLOAT_EQ(material_2.GetTransparency(), 0.3);
    EXPECT_EQ(material_2.GetPattern(), ptr);

    Material material_3(std::move(Material()));
    EXPECT_EQ(material_3.GetColor(), Color::white);
    EXPECT_FLOAT_EQ(material_3.GetAmbient(), 0.1);
    EXPECT_FLOAT_EQ(material_3.GetDiffuse(), 0.9);
    EXPECT_FLOAT_EQ(material_3.GetSpecular(), 0.9);
    EXPECT_FLOAT_EQ(material_3.GetShininess(), 200.0);
    EXPECT_FLOAT_EQ(material_3.GetReflectivity(), 0.0);
    EXPECT_FLOAT_EQ(material_3.GetRefractiveIndex(), 1.0);
    EXPECT_FLOAT_EQ(material_3.GetTransparency(), 0.0);
    EXPECT_EQ(material_3.GetPattern(), nullptr);

    //Does it use the copy constructor instead of the moving one ?
    Material material_4{ Material() };
    EXPECT_EQ(material_4.GetColor(), Color::white);
    EXPECT_FLOAT_EQ(material_4.GetAmbient(), 0.1);
    EXPECT_FLOAT_EQ(material_4.GetDiffuse(), 0.9);
    EXPECT_FLOAT_EQ(material_4.GetSpecular(), 0.9);
    EXPECT_FLOAT_EQ(material_4.GetShininess(), 200.0);
    EXPECT_FLOAT_EQ(material_4.GetReflectivity(), 0.0);
    EXPECT_FLOAT_EQ(material_4.GetRefractiveIndex(), 1.0);
    EXPECT_FLOAT_EQ(material_4.GetTransparency(), 0.0);
    EXPECT_EQ(material_4.GetPattern(), nullptr);
}

TEST(MaterialTests, affectation_copy) {
    Pattern_for_Test pattern;
    std::shared_ptr<Pattern_for_Test> ptr(std::make_shared<Pattern_for_Test>(pattern));
    Material material_1(Color::red, 0.2, 0.8, 0.7, 150, 0.1, 0.6, 0.3, ptr);

    Material material_2;
    material_2 = material_1;
    EXPECT_EQ(material_1.GetColor(), Color::red);
    EXPECT_FLOAT_EQ(material_1.GetAmbient(), 0.2);
    EXPECT_FLOAT_EQ(material_1.GetDiffuse(), 0.8);
    EXPECT_FLOAT_EQ(material_1.GetSpecular(), 0.7);
    EXPECT_FLOAT_EQ(material_1.GetShininess(), 150.0);
    EXPECT_FLOAT_EQ(material_1.GetReflectivity(), 0.1);
    EXPECT_FLOAT_EQ(material_1.GetRefractiveIndex(), 0.6);
    EXPECT_FLOAT_EQ(material_1.GetTransparency(), 0.3);
    EXPECT_EQ(material_1.GetPattern(), ptr);

    EXPECT_EQ(material_2.GetColor(), Color::red);
    EXPECT_FLOAT_EQ(material_2.GetAmbient(), 0.2);
    EXPECT_FLOAT_EQ(material_2.GetDiffuse(), 0.8);
    EXPECT_FLOAT_EQ(material_2.GetSpecular(), 0.7);
    EXPECT_FLOAT_EQ(material_2.GetShininess(), 150.0);
    EXPECT_FLOAT_EQ(material_2.GetReflectivity(), 0.1);
    EXPECT_FLOAT_EQ(material_2.GetRefractiveIndex(), 0.6);
    EXPECT_FLOAT_EQ(material_2.GetTransparency(), 0.3);
    EXPECT_EQ(material_2.GetPattern(), ptr);
}

TEST(MaterialTests, affectation_move) {
    Pattern_for_Test pattern;
    std::shared_ptr<Pattern_for_Test> ptr(std::make_shared<Pattern_for_Test>(pattern));
    Material material_1(Color::red, 0.2, 0.8, 0.7, 150, 0.1, 0.6, 0.3, ptr);

    Material material_2;
    material_2 = std::move(material_1);
    EXPECT_EQ(material_1.GetColor(), Color::black);
    EXPECT_FLOAT_EQ(material_1.GetAmbient(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetDiffuse(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetSpecular(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetShininess(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetReflectivity(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetRefractiveIndex(), 0.0);
    EXPECT_FLOAT_EQ(material_1.GetTransparency(), 0.0);
    EXPECT_EQ(material_1.GetPattern(), nullptr);

    EXPECT_EQ(material_2.GetColor(), Color::red);
    EXPECT_FLOAT_EQ(material_2.GetAmbient(), 0.2);
    EXPECT_FLOAT_EQ(material_2.GetDiffuse(), 0.8);
    EXPECT_FLOAT_EQ(material_2.GetSpecular(), 0.7);
    EXPECT_FLOAT_EQ(material_2.GetShininess(), 150.0);
    EXPECT_FLOAT_EQ(material_2.GetReflectivity(), 0.1);
    EXPECT_FLOAT_EQ(material_2.GetRefractiveIndex(), 0.6);
    EXPECT_FLOAT_EQ(material_2.GetTransparency(), 0.3);
    EXPECT_EQ(material_2.GetPattern(), ptr);

    Material material_3(Color::red, 0.2, 0.8, 0.7, 150, 0.1, 0.6, 0.3, ptr);

    Material material_4 = std::move(material_3);
    EXPECT_EQ(material_3.GetColor(), Color::black);
    EXPECT_FLOAT_EQ(material_3.GetAmbient(), 0.0);
    EXPECT_FLOAT_EQ(material_3.GetDiffuse(), 0.0);
    EXPECT_FLOAT_EQ(material_3.GetSpecular(), 0.0);
    EXPECT_FLOAT_EQ(material_3.GetShininess(), 0.0);
    EXPECT_FLOAT_EQ(material_3.GetReflectivity(), 0.0);
    EXPECT_FLOAT_EQ(material_3.GetRefractiveIndex(), 0.0);
    EXPECT_FLOAT_EQ(material_3.GetTransparency(), 0.0);
    EXPECT_EQ(material_3.GetPattern(), nullptr);

    EXPECT_EQ(material_4.GetColor(), Color::red);
    EXPECT_FLOAT_EQ(material_4.GetAmbient(), 0.2);
    EXPECT_FLOAT_EQ(material_4.GetDiffuse(), 0.8);
    EXPECT_FLOAT_EQ(material_4.GetSpecular(), 0.7);
    EXPECT_FLOAT_EQ(material_4.GetShininess(), 150.0);
    EXPECT_FLOAT_EQ(material_4.GetReflectivity(), 0.1);
    EXPECT_FLOAT_EQ(material_4.GetRefractiveIndex(), 0.6);
    EXPECT_FLOAT_EQ(material_4.GetTransparency(), 0.3);
    EXPECT_EQ(material_4.GetPattern(), ptr);
}

TEST(MaterialTests, equality) {
    Pattern_for_Test pattern;
    std::shared_ptr<Pattern_for_Test> ptr(std::make_shared<Pattern_for_Test>(pattern));
    Material material_1(Color::red, 0.2, 0.8, 0.7, 150, 0.1, 0.6, 0.3, ptr);

    Material material_2(Color::red, 0.2, 0.8, 0.7, 150, 0.1, 0.6, 0.3, ptr);

    EXPECT_EQ(material_1.GetColor(), material_2.GetColor());
    EXPECT_FLOAT_EQ(material_1.GetAmbient(), material_2.GetAmbient());
    EXPECT_FLOAT_EQ(material_1.GetDiffuse(), material_2.GetDiffuse());
    EXPECT_FLOAT_EQ(material_1.GetSpecular(), material_2.GetSpecular());
    EXPECT_FLOAT_EQ(material_1.GetShininess(), material_2.GetShininess());
    EXPECT_FLOAT_EQ(material_1.GetReflectivity(), material_2.GetReflectivity());
    EXPECT_FLOAT_EQ(material_1.GetRefractiveIndex(), material_2.GetRefractiveIndex());
    EXPECT_FLOAT_EQ(material_1.GetTransparency(), material_2.GetTransparency());
    EXPECT_EQ(material_1.GetPattern(), material_2.GetPattern());

    EXPECT_EQ(material_1, material_2);
    EXPECT_TRUE(material_1 == material_2);
    EXPECT_FALSE(material_1 != material_2);

    Material material_3;
    EXPECT_NE(material_1, material_3);
    EXPECT_FALSE(material_1 == material_3);
    EXPECT_TRUE(material_1 != material_3);
}

TEST(MaterialTests, SetColor) {
    Material material;
    material.SetColor(Color::red);
    EXPECT_EQ(material.GetColor(), Color::red);
}

TEST(MaterialTests, SetAmbient) {
    Material material;
    material.SetAmbient(0.2);
    EXPECT_FLOAT_EQ(material.GetAmbient(), 0.2);
}

TEST(MaterialTests, SetDiffuse) {
    Material material;
    material.SetDiffuse(0.8);
    EXPECT_FLOAT_EQ(material.GetDiffuse(), 0.8);
}

TEST(MaterialTests, SetSpecular) {
    Material material;
    material.SetSpecular(0.7);
    EXPECT_FLOAT_EQ(material.GetSpecular(), 0.7);
}

TEST(MaterialTests, SetShininess) {
    Material material;
    material.SetShininess(150);
    EXPECT_FLOAT_EQ(material.GetShininess(), 150);
}

TEST(MaterialTests, SetReflectivity) {
    Material material;
    material.SetReflectivity(0.1);
    EXPECT_FLOAT_EQ(material.GetReflectivity(), 0.1);
}

TEST(MaterialTests, SetRefractiveIndex) {
    Material material;
    material.SetRefractiveIndex(0.6);
    EXPECT_FLOAT_EQ(material.GetRefractiveIndex(), 0.6);
}

TEST(MaterialTests, SetTransparency) {
    Material material;
    material.SetTransparency(0.3);
    EXPECT_FLOAT_EQ(material.GetTransparency(), 0.3);
}

TEST(MaterialTests, SetPattern) {
    Pattern_for_Test pattern;
    std::shared_ptr<Pattern_for_Test> ptr(std::make_shared<Pattern_for_Test>(pattern));
    Material material;
    material.SetPattern(pattern);
    EXPECT_EQ(*material.GetPattern(), *ptr);
}