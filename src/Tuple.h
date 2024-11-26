#pragma once
#include <iostream>
#include <cmath>
#include "Utils.h"

//template <class Derived>
class Tuple
{
protected:
	float m_x, m_y, m_z, m_w;

	void afficher(std::ostream& flux) const;

public:
	// Constructeurs
	Tuple(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
	Tuple(Tuple const& other);
	Tuple& operator=(Tuple const& other);

	// Destructeur
	virtual ~Tuple();

	// Accesseurs
	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;

	//opérateurs
	friend std::ostream& operator<<(std::ostream& flux, Tuple const& tuple);
	
	bool operator==(Tuple const& other) const;

	template <typename T>
	Tuple& operator*=(T const& scalar) {
		float f_scalar = static_cast<float>(scalar);
		m_x *= f_scalar;
		m_y *= f_scalar;
		m_z *= f_scalar;
		m_w *= f_scalar;
		return *this;
	};

	/*template <typename T>
	Tuple operator*(T const& scalar) const {
		Derived copy = static_cast<Derived const&>(*this);
		copy *= scalar;
		return copy;
	};*/

	// Surcharge de l'opérateur - pour obtenir l'opposé
	/*Tuple operator-() const {
		Tuple copy = *this;
		copy.m_x *= -1.0f;
		copy.m_y *= -1.0f;
		copy.m_z *= -1.0f;
		copy.m_w *= -1.0f;
		return copy;
	};*/

	/*template <typename T>
	Tuple& Scale(T const& scalar)
	{
		return *this *= scalar;
	}*/

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