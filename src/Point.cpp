#include "Point.h"
#include "Vector.h"
#include "Mat4.h"

// Constructors
Point::Point(double x, double y, double z, double w) : Tuple(x, y, z, w) {}

Point::Point(Point const& other) : Tuple(other.getX(), other.getY(), other.getZ(), other.getW()) {}

Point::Point(Point&& other) noexcept : Tuple(std::move(other)) {}


// Destructor
Point::~Point() {}


// Member functions
void Point::set(double newX, double newY, double newZ, double newW) {
    m_x = newX;
    m_y = newY;
    m_z = newZ;
    m_w = newW;
}

void Point::afficher(std::ostream & flux) const {
	flux << "Point (" << m_x << ", " << m_y << ", " << m_z << ")";
}

Point& Point::operator=(Point const& other) {
    if (this != &other) {
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


// Non-member functions
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
    copy += v;
    return copy;
}

Point operator-(Point const& p) {
    Point copy(-p.getX(), -p.getY(), -p.getZ());
    return copy;
}

Point operator*(Mat4 const& m, Point const& p) {
    double x = m[0][0] * p.getX() + m[0][1] * p.getY() + m[0][2] * p.getZ() + m[0][3] * p.getW();
    double y = m[1][0] * p.getX() + m[1][1] * p.getY() + m[1][2] * p.getZ() + m[1][3] * p.getW();
    double z = m[2][0] * p.getX() + m[2][1] * p.getY() + m[2][2] * p.getZ() + m[2][3] * p.getW();
    double w = m[3][0] * p.getX() + m[3][1] * p.getY() + m[3][2] * p.getZ() + m[3][3] * p.getW();
    Point temp(x, y, z, w);
    return temp;
}