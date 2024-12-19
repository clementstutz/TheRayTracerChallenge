#include <cmath>
#include "Utils.h"


double Utils::GetEpsilon() { return Utils::EPSILON; }

double Utils::GetPI() { return Utils::PI; }

bool Utils::FE(double const& a, double const& b) {
	return std::abs(a - b) <= Utils::EPSILON;
}

double Utils::degToRad(double degrees) {
	return degrees * (Utils::PI / 180.0);
}
