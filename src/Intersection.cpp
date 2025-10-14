#include <vector>
#include <ostream>
#include <algorithm> // Pour std::sort

#include "Intersection.h"
#include "Shape.h"

// Constructors
Intersection::Intersection() : m_shape(nullptr), m_length(0.0) {}

Intersection::Intersection(const Shape& obj, double const& length) :
    m_shape(&obj),
    m_length(length) {}

Intersection::Intersection(Intersection const& other) :
    m_shape(other.m_shape),
    m_length(other.m_length) {}

Intersection::Intersection(Intersection&& other) noexcept :
    m_shape(std::exchange(other.m_shape, nullptr)),
    m_length(std::move(other.m_length)) {
    // Reset source object pour �viter des doublons
    other.m_length = 0.0;
}


// Accessors
const Shape* Intersection::getObjPtr() const { return m_shape; }

const Shape& Intersection::getObj() const {
    if (!m_shape) {
        throw std::runtime_error("m_shape is null. Invalid access.");
    }
    return *m_shape;
}

double Intersection::getLength() const { return m_length; }


// Member functions
Intersection& Intersection::operator=(const Intersection& other) {
    if (this != &other) {
        m_shape = other.m_shape;
        m_length = other.m_length;
    }
    return *this;
}

Intersection& Intersection::operator=(Intersection&& other) noexcept {
    if (this != &other) {
        m_shape = std::exchange(other.m_shape, nullptr);
        m_length = std::move(other.m_length);
        other.m_length = 0.0;
    }
    return *this;
}

bool Intersection::operator==(Intersection const& other) const {
    return (m_shape == other.m_shape) && (m_length == other.m_length);
}

std::ostream& operator<<(std::ostream& flux, Intersection const& intersection) {
    intersection.afficher(flux);
    return flux;
}

void Intersection::afficher(std::ostream& flux) const {
	flux << "Intersection (objId: " << m_shape->GetId() << ", value : " << m_length << ")";
}

std::vector<Intersection>& Intersection::SortIntersections(std::vector<Intersection>& intersections) {
    if (intersections.empty()) {
        return intersections;
    }

    std::sort(intersections.begin(), intersections.end(), [](const Intersection& a, const Intersection& b) {
            return a.getLength() < b.getLength();
        });

    return intersections;
}

bool Intersection::IsEmpty() const {
    return (m_shape == nullptr && m_length == 0.0);
}
