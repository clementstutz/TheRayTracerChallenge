#include "Sphere.h"
#include "Point.h"
#include "Vector.h"

// Constructors
Sphere::Sphere() : RayObject() {}

Sphere::Sphere(Sphere const& other) : RayObject(other) {}

Sphere::Sphere(Sphere&& other) noexcept : RayObject(std::move(other)) {}


// Member functions
Sphere& Sphere::operator=(Sphere const& other) {
    if (this != &other) {
        RayObject::operator=(other); // Appelle l'opérateur d'affectation par copie de la classe mère
        // Copiez ici des membres spécifiques à Sphere si nécessaire
    }
    return *this;
}

Sphere& Sphere::operator=(Sphere&& other) noexcept {
    if (this != &other) { // Vérification d'auto-affectation
        RayObject::operator=(std::move(other)); // Appelle l'opérateur d'affectation par déplacement de la classe mère
        // Déplacez ici des membres spécifiques à Sphere si nécessaire
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
    float a = transRay.getDirection().Dot(transRay.getDirection());   //Should always be 1.0 NOTE: normaliser la direction pour éviter ce calcult et les erreur d'arondie!
    float b = 2.0f * transRay.getDirection().Dot(sphereToRay);
    float c = sphereToRay.Dot(sphereToRay) - 1.0f;
    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0)   // Miss.
        return intersectionPoints; //NOTE: pour optimiser on peut peut-être essayer de ne pas renvoyer de liste vide comme c'est le cas ici...

    float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
    float t2 = (-b + sqrt(discriminant)) / (2.0f * a);

    // NOTE: pour optimiser encore on pourrait regarder le signe de t1 et t2 et ne renvoyer que les valeur positiver
    // les valeurs négatives sont des intersection qui on lieu derrière la camera (normalement...)
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