#pragma once

#include "Shape.h"
#include "Intersection.h"

class Group : public Shape
{
public :
	bool performAABBIntersectionTest = true;

	// Constructors
	Group();

	// Destructors
	~Group() = default;

	// Member functions
	std::vector<Intersection> Intersect(Ray const& ray) override;
	virtual Vector CalculateLocalNormal(Point const& localPoint, Intersection const& i) const override = 0;
};
