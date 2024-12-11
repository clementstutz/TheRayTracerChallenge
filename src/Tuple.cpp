#include <cmath>

#include "Tuple.h"
#include "Utils.h"

// Constructors
Tuple::Tuple(float x, float y, float z, float w) :
	m_x(x),
	m_y(y),
	m_z(z),
	m_w(w) {}

Tuple::Tuple(Tuple const& other) :
	m_x(other.m_x),
	m_y(other.m_y),
	m_z(other.m_z),
	m_w(other.m_w) {}

Tuple::Tuple(Tuple&& other) noexcept :
	m_x(other.m_x),
	m_y(other.m_y),
	m_z(other.m_z),
	m_w(other.m_w) {
	// Réinitialise l'objet source pour éviter des doublons
	other.m_x = 0.0f;
	other.m_y = 0.0f;
	other.m_z = 0.0f;
	other.m_w = 0.0f;
}


// Destructor
Tuple::~Tuple() {}


// Accessors
float Tuple::getX() const {return m_x;}

float Tuple::getY() const {return m_y;}

float Tuple::getZ() const {return m_z;}

float Tuple::getW() const {return m_w;}

void Tuple::set(float newX, float newY, float newZ, float newW) {
	m_x = newX;
	m_y = newY;
	m_z = newZ;
	m_w = newW;
}


// Member functions
std::ostream& operator<<(std::ostream& flux, Tuple const& tuple) {
	tuple.afficher(flux);
	return flux;
}

Tuple& Tuple::operator=(Tuple const& other) {
	if (this != &other) {
		m_x = other.m_x;
		m_y = other.m_y;
		m_z = other.m_z;
		m_w = other.m_w;
	}
	return *this;
}

Tuple& Tuple::operator=(Tuple&& other) noexcept {
	if (this != &other) {
		m_x = other.m_x;
		m_y = other.m_y;
		m_z = other.m_z;
		m_w = other.m_w;

		// Réinitialise l'objet source
		other.m_x = 0.0f;
		other.m_y = 0.0f;
		other.m_z = 0.0f;
		other.m_w = 0.0f;
	}
	return *this;
}

bool Tuple::operator==(Tuple const& other) const {
	return Utils::FE(m_x, other.m_x) &&
		   Utils::FE(m_y, other.m_y) &&
		   Utils::FE(m_z, other.m_z) &&
		   Utils::FE(m_w, other.m_w);
}

void Tuple::afficher(std::ostream& flux) const {
	flux << "Tuple (" << m_x << ", " << m_y << ", " << m_z << ", " << m_w << ")";
}

float Tuple::Magnitude() const {
	return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

float Tuple::SqrtMagnitude() const{
	return m_x * m_x + m_y * m_y + m_z * m_z;
}


// Non-member functions
bool operator!=(Tuple const& a, Tuple const& b) {
	return !(a == b);
}
