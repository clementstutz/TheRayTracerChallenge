#pragma once
#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"

class RayObject;

class Computations
{
private:
	float m_t;
	const RayObject* m_rayObject;
	Point m_point;
	Vector m_eye;
	Vector m_normal;
	bool m_inside;
	Point m_overPoint;
	Point m_underPoint;
	Vector m_reflectVector;
	float m_n1;
	float m_n2;

public:
	// Constructors
	Computations();
	Computations(RayObject &rayObject, float &t, Point &point, Vector &eye, Vector &normal, bool inside);

	// Destructor
	~Computations();

	// Accessors
	float GetLength() const;
	const RayObject* GetRayObjectPtr() const;
	const RayObject& GetRayObject() const;
	Point GetPoint() const;
	Vector GetEye() const;
	Vector GetNormal() const;
	bool GetInside() const;
	Point GetOverPoint() const;
	Point GetUnderPoint() const;
	Vector GetReflectVector() const;
	float GetN1() const;
	float GetN2() const;

	// Member-functions
	static Computations Prepare(Intersection const& i, Ray const& ray, std::vector<Intersection> const* xs);//NOTE : Comment mettre une valeur pas défaut à 0 pour xs ?
};

