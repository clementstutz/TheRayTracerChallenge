#pragma once
#include "Tuple.h"

// Déclaration anticipée de la classe Vector
class Vector;
class Mat4;

class Point : public Tuple
{
protected:
	virtual void afficher(std::ostream& flux) const;

public:
	// Constructors
	Point(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	Point(Point const& other);
	Point(Point&& other) noexcept;
	

	// Destructor
	~Point();


	// Member functions
	void set(float newX, float newY, float newZ, float newW = 1.0);
	Point& operator=(Point const& other);
	Point& operator=(Point&& other) noexcept;
	Point& operator+=(Vector const& v);
	Point& operator-=(Vector const& v);
	template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
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
Point operator*(Mat4 const& m, Point const& p);
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Point operator*(Point const& a, T const& scalar) {
	Point copy(a);
	copy.Point::operator*=(scalar);
	return copy;
}
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Point operator*(T const& scalar, Point const& a) {
	Point copy(a);
	copy.Point::operator*=(scalar);
	return copy;
}
