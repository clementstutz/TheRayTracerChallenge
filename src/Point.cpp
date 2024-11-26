#include "Point.h"
#include "Vector.h"

// Constructeurs
Point::Point(float x, float y, float z) : Tuple(x, y, z, 1.0f) {}

Point::Point(Tuple const& other) : Tuple(other.getX(), other.getY(), other.getZ(), 1.0f) {}

Point& Point::operator=(Point const& other) {
    if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;
        m_w = 1.0f;
    }
    return *this;
}

// Destructeur
Point::~Point() {}

// Fonctions membres
void Point::afficher(std::ostream & flux) const {
	flux << "Point (" << m_x << ", " << m_y << ", " << m_z << ")";
}

Point& Point::operator+=(Vector const& v) {
    m_x += v.getX();
    m_y += v.getY();
    m_z += v.getZ();
    return *this;
}

Point& Point::operator-=(Vector const& v) {
    m_x -= v.getX();
    m_y -= v.getY();
    m_z -= v.getZ();
    return *this;
}

// Fonctions non-membres
Point operator+(Point const& p, Vector const& v) {
    Point copy(p);
    copy += v;
    return copy;
}

Point operator+(Vector const& v, Point const& p) {
    Point copy(p);
    copy += v;
    return copy;
}

Point operator-(Point const& p, Vector const& v) {
    Point copy(p);
    copy -= v;
    return copy;
}

Point operator-(Vector const& v, Point const& p) {
    Point copy(-p);
    copy += v; //Ca marche mais je ne sais pas pourquoi. Je n'ai pas défini l'opérateur -= entre deux points.
    return copy;
}

Point operator-(Point const& p) {
    Point copy(-p.getX(), -p.getY(), -p.getZ());
    return copy;
}
