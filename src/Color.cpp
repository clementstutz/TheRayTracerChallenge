#include "Color.h"
#include "Utils.h"

// Constructeurs
Color::Color(float r, float g, float b) : m_r(r), m_g(g), m_b(b) {}

Color::Color(Color const& other) : m_r(other.m_r), m_g(other.m_g), m_b(other.m_b) {}

Color& Color::operator=(Color const& other) {
	if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
		m_r = other.m_r;
		m_g = other.m_g;
		m_b = other.m_b;
	}
	return *this;
}

// Destructeur
Color::~Color() {}

// Définition des couleurs statiques
const Color Color::red = Color(1.0f, 0.0f, 0.0f);
const Color Color::green = Color(0.0f, 1.0f, 0.0f);
const Color Color::blue = Color(0.0f, 0.0f, 1.0f);
const Color Color::cyan = Color(0.0f, 1.0f, 1.0f);
const Color Color::magenta = Color(1.0f, 0.0f, 1.0f);
const Color Color::yellow = Color(1.0f, 1.0f, 0.0f);
const Color Color::white = Color(1.0f, 1.0f, 1.0f);
const Color Color::grey = Color(0.5f, 0.5f, 0.5f);
const Color Color::black = Color(0.0f, 0.0f, 0.0f);

// Accesseurs
float Color::getR() const { return m_r; }

float Color::getG() const { return m_g; }

float Color::getB() const { return m_b; }

// Fonctions membres
void Color::afficher(std::ostream& flux) const {
	flux << "Color (" << m_r << ", " << m_g << ", " << m_b << ")";
}

std::ostream& operator<<(std::ostream& flux, Color const& color) {
	color.afficher(flux);
	return flux;
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

// Fonctions non-membres
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
