#pragma once
#include "Tuple.h"

// Déclaration anticipée de la classe Vector
class Vector;

class Point : public Tuple
{
protected:
	void afficher(std::ostream& flux) const;

public:
	// Constructeurs
	Point(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	Point(Tuple const& other);
	Point& operator=(Point const& other);
	
	// Destructeurs
	~Point();

	// Opérateurs arithmétiques
	Point& operator+=(Vector const& v);
	Point& operator-=(Vector const& v);

	template <typename T>
	Point& operator*=(T const& scalar) {
		float f_scalar = static_cast<float>(scalar);
		m_x *= f_scalar;
		m_y *= f_scalar;
		m_z *= f_scalar;
		m_w *= f_scalar;
        return *this;
    };
};

Point operator+(Point const& p, Vector const& v);
Point operator+(Vector const& v, Point const& p);
Point operator-(Point const& p, Vector const& v);
Point operator-(Vector const& v, Point const& p);
Point operator-(Point const& p);

template <typename T>
Point operator*(Point const& a, T const& scalar) {
	Point copy(a);
	copy.Point::operator*=(scalar);
	return copy;
}
