#include <cmath>
#include "Utils.h"


float Utils::GetEpsilon() { return Utils::EPSILON; }

float Utils::GetPI() { return Utils::PI; }

bool Utils::FE(float const& a, float const& b) {
	return std::abs(a - b) <= Utils::EPSILON;
}

float Utils::degToRad(float degrees) {
	return degrees * (Utils::PI / 180.0f);
}
