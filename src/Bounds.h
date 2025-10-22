#pragma once
#include <vector>
#include "Point.h"
#include "Ray.h"

namespace Axis {
	constexpr uint8_t X = 1;
	constexpr uint8_t Y = 2;
	constexpr uint8_t Z = 3;
}

class Bounds
{
protected:
	Point m_min;
	Point m_max;

public:
	Bounds();

	Bounds GetAABB(const Mat4& transformMatrix);
	Bounds GetAABB(std::vector<std::shared_ptr<Point>> points);
	std::vector<std::shared_ptr<Point>> GetTransformedCorners(const Mat4& mat);
	std::vector<std::shared_ptr<Point>> GetCorners();
	bool Intersect(const Ray& ray);
	std::array<double, 2> CheckAxis(uint8_t axis, double origin, double direction);
};
