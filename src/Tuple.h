#pragma once
#include <iostream>

class Tuple
{
protected:
	float m_x, m_y, m_z, m_w;

	virtual void afficher(std::ostream& flux) const;

public:
	// Constructors
	Tuple(float x = 0.0, float y = 0.0, float z = 0.0, float w = 0.0);
	Tuple(Tuple const& other);
	Tuple(Tuple&& other) noexcept;

	// Destructor
	virtual ~Tuple();

	// Accessors
	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;
	void set(float newX, float newY, float newZ, float newW);

	// Member - functions
	friend std::ostream& operator<<(std::ostream& flux, Tuple const& tuple);
	
	Tuple& operator=(Tuple const& other);

	Tuple& operator=(Tuple&& other) noexcept;

	bool operator==(Tuple const& other) const;

	template <typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, Tuple&>::type
	operator*=(T const& scalar) {
		float f_scalar = static_cast<float>(scalar);
		m_x *= f_scalar;
		m_y *= f_scalar;
		m_z *= f_scalar;
		m_w *= f_scalar;
		return *this;
	};

	// Surcharge de l'opérateur - pour obtenir l'opposé
	/*Tuple operator-() const {
		Tuple copy = *this;
		copy.m_x *= -1.0f;
		copy.m_y *= -1.0f;
		copy.m_z *= -1.0f;
		copy.m_w *= -1.0f;
		return copy;
	};*/

	float Magnitude() const;

	float SqrtMagnitude() const;
};

bool operator!=(Tuple const& a, Tuple const& b);

template <typename T>
Tuple operator*(Tuple const& t, T const& scalar) {
	Tuple copy(t);
	copy *= scalar;
	return copy;
}