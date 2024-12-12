#include <vector>
#include <ostream>
#include <algorithm> // Pour std::sort

#include "Intersection.h"
#include "RayObject.h"

// Constructors
Intersection::Intersection() : m_rayObject(nullptr), m_length(0.0f) {}

Intersection::Intersection(const RayObject& obj, float const& length) :
    m_rayObject(&obj),
    m_length(length) {}

Intersection::Intersection(Intersection const& other) :
    m_rayObject(other.m_rayObject),
    m_length(other.m_length) {}

Intersection::Intersection(Intersection&& other) noexcept :
    m_rayObject(std::exchange(other.m_rayObject, nullptr)),
    m_length(std::move(other.m_length)) {
    // Reset source object pour éviter des doublons
    other.m_length = 0.0f;
}


// Accessors
const RayObject* Intersection::getObjPtr() const { return m_rayObject; }

const RayObject& Intersection::getObj() const {
    if (!m_rayObject) {
        throw std::runtime_error("m_rayObject is null. Invalid access.");
    }
    return *m_rayObject;
}

float Intersection::getLength() const { return m_length; }


// Member functions
Intersection& Intersection::operator=(const Intersection& other) {
    if (this != &other) {
        m_rayObject = other.m_rayObject;
        m_length = other.m_length;
    }
    return *this;
}

Intersection& Intersection::operator=(Intersection&& other) noexcept {
    if (this != &other) {
        m_rayObject = std::exchange(other.m_rayObject, nullptr);
        m_length = std::move(other.m_length);
        other.m_length = 0.0f;
    }
    return *this;
}

bool Intersection::operator==(Intersection const& other) {
    return (m_rayObject == other.m_rayObject) && (m_length == other.m_length);
}

std::ostream& operator<<(std::ostream& flux, Intersection const& intersection) {
    intersection.afficher(flux);
    return flux;
}

void Intersection::afficher(std::ostream& flux) const {
	flux << "Intersection (objId: " << m_rayObject->GetId() << ", value : " << m_length << ")";
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
    return (m_rayObject == nullptr && m_length == 0.0);
}
