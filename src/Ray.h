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
	Ray(Ray&& other) noexcept;


	// Destructor
	~Ray() = default;


	// Accessors
	Point getOrigin() const;
	Vector getDirection() const;


	// Member functions
	bool operator==(Ray const& other) const;
	Ray& operator=(Ray const& other);
	Ray& operator=(Ray&& other) noexcept;
	Ray& operator*=(Mat4 const& mat);
	friend std::ostream& operator<<(std::ostream& flux, Ray const& ray);
	Point position(float t) const;
};

Ray operator*(Mat4 const& mat, Ray const& ray);