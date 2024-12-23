#include "RayObject_for_Test.h"
#include "Point.h"
#include "Vector.h"

// Constructors
RayObject_for_Test::RayObject_for_Test() : RayObject() {}

RayObject_for_Test::RayObject_for_Test(RayObject_for_Test const& other) :
    RayObject(other) {}

RayObject_for_Test::RayObject_for_Test(RayObject_for_Test&& other) noexcept :
    RayObject(std::move(other)) {}


// Member functions
RayObject_for_Test& RayObject_for_Test::operator=(RayObject_for_Test const& other) {
    if (this != &other) {
        RayObject::operator=(other); // Appelle l'op�rateur d'affectation par copie de la classe m�re
    }
    return *this;
}

RayObject_for_Test& RayObject_for_Test::operator=(RayObject_for_Test&& other) noexcept {
    if (this != &other) {
        RayObject::operator=(std::move(other)); // Appelle l'op�rateur d'affectation par d�placement de la classe m�re
    }
    return *this;
}

std::vector<Intersection> RayObject_for_Test::Intersect(Ray const& ray) {
    std::vector<Intersection> intersectionPoints;
    intersectionPoints.push_back(Intersection(*this, 1.0));
    return intersectionPoints;
}

Vector RayObject_for_Test::GetNormal(Point const& worldPoint, Intersection const& i) const {
    return CalculateLocalNormal(worldPoint, i);
}

Vector RayObject_for_Test::CalculateLocalNormal(Point const& localPoint, Intersection const& i) const {
    return Vector(1, 2, 3);
}