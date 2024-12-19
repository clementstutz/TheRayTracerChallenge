#pragma once
#include <ostream>
#include <vector>
#include "RayObject.h"
#include "Ray.h"
#include "Intersection.h"
#include "Point.h"
#include "Vector.h"

class Plane : public RayObject
{
private:
	Vector m_normal;

	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Plane();
	Plane(Plane const& other);
	Plane(Plane&& other) noexcept;

	// Destructor
	~Plane() = default;

	// Member functions
	bool operator==(Plane const& other) const;
	Plane& operator=(Plane const& other);
	Plane& operator=(Plane&& other) noexcept;
	friend std::ostream& operator<<(std::ostream& flux, Plane const& sphere);
	std::vector<Intersection> Intersect(Ray const& ray) override;
	Vector GetNormal(Point const& worldPoint, Intersection const& i) const override;
	Vector CalculateLocalNormal(Point const& localPoint, Intersection const& i) const override;
};
