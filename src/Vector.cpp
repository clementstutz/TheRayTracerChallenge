#include "Vector.h"
#include "Point.h"
#include "Mat4.h"

// Constructors
Vector::Vector(double x, double y, double z, double w) : Tuple(x, y, z, w) {}

Vector::Vector(Vector const& other) : Tuple(other.getX(), other.getY(), other.getZ(), other.getW()) {}

Vector::Vector(Vector&& other) noexcept : Tuple(std::move(other)) {}


// Destructor
Vector::~Vector() {}


// Member functions
void Vector::set(double newX, double newY, double newZ, double newW) {
    m_x = newX;
    m_y = newY;
    m_z = newZ;
    m_w = newW;
}

void Vector::afficher(std::ostream& flux) const {
    flux << "Vector (" << m_x << ", " << m_y << ", " << m_z << ")";
}

Vector& Vector::operator=(Vector const& other) {
    if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;
        //m_w = other.m_w;
    }
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;
        //m_w = other.m_w;
    }
    return *this;
}

Vector& Vector::operator+=(const Vector& v) {
    m_x += v.getX();
    m_y += v.getY();
    m_z += v.getZ();
    return *this;
}

Vector& Vector::operator-=(const Vector& v) {
    m_x -= v.getX();
    m_y -= v.getY();
    m_z -= v.getZ();
    return *this;
}

Vector& Vector::Normalize() {
    double mag = this->Magnitude();
    this->m_x = this->m_x / mag;
    this->m_y = this->m_y / mag;
    this->m_z = this->m_z / mag;
    return *this;
}

Vector Vector::Normalized() {
    Vector temp;
    double mag = this->Magnitude();
    temp.m_x = this->m_x / mag;
    temp.m_y = this->m_y / mag;
    temp.m_z = this->m_z / mag;
    return temp;
}

double Vector::Dot(Vector const& a) const {
    return this->m_x * a.m_x + this->m_y * a.m_y + this->m_z * a.m_z;
}

Vector Vector::Cross(Vector const& b) {
    Vector temp;
    temp.m_x = this->m_y * b.m_z - b.m_y * this->m_z;
    temp.m_y = this->m_z * b.m_x - b.m_z * this->m_x;
    temp.m_z = this->m_x * b.m_y - b.m_x * this->m_y;
    return temp;
}

Vector Vector::Reflect(Vector const& incoming, Vector const& normal) {
    return incoming - (2.0 * incoming.Dot(normal) * normal);
    //formule : r - i = - 2 * (i dot n) * n -> r = i - 2 * (i dot n) * n
}


// Non-member functions
Vector operator+(Point const& a, Point const& b) {
    return Vector(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

Vector operator-(Point const& a, Point const& b) {
    return Vector(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}

Vector operator+(Vector const& a, Vector const& b) {
	Vector copy(a);
	copy += b;
	return copy;
}

Vector operator-(Vector const& a, Vector const& b) {
    Vector copy(a);
    copy -= b;
    return copy;
}

Vector operator-(Vector const& v) {
    Vector copy(-v.getX(), -v.getY(), -v.getZ());
    return copy;
}

Vector operator*(Mat4 const& m, Vector const& v) {
    double x = m[0][0] * v.getX() + m[0][1] * v.getY() + m[0][2] * v.getZ() + m[0][3] * v.getW();
    double y = m[1][0] * v.getX() + m[1][1] * v.getY() + m[1][2] * v.getZ() + m[1][3] * v.getW();
    double z = m[2][0] * v.getX() + m[2][1] * v.getY() + m[2][2] * v.getZ() + m[2][3] * v.getW();
    double w = m[3][0] * v.getX() + m[3][1] * v.getY() + m[3][2] * v.getZ() + m[3][3] * v.getW();
    return Vector(x, y, z, w);
}