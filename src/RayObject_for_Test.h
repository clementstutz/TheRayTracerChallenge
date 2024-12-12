#pragma once
#include "RayObject.h"
#include "Intersection.h"

class RayObject_for_Test : public RayObject
{
public:
	// Constructors
	RayObject_for_Test();
	RayObject_for_Test(RayObject_for_Test const& other);
	RayObject_for_Test(RayObject_for_Test&& other) noexcept;


	// Destructor
	~RayObject_for_Test() = default;

	// Member functions
	RayObject_for_Test& operator=(RayObject_for_Test const& other);
	RayObject_for_Test& operator=(RayObject_for_Test&& other) noexcept;
	std::vector<Intersection> Intersect(Ray const& ray) override;
	Vector GetNormal(Point const& worldPoint, Intersection const& i) const override;
	Vector CalculateLocalNormal(Point const& localPoint, Intersection const& i) const override;
};

