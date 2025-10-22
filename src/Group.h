#pragma once

#include "Shape.h"
#include "Intersection.h"

class Group : public Shape
{
protected :
	std::vector<Shape*> m_children;

	void afficher(std::ostream& flux) const;

public :
	// Constructors
	Group();

	// Destructors
	~Group() = default;

	// Member functions
	Group& operator=(Group const& other);
	Group& operator=(Group&& other) noexcept;
	bool operator==(Group const& other) const;
	friend std::ostream& operator<<(std::ostream& flux, Group const& group);

	void AddChildren(Shape& shape);
	const std::vector<Shape*> GetChildrens() const;
	std::vector<Intersection> Intersect(Ray const& ray) override;
	Vector GetNormal(Point const& worldPoint, Intersection const& i) const;
	Vector CalculateLocalNormal(Point const& localPoint, Intersection const& i) const;
};

bool operator!=(Tuple const& a, Tuple const& b);
