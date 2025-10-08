#pragma once

#include "RayObject.h"
#include "Intersection.h"

class Cone : public RayObject
{
protected :
    double m_minimum;
    double m_maximum;
    bool m_isClosed;	// WARNING : dissocier isClose en isTopClose et isBottomClose
	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Cone();
	Cone(float min, float max, bool isClose = false);
	Cone(Cone const& other);
	Cone(Cone&& other) noexcept;

	// Destructors
	~Cone() = default;

	// Member functions
	Cone& operator=(Cone const& other);
	Cone& operator=(Cone&& other) noexcept;
	friend std::ostream& operator<<(std::ostream& flux, Cone const& Cone);
	std::vector<Intersection> Intersect(Ray const& ray) override;
	void IntersectCaps(const Ray& transRay, std::vector<Intersection>& hits);
	bool CheckCap(const Ray& transRay, const double& t);
	Vector GetNormal(Point const& worldPoint, Intersection const& i) const override;
	Vector CalculateLocalNormal(Point const& localPoint, Intersection const& i) const override;
};

