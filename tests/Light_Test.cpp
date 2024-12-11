#include "pch.h"
#include "Light.h"

TEST(LightTests, constructor_default) {
	int nbInstanceAlreadyExisting = Light::GetNbInstances();

	Light light_1;
	EXPECT_EQ(typeid(light_1).name(), typeid(Light).name());
	EXPECT_EQ(Light::GetNbInstances() - nbInstanceAlreadyExisting, 1);
	EXPECT_EQ(light_1.GetId() - nbInstanceAlreadyExisting, 1);
	EXPECT_EQ(light_1.GetIntensity(), Color(1, 1, 1));
	EXPECT_EQ(light_1.GetPosition(), Point(0, 0, 0));
}