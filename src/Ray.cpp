#include "Ray.h"

// Constructors
Ray::Ray(Point origin, Vector direction) :
    m_origin(origin),
    m_direction(direction) {}

Ray::Ray(Ray const& other) :
    m_origin(other.m_origin),
    m_direction(other.m_direction) {}

Ray::Ray(Ray&& other) noexcept :
    m_origin(std::move(other.m_origin)),
    m_direction(std::move(other.m_direction)) {
    other.m_origin = Point();
    other.m_direction = Vector();
}


// Accesseurs
Point Ray::getOrigin() const {return m_origin;}

Vector Ray::getDirection() const {return m_direction;}


// Member functions
bool Ray::operator==(Ray const& other) const {
    return (m_origin == other.m_origin &&
            m_direction == other.m_direction);
}

Ray& Ray::operator=(Ray const& other) {
    if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
        m_origin = other.m_origin;
        m_direction = other.m_direction;
    }
    return *this;
}

Ray& Ray::operator=(Ray&& other) noexcept {
    if (this != &other) {
        m_origin = std::move(other.m_origin);
        m_direction = std::move(other.m_direction);
        // Reset source object
        other.m_origin = Point();
        other.m_direction = Vector();
    }
    return *this;
}

Ray& Ray::operator*=(Mat4 const& mat) {
    m_origin = mat * m_origin;
    m_direction = mat * m_direction;
    return *this;
}

std::ostream& operator<<(std::ostream& flux, Ray const& ray) {
    ray.afficher(flux);
    return flux;
}

void Ray::afficher(std::ostream& flux) const {
    flux << "Ray (" << m_origin << " -> " << m_direction << ")";
}

Point Ray::position(float t) const {
    return m_origin + m_direction * t;
}


// Non-member functions
Ray operator*(Mat4 const& mat, Ray const& ray) {
    Ray copy(ray);
    copy *= mat;
    return copy;
}
