#pragma once
#include <vector>
//#include "Shape.h"

// D�claration anticip�e de classes
class Shape;

class Intersection
{
protected:
	const Shape* m_shape;
	double m_length;

	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Intersection();
	Intersection(const Shape& obj, double const& length);
	Intersection(Intersection const& other);
	Intersection(Intersection&& other) noexcept;


	// Destructor
	~Intersection() = default;


	// Accessors
	const Shape* getObjPtr() const;
	const Shape& getObj() const;
	double getLength() const;


	// Member functions
	Intersection& operator=(const Intersection& other);	// NOTE : N�cessaire sinon erreurs suivantes :
	Intersection& operator=(Intersection&& other) noexcept;
	bool operator==(Intersection const& other) const;
	friend std::ostream& operator<<(std::ostream& flux, Intersection const& intersection);
	static std::vector<Intersection>& SortIntersections(std::vector<Intersection>& intersections);
	bool IsEmpty() const;
};
