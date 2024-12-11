#include "Point.h"
#include "Vector.h"
#include "Mat4.h"

// Constructeurs
Point::Point(float x, float y, float z, float w) : Tuple(x, y, z, w) {}

Point::Point(Point const& other) : Tuple(other.getX(), other.getY(), other.getZ(), other.getW()) {}

Point::Point(Point&& other) noexcept : Tuple(std::move(other)) {}

// Destructeur
Point::~Point() {}

// Fonctions membres
void Point::set(float newX, float newY, float newZ, float newW) {
    m_x = newX;
    m_y = newY;
    m_z = newZ;
    m_w = newW;
}

void Point::afficher(std::ostream & flux) const {
	flux << "Point (" << m_x << ", " << m_y << ", " << m_z << ")";
}

Point& Point::operator=(Point const& other) {
    if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;
        m_w = other.m_w;
    }
    return *this;
}

Point& Point::operator=(Point&& other) noexcept {
    if (this != &other) {
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;
        m_w = other.m_w;
    }
    return *this;
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

Point operator*(Mat4 const& m, Point const& p) {
    float x = m[0][0] * p.getX() + m[0][1] * p.getY() + m[0][2] * p.getZ() + m[0][3] * p.getW();
    float y = m[1][0] * p.getX() + m[1][1] * p.getY() + m[1][2] * p.getZ() + m[1][3] * p.getW();
    float z = m[2][0] * p.getX() + m[2][1] * p.getY() + m[2][2] * p.getZ() + m[2][3] * p.getW();
    float w = m[3][0] * p.getX() + m[3][1] * p.getY() + m[3][2] * p.getZ() + m[3][3] * p.getW();
    Point temp(x, y, z, w);
    return temp;
}