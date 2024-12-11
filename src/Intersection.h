#pragma once
#include <vector>
//#include "RayObject.h"

class RayObject;

class Intersection
{
protected:
	const RayObject* m_rayObject;
	float m_length;

	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Intersection();
	Intersection(const RayObject& obj, float const& length);
	Intersection(Intersection const& other);
	Intersection(Intersection&& other) noexcept;

	// Destructor
	~Intersection();

	// Accessors
	const RayObject* getObjPtr() const;
	const RayObject& getObj() const;
	float getLength() const;

	// Operators
	Intersection& operator=(const Intersection& other);	// NOTE : Nécessaire sinon erreurs suivantes : 
	Intersection& operator=(Intersection&& other) noexcept;
	friend std::ostream& operator<<(std::ostream& flux, Intersection const& intersection);

	// Member-functions
	static std::vector<Intersection>& SortIntersections(std::vector<Intersection>& intersections);
};

