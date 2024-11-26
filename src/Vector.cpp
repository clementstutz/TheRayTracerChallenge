#include "Vector.h"
#include "Point.h"

// Constructeurs
Vector::Vector(float x, float y, float z) : Tuple(x, y, z, 0.0f) {}

Vector::Vector(Tuple const& other) : Tuple(other.getX(), other.getY(), other.getZ(), 0.0f) {}

Vector& Vector::operator=(Vector const& other) {
    if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
        m_x = other.getX();
        m_y = other.getY();
        m_z = other.getZ();
        m_w = 0.0f;
    }
    return *this;
}

// Destructeurs
Vector::~Vector() {}

// Fonctions membres
void Vector::afficher(std::ostream& flux) const {
    flux << "Vector (" << m_x << ", " << m_y << ", " << m_z << ")";
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
    float mag = this->Magnitude();
    this->m_x = this->m_x / mag;
    this->m_y = this->m_y / mag;
    this->m_z = this->m_z / mag;
    return *this;
}

Vector Vector::Normalized() {
    Vector temp;
    float mag = this->Magnitude();
    temp.m_x = this->m_x / mag;
    temp.m_y = this->m_y / mag;
    temp.m_z = this->m_z / mag;
    return temp;
}

float Vector::Dot(Vector const& a) {
    return this->m_x * a.m_x + this->m_y * a.m_y + this->m_z * a.m_z;
}

Vector Vector::Cross(Vector const& b) {
    Vector temp;
    temp.m_x = this->m_y * b.m_z - b.m_y * this->m_z;
    temp.m_y = this->m_z * b.m_x - b.m_z * this->m_x;
    temp.m_z = this->m_x * b.m_y - b.m_x * this->m_y;
    return temp;
}

// Fonctions non-membres
Vector operator+(Point const& a, Point const& b) {
    return Vector(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

Vector operator-(Point const& a, Point const& b) {
    return Vector(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}

Vector operator+(Vector const& a, Vector const& b) {
	Vector copie(a);
	copie += b;
	return copie;
}

Vector operator-(Vector const& a, Vector const& b) {
    Vector copie(a);
    copie -= b;
    return copie;
}

Vector operator-(Vector const& v) {
    Vector copie(-v.getX(), -v.getY(), -v.getZ());
    return copie;
}
