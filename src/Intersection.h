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
	~Intersection() = default;


	// Accessors
	const RayObject* getObjPtr() const;
	const RayObject& getObj() const;
	float getLength() const;


	// Member functions
	Intersection& operator=(const Intersection& other);	// NOTE : Nécessaire sinon erreurs suivantes : 
	Intersection& operator=(Intersection&& other) noexcept;
	bool operator==(Intersection const& other);
	friend std::ostream& operator<<(std::ostream& flux, Intersection const& intersection);
	static std::vector<Intersection>& SortIntersections(std::vector<Intersection>& intersections);
	bool IsEmpty() const;
};
