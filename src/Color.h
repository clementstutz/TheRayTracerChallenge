#pragma once
#include <ostream>

class Color
{
protected:
	double m_r, m_g, m_b;

	void afficher(std::ostream& flux) const;

public:
	// Déclaration des couleurs statiques
	static const Color red;
	static const Color green;
	static const Color blue;
	static const Color cyan;
	static const Color magenta;
	static const Color yellow;
	static const Color white;
	static const Color grey;
	static const Color black;


	// Constructors
	Color(double r = 0.0, double g = 0.0, double b = 0.0);
	Color(Color const& other);
	Color(Color&& other) noexcept;


	// Destructor
	virtual ~Color() = default;


	// Accessors
	double getR() const;
	double getG() const;
	double getB() const;


	// Member functions
	Color& operator=(Color const& other);
	Color& operator=(Color&& other) noexcept;
	bool operator==(Color const& other) const;
	Color& operator+=(Color const& c);
	Color& operator-=(Color const& c);
	Color& operator*=(Color const& c);
	friend std::ostream& operator<<(std::ostream& flux, Color const& color);
	template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	Color& operator*=(T const& scalar) {
		double f_scalar = static_cast<double>(scalar);
		m_r *= f_scalar;
		m_g *= f_scalar;
		m_b *= f_scalar;
		return *this;
	};
};

bool operator!=(Color const& a, Color const& b);
Color operator+(Color const& a, Color const& b);
Color operator-(Color const& a, Color const& b);
Color operator-(Color const& c);
Color operator*(Color const& a, Color const& b);
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Color operator*(Color const& c, T const& scalar) {
	Color copy(c);
	copy.Color::operator*=(scalar);
	return copy;
};
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Color operator*(T const& scalar, Color const& c) {
	Color copy(c);
	copy.Color::operator*=(scalar);
	return copy;
};
