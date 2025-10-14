#include <limits>  // for std::numeric_limits

#include "Cube.h"
#include "Utils.h"

// Constructors
Cube::Cube() : Shape() {}

Cube::Cube(Cube const& other) : Shape(other) {}

Cube::Cube(Cube&& other) noexcept : Shape(std::move(other)) {}


// Member functions
Cube& Cube::operator=(Cube const& other) {
    if (this != &other) {
        Shape::operator=(other); // Appelle l'op�rateur d'affectation par copie de la classe m�re
        // Copiez ici des membres sp�cifiques � Cube si n�cessaire
    }
    return *this;
}

Cube& Cube::operator=(Cube&& other) noexcept {
    if (this != &other) { // V�rification d'auto-affectation
        Shape::operator=(std::move(other)); // Appelle l'op�rateur d'affectation par d�placement de la classe m�re
        // D�placez ici des membres sp�cifiques � Cube si n�cessaire
    }
    return *this;
}

std::ostream& operator<<(std::ostream& flux, Cube const& Cube) {
    Cube.afficher(flux);
    return flux;
}

void Cube::afficher(std::ostream& flux) const {
    flux << "Cube (id: " << m_id << ", Position: " << GetPosition() << ")";
}

std::array<double, 2> Cube::CheckAxis(const double& origin, const double& direction) {
    std::array<double, 2> t;
    double tMinNumerator = (-1 - origin);
    double tMaxNumerator = (1 - origin);

    //Infinities might pop here due to division by zero
    if (std::abs(direction) >= Utils::GetEpsilon()) {
        t[0] = tMinNumerator / direction;
        t[1] = tMaxNumerator / direction;
    }
    else {
        t[0] = tMinNumerator * std::numeric_limits<double>::infinity();
        t[1] = tMaxNumerator * std::numeric_limits<double>::infinity();
    }

    if (t[0] > t[1]) {
        double temp = std::move(t[0]);
        t[0] = std::move(t[1]);
        t[1] = std::move(temp);
    }

    return t;
}

std::vector<Intersection> Cube::Intersect(Ray const& ray) {
    std::vector<Intersection> intersectionPoints;

    Ray transRay = RayToObjectSpace(ray);

    // NOTE : There is a place for optimisation according to the page 176 of the book !!
    std::array<double, 2> xt = CheckAxis(transRay.getOrigin().getX(), transRay.getDirection().getX());
    std::array<double, 2> yt = CheckAxis(transRay.getOrigin().getY(), transRay.getDirection().getY());
    std::array<double, 2> zt = CheckAxis(transRay.getOrigin().getZ(), transRay.getDirection().getZ());

    double tMin = std::max(std::max(xt[0], yt[0]), zt[0]);
    double tMax = std::min(std::min(xt[1], yt[1]), zt[1]);

    if (tMin > tMax) { // There is no intersection
        return intersectionPoints;
    }

    intersectionPoints.push_back(Intersection(*this, tMin));
    intersectionPoints.push_back(Intersection(*this, tMax));
    return intersectionPoints;
}

Vector Cube::GetNormal(Point const& worldPoint, Intersection const& i) const {
    Point localPoint = WorldToObject(worldPoint);
    Vector localNormal = CalculateLocalNormal(localPoint, i);
    Vector worldNormal = NormalToWorld(localNormal);
    return worldNormal;
}

Vector Cube::CalculateLocalNormal(Point const& localPoint, Intersection const& i) const {
    double x = localPoint.getX();
    double y = localPoint.getY();
    double z = localPoint.getZ();
    double maxFace = std::max(
        std::max(
            std::abs(x),
            std::abs(y)),
        std::abs(z));

    if (Utils::FE(maxFace, std::abs(x))) {
        return Vector(x, 0, 0);
    }
    else if (Utils::FE(maxFace, std::abs(y))) {
        return Vector(0, y, 0);
    }
    return Vector(0, 0, z);
}
