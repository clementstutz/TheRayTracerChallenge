#include <cmath>
#include "Utils.h"


float Utils::GetEpsilon() { return Utils::EPSILON; }

bool Utils::FE(float const& a, float const& b) {
	float temp = std::abs(a - b);
	bool c = temp <= Utils::EPSILON;
	return c;
}

float Utils::degToRad(float degrees) {
	return degrees * (Utils::PI / 180.0f);
}
