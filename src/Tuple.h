#pragma once
#include <iostream>

class Tuple
{
protected:
	double m_x, m_y, m_z, m_w;

	virtual void afficher(std::ostream& flux) const;

public:
	// Constructors
	Tuple(double x = 0.0, double y = 0.0, double z = 0.0, double w = 0.0);
	Tuple(Tuple const& other);
	Tuple(Tuple&& other) noexcept;


	// Destructor
	virtual ~Tuple();


	// Accessors
	double getX() const;
	double getY() const;
	double getZ() const;
	double getW() const;
	void set(double newX, double newY, double newZ, double newW);


	// Member functions
	friend std::ostream& operator<<(std::ostream& flux, Tuple const& tuple);
	
	Tuple& operator=(Tuple const& other);

	Tuple& operator=(Tuple&& other) noexcept;

	bool operator==(Tuple const& other) const;

	template <typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, Tuple&>::type
	operator*=(T const& scalar) {
		double f_scalar = static_cast<double>(scalar);
		m_x *= f_scalar;
		m_y *= f_scalar;
		m_z *= f_scalar;
		m_w *= f_scalar;
		return *this;
	};

	double Magnitude() const;

	double SqrtMagnitude() const;
};

bool operator!=(Tuple const& a, Tuple const& b);
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Tuple operator*(Tuple const& t, T const& scalar) {
	Tuple copy(t);
	copy *= scalar;
	return copy;
}