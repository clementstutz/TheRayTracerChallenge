#include "Color.h"
#include "Utils.h"

// Définition des couleurs statiques
const Color Color::red = Color(1.0, 0.0, 0.0);
const Color Color::green = Color(0.0, 1.0, 0.0);
const Color Color::blue = Color(0.0, 0.0, 1.0);
const Color Color::cyan = Color(0.0, 1.0, 1.0);
const Color Color::magenta = Color(1.0, 0.0, 1.0);
const Color Color::yellow = Color(1.0, 1.0, 0.0);
const Color Color::white = Color(1.0, 1.0, 1.0);
const Color Color::grey = Color(0.5, 0.5, 0.5);
const Color Color::black = Color(0.0, 0.0, 0.0);


// Constructors
Color::Color(double r, double g, double b) : m_r(r), m_g(g), m_b(b) {}

Color::Color(Color const& other) :
	m_r(other.m_r),
	m_g(other.m_g),
	m_b(other.m_b) {}

Color::Color(Color&& other) noexcept {
	m_r = other.m_r;
	m_g = other.m_g;
	m_b = other.m_b;

	// Reset source object
	other.m_r = 0.0;
	other.m_g = 0.0;
	other.m_b = 0.0;
}


// Accesseurs
double Color::getR() const { return m_r; }
double Color::getG() const { return m_g; }
double Color::getB() const { return m_b; }


// Member functions
Color& Color::operator=(Color const& other) {
	if (this != &other) {
		m_r = other.m_r;
		m_g = other.m_g;
		m_b = other.m_b;
	}
	return *this;
}

Color& Color::operator=(Color&& other) noexcept {
	if (this != &other) {
		m_r = other.m_r;
		m_g = other.m_g;
		m_b = other.m_b;

		// Reset source object
		other.m_r = 0.0;
		other.m_g = 0.0;
		other.m_b = 0.0;
	}
	return *this;
}

bool Color::operator==(Color const& other) const {
	return Utils::FE(m_r, other.m_r) &&
		Utils::FE(m_g, other.m_g) &&
		Utils::FE(m_b, other.m_b);
}

Color& Color::operator+=(Color const& c) {
	m_r += c.getR();
	m_g += c.getG();
	m_b += c.getB();
	return *this;
}

Color& Color::operator-=(Color const& c) {
	m_r -= c.getR();
	m_g -= c.getG();
	m_b -= c.getB();
	return *this;
}

Color& Color::operator*=(Color const& c) {
	m_r *= c.getR();
	m_g *= c.getG();
	m_b *= c.getB();
	return *this;
}

std::ostream& operator<<(std::ostream& flux, Color const& color) {
	color.afficher(flux);
	return flux;
}

void Color::afficher(std::ostream& flux) const {
	flux << "Color (" << m_r << ", " << m_g << ", " << m_b << ")";
}


// Non-member functions
bool operator!=(Color const& a, Color const& b) {
	return !(a == b);
}

Color operator+(Color const& a, Color const& b) {
	Color copy(a);
	copy += b;
	return copy;
}

Color operator-(Color const& a, Color const& b) {
	Color copy(a);
	copy -= b;
	return copy;
}

Color operator-(Color const& c) {
	Color copy(-c.getR(), -c.getG(), -c.getB());
	return copy;
}

Color operator*(Color const& a, Color const& b) {
	Color copy(a);
	copy *= b;
	return copy;
}
