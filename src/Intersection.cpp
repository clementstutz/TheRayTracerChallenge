#include <vector>
#include <ostream>
#include <algorithm> // Pour std::sort
#include "Intersection.h"
#include "RayObject.h"

// Constructors
Intersection::Intersection() : m_rayObject(nullptr), m_length(0.0f) {}

Intersection::Intersection(const RayObject& obj, float const& length) :
    m_rayObject(&obj),  // Initialise le pointeur à l'adresse de l'objet passé en paramètre
    m_length(length) {}

Intersection::Intersection(Intersection const& other) :
    m_rayObject(other.m_rayObject),
    m_length(other.m_length) {}

Intersection::Intersection(Intersection&& other) noexcept :
    m_rayObject(std::exchange(other.m_rayObject, nullptr)),
    m_length(std::move(other.m_length)) {
    // Réinitialise l'objet source pour éviter des doublons
    other.m_length = 0.0f;
}


// Destructor
Intersection::~Intersection() {}


// Accessors
const RayObject* Intersection::getObjPtr() const {
    return m_rayObject;
}

const RayObject& Intersection::getObj() const {
    if (!m_rayObject) {
        throw std::runtime_error("m_rayObject is null. Invalid access.");
    }
    return *m_rayObject; // Déréférencement du pointeur
}

float Intersection::getLength() const {return m_length;}


// Operators

Intersection& Intersection::operator=(const Intersection& other) {
    if (this != &other) { // Vérifie que ce n'est pas une auto-affectation
        m_rayObject = other.m_rayObject; // Assigne le pointeur
        m_length = other.m_length;
    }
    return *this;
}

Intersection& Intersection::operator=(Intersection&& other) noexcept {
    if (this != &other) { // Vérifie que ce n'est pas une auto-affectation
        m_rayObject = std::exchange(other.m_rayObject, nullptr);
        m_length = std::move(other.m_length);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& flux, Intersection const& intersection) {
    intersection.afficher(flux);
    return flux;
}


// Member-functions
void Intersection::afficher(std::ostream& flux) const {
	flux << "Intersection (objId: " << m_rayObject->GetId() << ", value : " << m_length << ")";
}

//std::vector<Intersection> Intersection::SortIntersections(std::vector<Intersection>& Intersections) {
//    // NOTE : USE AN ITERATOR !!!
//    if (Intersections.empty()) {
//        return Intersections;
//    }
//
//    std::vector<Intersection> sortedIntersections;
//
//    sortedIntersections.push_back(Intersections[0]);
//
//    int currentIntersection = 1;
//    bool valueInserted = false;
//
//    while (currentIntersection < Intersections.size()) {
//        valueInserted = false;
//        for (int i = 0; i < sortedIntersections.size(); i++) {
//            if (Intersections[currentIntersection].getLength() < sortedIntersections[i].getLength()) {
//                sortedIntersections.insert(sortedIntersections.begin() + i, Intersections[currentIntersection]);
//                currentIntersection++;
//                valueInserted = true;
//                break;
//            }
//        }
//
//        if (!valueInserted) {
//            sortedIntersections.push_back(Intersections[currentIntersection]);
//            currentIntersection++;
//        }
//    }
//    return sortedIntersections;
//}

std::vector<Intersection>& Intersection::SortIntersections(std::vector<Intersection>& intersections) {
    if (intersections.empty()) {
        return intersections;
    }

    // Tri des intersections par longueur croissante
    std::sort(intersections.begin(), intersections.end(), [](const Intersection& a, const Intersection& b) {
            return a.getLength() < b.getLength();
        });

    return intersections;
}