#pragma once
#include <array>

#include "RayObject.h"
#include "Intersection.h"

class Cube : public RayObject
{
private:
	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Cube();
	Cube(Cube const& other);
	Cube(Cube&& other) noexcept;

	// Destructor
	~Cube() = default;

	// Member functions
	Cube& operator=(Cube const& other);
	Cube& operator=(Cube&& other) noexcept;
	friend std::ostream& operator<<(std::ostream& flux, Cube const& Cube);
	std::array<double, 2> CheckAxis(const double& origin, const double& direction);
	std::vector<Intersection> Intersect(Ray const& ray) override;
	Vector GetNormal(Point const& worldPoint, Intersection const& i) const override;
	Vector CalculateLocalNormal(Point const& localPoint, Intersection const& i) const override;
};

