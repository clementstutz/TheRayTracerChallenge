#include "Ray.h"

// Constructeurs
Ray::Ray(Point origin, Vector direction) : m_origin(origin), m_direction(direction) {}

Ray::Ray(Ray const& other) {
    m_origin = other.m_origin;
    m_direction = other.m_direction;
}

// Destructor
Ray::~Ray() {}

// Accesseurs
Point Ray::getOrigin() const {return m_origin;}

Vector Ray::getDirection() const {return m_direction;}

bool Ray::operator==(Ray const& other) const {
    return (m_origin == other.m_origin &&
            m_direction == other.m_direction);
}

// Opérators
Ray& Ray::operator*=(Mat4 const& mat) {
    m_origin = mat * m_origin;
    m_direction = mat * m_direction;
    return *this;
}

void Ray::afficher(std::ostream& flux) const {
    flux << "Ray (" << m_origin << " -> " << m_direction << ")";
}

std::ostream& operator<<(std::ostream& flux, Ray const& ray) {
    ray.afficher(flux);
    return flux;
}

Point Ray::position(float t) const {
    return m_origin + m_direction * t;
}

Ray operator*(Mat4 const& mat, Ray const& ray) {
    Ray copy(ray);
    copy *= mat;
    return copy;
}
