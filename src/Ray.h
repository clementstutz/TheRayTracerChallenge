#pragma once
#include "Point.h"
#include "Vector.h"

class Ray
{
protected:
	Point m_origin;
	Vector m_direction;

	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Ray(Point origin, Vector direction);
	Ray(Ray const& other);

	// Destructor
	~Ray();

	// Accesseurs
	Point getOrigin() const;
	Vector getDirection() const;

	// Operators
	friend std::ostream& operator<<(std::ostream& flux, Ray const& ray);
	bool operator==(Ray const& other) const;
	Ray& operator*=(Mat4 const& mat);

	Point position(float t) const;
};

Ray operator*(Mat4 const& mat, Ray const& ray);