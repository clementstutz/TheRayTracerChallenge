#include "Tuple.h"
#include "Utils.h"
#include <iostream>
#include <cmath>

// Constructeurs
Tuple::Tuple(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}

Tuple::Tuple(Tuple const& other) : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z), m_w(other.m_w) {}

Tuple& Tuple::operator=(Tuple const& other) {
	if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
		m_x = other.m_x;
		m_y = other.m_y;
		m_z = other.m_z;
		m_w = other.m_w;
	}
	return *this;
}

// Destructeur
Tuple::~Tuple() {}

// Accesseurs
float Tuple::getX() const {return m_x;}
float Tuple::getY() const {return m_y;}
float Tuple::getZ() const {return m_z;}
float Tuple::getW() const {return m_w;}

// Fonctions membres
void Tuple::afficher(std::ostream& flux) const {
	flux << "Tuple (" << m_x << ", " << m_y << ", " << m_z << ", " << m_w << ")";
}

std::ostream& operator<<(std::ostream& flux, Tuple const& tuple) {
	tuple.afficher(flux);
	return flux;
}

bool Tuple::operator==(Tuple const& other) const {
	return Utils::FE(m_x, other.m_x) &&
		   Utils::FE(m_y, other.m_y) &&
		   Utils::FE(m_z, other.m_z) &&
		   Utils::FE(m_w, other.m_w);
}

float Tuple::Magnitude() const {
	return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

float Tuple::SqrtMagnitude() const{
	return m_x * m_x + m_y * m_y + m_z * m_z;
}

// Fonctions non-membres
bool operator!=(Tuple const& a, Tuple const& b) {
	return !(a == b);
}
