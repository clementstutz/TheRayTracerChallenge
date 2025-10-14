#pragma once
#include "Shape.h"
#include "Intersection.h"

class Shape_for_Test : public Shape
{
public:
	// Constructors
	Shape_for_Test();
	Shape_for_Test(Shape_for_Test const& other);
	Shape_for_Test(Shape_for_Test&& other) noexcept;


	// Destructor
	~Shape_for_Test() = default;

	// Member functions
	Shape_for_Test& operator=(Shape_for_Test const& other);
	Shape_for_Test& operator=(Shape_for_Test&& other) noexcept;
	std::vector<Intersection> Intersect(Ray const& ray) override;
	Vector GetNormal(Point const& worldPoint, Intersection const& i) const override;
	Vector CalculateLocalNormal(Point const& localPoint, Intersection const& i) const override;
};
