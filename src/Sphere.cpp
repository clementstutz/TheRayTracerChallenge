#include <cmath>

#include "Sphere.h"
#include "Point.h"
#include "Vector.h"

// Constructors
Sphere::Sphere() : Shape() {}

Sphere::Sphere(Sphere const& other) : Shape(other) {}

Sphere::Sphere(Sphere&& other) noexcept : Shape(std::move(other)) {}


// Member functions
Sphere& Sphere::operator=(Sphere const& other) {
    if (this != &other) {
        Shape::operator=(other); // Appelle l'op�rateur d'affectation par copie de la classe m�re
        // Copiez ici des membres sp�cifiques � Sphere si n�cessaire
    }
    return *this;
}

Sphere& Sphere::operator=(Sphere&& other) noexcept {
    if (this != &other) { // V�rification d'auto-affectation
        Shape::operator=(std::move(other)); // Appelle l'op�rateur d'affectation par d�placement de la classe m�re
        // D�placez ici des membres sp�cifiques � Sphere si n�cessaire
    }
    return *this;
}

std::ostream& operator<<(std::ostream& flux, Sphere const& sphere) {
    sphere.afficher(flux);
    return flux;
}

void Sphere::afficher(std::ostream& flux) const {
    flux << "Sphere (id: " << m_id << ", Position: " << GetPosition() << ")";
}

std::vector<Intersection> Sphere::Intersect(Ray const& ray) {
	std::vector<Intersection> intersectionPoints;

	Ray transRay = RayToObjectSpace(ray);

    Vector sphereToRay = (transRay.getOrigin() - Point());
    double a = transRay.getDirection().Dot(transRay.getDirection());   //Should always be 1.0 NOTE: normaliser la direction pour �viter ce calcult et les erreur d'arondie!
    double b = 2.0 * transRay.getDirection().Dot(sphereToRay);
    double c = sphereToRay.Dot(sphereToRay) - 1.0;
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0)   // Miss.
        return intersectionPoints; //NOTE: pour optimiser on peut peut-�tre essayer de ne pas renvoyer de liste vide comme c'est le cas ici...

    double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

    // NOTE: pour optimiser encore on pourrait regarder le signe de t1 et t2 et ne renvoyer que les valeur positiver
    // les valeurs n�gatives sont des intersection qui on lieu derri�re la camera (normalement...)
    intersectionPoints.push_back(Intersection(*this, t1));
    intersectionPoints.push_back(Intersection(*this, t2));

    return intersectionPoints;
}

Vector Sphere::GetNormal(Point const &worldPoint, Intersection const &i) const {
    Point localPoint = WorldToObject(worldPoint);
    Vector localNormal = CalculateLocalNormal(localPoint, i);
    Vector worldNormal = NormalToWorld(localNormal);
    return worldNormal;
}

Vector Sphere::CalculateLocalNormal(Point const& localPoint, Intersection const & i) const {
    Vector normal(localPoint.getX(), localPoint.getY(), localPoint.getZ());
    return normal.Normalize(); // il faut normaliser ou pas ???
}
