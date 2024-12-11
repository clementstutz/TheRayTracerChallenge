#pragma once

class Utils
{
private :
	/*static constexpr float EPSILON = 1.e10-7;*/

public:
	static constexpr float EPSILON = 0.00001;

	static constexpr float PI = 3.14159265358979323846;

	static float GetEpsilon();

	static bool FE(float const &a, float const& b);

	static float degToRad(float degrees);
};