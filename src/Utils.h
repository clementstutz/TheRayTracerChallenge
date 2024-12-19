#pragma once

class Utils
{
private :
	static constexpr double EPSILON = 0.001; //1.e10-7;
	static constexpr double PI = 3.14159265358979323846;

public:
	static double GetEpsilon();
	static double GetPI();
	static bool FE(double const &a, double const& b);
	static double degToRad(double degrees);
};