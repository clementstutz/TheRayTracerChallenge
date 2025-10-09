#include <cmath>
#include <limits>  // for std::numeric_limits

#include "Cylinder.h"
#include "Utils.h"

// Constructors
Cylinder::Cylinder() :
    RayObject(),
    m_minimum(-std::numeric_limits<double>::infinity()),
    m_maximum(std::numeric_limits<double>::infinity()),
    m_isClosed(false) {}

Cylinder::Cylinder(float min, float max, bool isClose) :
    RayObject(),
    m_minimum(min),
    m_maximum(max),
    m_isClosed(isClose) {}

Cylinder::Cylinder(Cylinder const& other) :
    RayObject(other),
    m_minimum(other.m_minimum),
    m_maximum(other.m_maximum),
    m_isClosed(other.m_isClosed) {}

Cylinder::Cylinder(Cylinder&& other) noexcept :
    RayObject(std::move(other)),
    m_minimum(std::move(other.m_minimum)),
    m_maximum(std::move(other.m_maximum)),
    m_isClosed(std::move(other.m_isClosed)) {
    other.m_minimum = -std::numeric_limits<double>::infinity();
    other.m_maximum = std::numeric_limits<double>::infinity();
    other.m_isClosed = false;
}


// Member functions
Cylinder& Cylinder::operator=(Cylinder const& other) {
    if (this != &other) {
        RayObject::operator=(other); // Appelle l'op�rateur d'affectation par copie de la classe m�re
        m_minimum = std::move(other.m_minimum);
        m_maximum = std::move(other.m_maximum);
        m_isClosed = std::move(other.m_isClosed);
    }
    return *this;
}

Cylinder& Cylinder::operator=(Cylinder&& other) noexcept {
    if (this != &other) { // V�rification d'auto-affectation
        RayObject::operator=(std::move(other)); // Appelle l'op�rateur d'affectation par d�placement de la classe m�re
        m_minimum = other.m_minimum;
        m_maximum = other.m_maximum;
        m_isClosed = other.m_isClosed;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& flux, Cylinder const& Cylinder) {
    Cylinder.afficher(flux);
    return flux;
}

void Cylinder::afficher(std::ostream& flux) const {
    flux << "Cylinder (id: " << m_id << ", Position: " << GetPosition() << ", min: " << m_minimum << ", max: " << m_maximum << ", isClosed: " << m_isClosed << ")";
}

std::vector<Intersection> Cylinder::Intersect(Ray const& ray) {
    Ray transRay = RayToObjectSpace(ray);

    std::vector<Intersection> hits = std::vector<Intersection>();

    double a = transRay.getDirection().getX() * transRay.getDirection().getX() +
        transRay.getDirection().getZ() * transRay.getDirection().getZ();

    // ray is parallel to the y axis
    if (Utils::FE(0, a)) {
        IntersectCaps(transRay, hits);
        return hits;
    }

    double b = 2.0 * transRay.getOrigin().getX() * transRay.getDirection().getX() +
        2.0 * transRay.getOrigin().getZ() * transRay.getDirection().getZ();

    double c = transRay.getOrigin().getX() * transRay.getOrigin().getX() +
        transRay.getOrigin().getZ() * transRay.getOrigin().getZ() - 1.0;

    double discriminant = b * b - 4 * a * c;

    //ray does not intersect the cylinder
    if (discriminant < 0)
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

    double y1 = transRay.getOrigin().getY() + t1 * transRay.getDirection().getY();

    if (m_minimum < y1 && y1 < m_maximum) {
        hits.push_back(Intersection(*this, t1));
    }

    IntersectCaps(transRay, hits); // ref hits

    return hits;
}

void Cylinder::IntersectCaps(const Ray& transRay, std::vector<Intersection>& hits) {
    if (m_isClosed && !Utils::FE(0, transRay.getDirection().getY())) {
        double t0 = (m_minimum - transRay.getOrigin().getY()) / transRay.getDirection().getY();
        double t1 = (m_maximum - transRay.getOrigin().getY()) / transRay.getDirection().getY();
        if (t0 > t1) {
            double temp = t0;
            t0 = t1;
            t1 = temp;
        }

        if (CheckCap(transRay, t0)) {
            hits.push_back(Intersection(*this, t0));
        }
        
        if (CheckCap(transRay, t1)) {
            hits.push_back(Intersection(*this, t1));
        }
    }
}

bool Cylinder::CheckCap(const Ray& transRay, const double& t) {
    double x = transRay.getOrigin().getX() + t * transRay.getDirection().getX();
    double z = transRay.getOrigin().getZ() + t * transRay.getDirection().getZ();
    return (x * x + z * z) <= 1.0;
}

Vector Cylinder::GetNormal(Point const& worldPoint, Intersection const& i) const {
    Point localPoint = WorldToObject(worldPoint);
    Vector localNormal = CalculateLocalNormal(localPoint, i);
    Vector worldNormal = NormalToWorld(localNormal);
    return worldNormal;
}

Vector Cylinder::CalculateLocalNormal(Point const& localPoint, Intersection const& i) const {
    double distance = localPoint.getX() * localPoint.getX() + localPoint.getZ() * localPoint.getZ();

    if (distance < 1 && localPoint.getY() >= m_maximum - Utils::GetEpsilon()) {
        return Vector(0, 1, 0);
    }

    else if (distance < 1 && localPoint.getY() <= m_minimum + Utils::GetEpsilon()) {
        return Vector(0, -1, 0);
    }

    else {
        return Vector(localPoint.getX(), 0, localPoint.getZ());
    }
}
