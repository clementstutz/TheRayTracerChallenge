#pragma once

#include "Shape.h"
#include "Intersection.h"

class Cylinder : public Shape
{
protected:
	double m_minimum;
	double m_maximum;
	bool m_isClosed;	// WARNING : dissocier isClose en isTopClose et isBottomClose
	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Cylinder();
	Cylinder(float min, float max, bool isClose = false);
	Cylinder(Cylinder const& other);
	Cylinder(Cylinder&& other) noexcept;

	// Destructors
	~Cylinder() = default;

	// Member functions
	Cylinder& operator=(Cylinder const& other);
	Cylinder& operator=(Cylinder&& other) noexcept;
	friend std::ostream& operator<<(std::ostream& flux, Cylinder const& Cylinder);
	std::vector<Intersection> Intersect(Ray const& ray) override;
	void IntersectCaps(const Ray& transRay, std::vector<Intersection>& hits);
	bool CheckCap(const Ray& transRay, const double& t);
	Vector GetNormal(Point const& worldPoint, Intersection const& i) const override;
	Vector CalculateLocalNormal(Point const& localPoint, Intersection const& i) const override;
};
