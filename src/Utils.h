#pragma once

class Utils
{
private :
	static constexpr float EPSILON = 0.00001f; //1.e10-7;
	static constexpr float PI = 3.14159265358979323846f;

public:
	static float GetEpsilon();
	static float GetPI();
	static bool FE(float const &a, float const& b);
	static float degToRad(float degrees);
};