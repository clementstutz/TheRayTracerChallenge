#include "RayObject_for_Test.h"
#include "Point.h"
#include "Vector.h"

// Constructors
RayObject_for_Test::RayObject_for_Test() : RayObject() {}

RayObject_for_Test::RayObject_for_Test(RayObject_for_Test const& other) : RayObject(other) {}

RayObject_for_Test::RayObject_for_Test(RayObject_for_Test&& other) noexcept : RayObject(std::move(other)) {}


// Destructor
RayObject_for_Test::~RayObject_for_Test() {}


// Operators
RayObject_for_Test& RayObject_for_Test::operator=(RayObject_for_Test const& other) {
    if (this != &other) { // V�rification d'auto-affectation
        RayObject::operator=(other); // Appelle l'op�rateur d'affectation par copie de la classe m�re
    }
    return *this;
}

RayObject_for_Test& RayObject_for_Test::operator=(RayObject_for_Test&& other) noexcept {
    if (this != &other) { // V�rification d'auto-affectation
        RayObject::operator=(std::move(other)); // Appelle l'op�rateur d'affectation par d�placement de la classe m�re
    }
    return *this;
}


// Member-functions
std::vector<Intersection> RayObject_for_Test::Intersect(Ray ray) {
    std::vector<Intersection> intersectionPoints;
    intersectionPoints.push_back(Intersection(*this, 1.0f));
    return intersectionPoints;
}

Vector RayObject_for_Test::GetNormal(Point const& worldPoint, Intersection const& i) const {
    return CalculateLocalNormal(worldPoint, i);
}

Vector RayObject_for_Test::CalculateLocalNormal(Point const& localPoint, Intersection const& i) const {
    return Vector(1, 2, 3);
}