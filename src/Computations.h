#pragma once
#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"

class RayObject;

class Computations
{
private:
	double m_t;
	const RayObject* m_rayObjectPtr;
	Point m_point;
	Vector m_eye;
	Vector m_normal;
	bool m_inside;
	Point m_overPoint;
	Point m_underPoint;
	Vector m_reflectVector;
	double m_n1;
	double m_n2;

public:
	// Constructors
	Computations();


	// Destructor
	~Computations() = default;


	// Accessors
	const double GetLength() const;
	const RayObject* GetRayObjectPtr() const;
	const RayObject& GetRayObject() const;
	const Point GetPoint() const;
	const Vector GetEye() const;
	const Vector GetNormal() const;
	const bool GetInside() const;
	const Point GetOverPoint() const;
	const Point GetUnderPoint() const;
	const Vector GetReflectVector() const;
	const double GetN1() const;
	const double GetN2() const;


	// Member functions
	static Computations Prepare(Intersection const& hit, Ray const& ray, std::vector<Intersection> const* xs = nullptr);
};

