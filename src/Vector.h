#pragma once
#include "Tuple.h"

// Déclaration anticipée de classes
class Point;
class Mat4;

class Vector : public Tuple
{
protected:
	virtual void afficher(std::ostream& flux) const;

public:
	// Constructeurs
	Vector(float x = 0.0, float y = 0.0, float z = 0.0, float w = 0.0);
	Vector(Vector const& other);
	Vector(Vector&& other) noexcept;

	// Destructeurs
	~Vector();

	void set(float newX, float newY, float newZ, float newW = 0.0);

	// Opérateurs
	Vector& operator=(Vector const& other);
	Vector& operator=(Vector&& other) noexcept;
	Vector& operator+=(const Vector& v);
	Vector& operator-=(const Vector& v);

	template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
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
	float Dot(Vector const& a) const;
	Vector Cross(Vector const& a);
	static Vector Reflect(Vector const& incoming, Vector & normal);
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

template <typename T>
Vector operator*(T const& scalar, Vector const& a) {
	Vector copie(a);
	copie.Vector::operator*=(scalar);
	return copie;
}

Vector operator*(Mat4 const& m, Vector const& v);