#include <cmath>
#include <limits>  // for std::numeric_limits

#include "Cone.h"
#include "Utils.h"

// Constructors
Cone::Cone() :
    RayObject(),
    m_minimum(-std::numeric_limits<double>::infinity()),
    m_maximum(std::numeric_limits<double>::infinity()),
    m_isClosed(false) {}

Cone::Cone(float min, float max, bool isClose) :
    RayObject(),
    m_minimum(min),
    m_maximum(max),
    m_isClosed(isClose) {}

Cone::Cone(Cone const& other) :
    RayObject(other),
    m_minimum(other.m_minimum),
    m_maximum(other.m_maximum),
    m_isClosed(other.m_isClosed) {}

Cone::Cone(Cone&& other) noexcept :
    RayObject(std::move(other)),
    m_minimum(std::move(other.m_minimum)),
    m_maximum(std::move(other.m_maximum)),
    m_isClosed(std::move(other.m_isClosed)) {
    other.m_minimum = -std::numeric_limits<double>::infinity();
    other.m_maximum = std::numeric_limits<double>::infinity();
    other.m_isClosed = false;
}


// Member functions
Cone& Cone::operator=(Cone const& other) {
    if (this != &other) {
        RayObject::operator=(other); // Appelle l'op�rateur d'affectation par copie de la classe m�re
        m_minimum = std::move(other.m_minimum);
        m_maximum = std::move(other.m_maximum);
        m_isClosed = std::move(other.m_isClosed);
    }
    return *this;
}

Cone& Cone::operator=(Cone&& other) noexcept {
    if (this != &other) { // V�rification d'auto-affectation
        RayObject::operator=(std::move(other)); // Appelle l'op�rateur d'affectation par d�placement de la classe m�re
        m_minimum = other.m_minimum;
        m_maximum = other.m_maximum;
        m_isClosed = other.m_isClosed;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& flux, Cone const& Cone) {
    Cone.afficher(flux);
    return flux;
}

void Cone::afficher(std::ostream& flux) const {
    flux << "Cone (id: " << m_id << ", Position: " << GetPosition() << ", min: " << m_minimum << ", max: " << m_maximum << ", isClosed: " << m_isClosed << ")";
}

std::vector<Intersection> Cone::Intersect(Ray const& ray) {
    Ray transRay = RayToObjectSpace(ray);

    std::vector<Intersection> hits = std::vector<Intersection>();

    double a = transRay.getDirection().getX() * transRay.getDirection().getX() -
        transRay.getDirection().getY() * transRay.getDirection().getY() +
        transRay.getDirection().getZ() * transRay.getDirection().getZ();

    double b = 2.0 * transRay.getOrigin().getX() * transRay.getDirection().getX() -
        2.0 * transRay.getOrigin().getY() * transRay.getDirection().getY() +
        2.0 * transRay.getOrigin().getZ() * transRay.getDirection().getZ();

    double c = transRay.getOrigin().getX() * transRay.getOrigin().getX() -
        transRay.getOrigin().getY() * transRay.getOrigin().getY() +
        transRay.getOrigin().getZ() * transRay.getOrigin().getZ();

    if (Utils::FE(0, a)) {
        if (Utils::FE(0, b)) {
            // All misses
            return hits;
        }

        // b is not zero, have a single point of intersection.
        // Configuration possible seulement si le ray est à l'interieur du cone.
        // TODO: Vérifier si ce cas correspond bien ç une situation avec ray à l'interieur !
        hits.push_back(Intersection(*this, -c / (2 * b)));
    }

    // Both A and B are not zero at this point.
    // Use the cylinder algorithm but with the new A B and C...

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        // TODO: Vérifier a quelle situation correspond ce cas ?
        return hits;

    double t0 = (-b - std::sqrt(discriminant)) / (2 * a);
    double t1 = (-b + std::sqrt(discriminant)) / (2 * a);

    if (t0 > t1) {
        double temp = t0;
        t0 = t1;
        t1 = temp;
    }

    double y0 = transRay.getOrigin().getY() + t0 * transRay.getDirection().getY();

    if (m_minimum < y0 && y0 < m_maximum) {
        hits.push_back(Intersection(*this, t0));
    }

    double y1 = transRay.getOrigin().getY()  + t1 * transRay.getDirection().getY();

    if (m_minimum < y1 && y1 < m_maximum) {
        hits.push_back(Intersection(*this, t1));
    }

    IntersectCaps(transRay, hits); // ref hits

    Intersection::SortIntersections(hits);
    
    return hits;
}

void Cone::IntersectCaps(const Ray& transRay, std::vector<Intersection>& hits) {
    if (m_isClosed && !Utils::FE(0, transRay.getDirection().getY())) {
        double t = (m_minimum - transRay.getOrigin().getY()) / transRay.getDirection().getY();
        if (CheckCap(transRay, t)) {
            hits.push_back(Intersection(*this, t));
        }

        t = (m_maximum - transRay.getOrigin().getY()) / transRay.getDirection().getY();
        if (CheckCap(transRay, t)) {
            hits.push_back(Intersection(*this, t));
        }
    }
}

bool Cone::CheckCap(const Ray& transRay, const double& t) {
    double x = transRay.getOrigin().getX() + t * transRay.getDirection().getX();
    double z = transRay.getOrigin().getZ() + t * transRay.getDirection().getZ();
    return (x * x + z * z) <= std::abs(transRay.getOrigin().getY() + t * transRay.getDirection().getY()); // TODO : Radius of 1 was for a cylinder, this needs to be changed
    // to be the absolute value of the y coordinate, because a cone fans out with distance.
}

Vector Cone::GetNormal(Point const& worldPoint, Intersection const& i) const {
    Point localPoint = WorldToObject(worldPoint);
    Vector localNormal = CalculateLocalNormal(localPoint, i);
    Vector worldNormal = NormalToWorld(localNormal);
    return worldNormal;
}

Vector Cone::CalculateLocalNormal(Point const& localPoint, Intersection const& i) const {
    double distance = localPoint.getX() * localPoint.getX() + localPoint.getZ() * localPoint.getZ();

    if (distance < 1 && localPoint.getY() >= m_maximum - Utils::GetEpsilon()) {
        return Vector(0, 1, 0);
    }

    else if (distance < 1 && localPoint.getY() <= m_minimum + Utils::GetEpsilon()) {
        return Vector(0, -1, 0);
    }

    else {
        double y = std::sqrt(distance);
        if (localPoint.getY() > 0) {
            y = -y;
        }
        return Vector(localPoint.getX(), y, localPoint.getZ());
    }
}
