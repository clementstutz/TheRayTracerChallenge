#include "pch.h"
#include "Material.h"

TEST(MaterialTests, constructor_default) {
	Material material_1;
	EXPECT_EQ(typeid(material_1).name(), typeid(Material).name());
	EXPECT_EQ(material_1.GetColor(), Color::white);
	EXPECT_FLOAT_EQ(material_1.GetAmbient(), 0.1f);
	EXPECT_FLOAT_EQ(material_1.GetDiffuse(), 0.9f);
	EXPECT_FLOAT_EQ(material_1.GetSpecular(), 0.9f);
	EXPECT_FLOAT_EQ(material_1.GetShininess(), 200.0f);
	EXPECT_FLOAT_EQ(material_1.GetReflectivity(), 0.0f);
	EXPECT_FLOAT_EQ(material_1.GetRefractiveIndex(), 1.0f);
	EXPECT_FLOAT_EQ(material_1.GetTransparency(), 0.0f);
	//EXPECT_EQ(material_1.GetPattern(), null);
	//std::cout << material_1 << std::endl;
}