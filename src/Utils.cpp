#include "Utils.h"
#include <cmath>

const float Utils::EPSILON = 0.00001f;

bool Utils::FE(float const& a, float const& b)
{
	float temp = a - b;
	if (abs(temp) < EPSILON)
	{
		return true;
	}
	else
	{
		return false;
	}
}
