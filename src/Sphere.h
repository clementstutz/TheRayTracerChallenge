#pragma once
#include <ostream>
#include <vector>
#include "RayObject.h"
#include "Ray.h"
#include "Intersection.h"
#include "Point.h"
#include "Vector.h"

class Sphere : public RayObject
{
private:
	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Sphere();
	Sphere(Sphere const& other);
	Sphere(Sphere&& other) noexcept;

	// Destructor
	~Sphere();

	// Operators
	Sphere& operator=(Sphere const& other);
	Sphere& operator=(Sphere&& other) noexcept;
	friend std::ostream& operator<<(std::ostream& flux, Sphere const& sphere);

	// Member-functions
	std::vector<Intersection> Intersect(Ray ray) override;
	Vector GetNormal(Point const& worldPoint, Intersection const &i) const override;
	Vector CalculateLocalNormal(Point const& localPoint, Intersection const& i) const override;
};

