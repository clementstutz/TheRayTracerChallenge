#include "Shape_for_Test.h"
#include "Point.h"
#include "Vector.h"

// Constructors
Shape_for_Test::Shape_for_Test() : Shape() {}

Shape_for_Test::Shape_for_Test(Shape_for_Test const& other) :
    Shape(other) {}

Shape_for_Test::Shape_for_Test(Shape_for_Test&& other) noexcept :
    Shape(std::move(other)) {}


// Member functions
Shape_for_Test& Shape_for_Test::operator=(Shape_for_Test const& other) {
    if (this != &other) {
        Shape::operator=(other); // Appelle l'op�rateur d'affectation par copie de la classe m�re
    }
    return *this;
}

Shape_for_Test& Shape_for_Test::operator=(Shape_for_Test&& other) noexcept {
    if (this != &other) {
        Shape::operator=(std::move(other)); // Appelle l'op�rateur d'affectation par d�placement de la classe m�re
    }
    return *this;
}

std::vector<Intersection> Shape_for_Test::Intersect(Ray const& ray) {
    std::vector<Intersection> intersectionPoints;
    intersectionPoints.push_back(Intersection(*this, 1.0));
    return intersectionPoints;
}

Vector Shape_for_Test::GetNormal(Point const& worldPoint, Intersection const& i) const {
    return CalculateLocalNormal(worldPoint, i);
}

Vector Shape_for_Test::CalculateLocalNormal(Point const& localPoint, Intersection const& i) const {
    return Vector(1, 2, 3);
}
