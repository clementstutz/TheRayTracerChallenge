#pragma once
#include "Tuple.h"

// Déclaration anticipée de la classe Point
class Point;

class Vector : public Tuple
{
protected:
	void afficher(std::ostream& flux) const;

public:
	// Constructeurs
	Vector(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	Vector(Tuple const& other);
	Vector& operator=(Vector const& other);

	// Destructeurs
	~Vector();

	// Opérateurs arithmétiques
	Vector& operator+=(const Vector& v);
	Vector& operator-=(const Vector& v);

	template <typename T>
	Vector& operator*=(T const& scalar) {
		float f_scalar = static_cast<float>(scalar);
		m_x *= f_scalar;
		m_y *= f_scalar;
		m_z *= f_scalar;
		m_w *= f_scalar;
        return *this;
    };

	Vector& Normalize();
	Vector Normalized();
	float Dot(Vector const& a);
	Vector Cross(Vector const& a);
};

Vector operator+(Point const& a, Point const& b);
Vector operator-(Point const& a, Point const& b);
Vector operator+(Vector const& a, Vector const& b);
Vector operator-(Vector const& a, Vector const& b);
Vector operator-(Vector const& v);

template <typename T>
Vector operator*(Vector const& a, T const& scalar) {
	Vector copie(a);
	copie.Vector::operator*=(scalar);
	return copie;
}
