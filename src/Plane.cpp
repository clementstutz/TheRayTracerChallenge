#include "Plane.h"
#include "Utils.h"

// Constructors
Plane::Plane() :
    RayObject(),
    m_normal(Vector(0, 1, 0)) {}

Plane::Plane(Plane const& other) :
    RayObject(other),
    m_normal(other.m_normal) {}

Plane::Plane(Plane&& other) noexcept :
    RayObject(std::move(other)),
    m_normal(std::move(other.m_normal)) {
    // Reset source object pour éviter des doublons
    other.m_normal = Vector(0, 1, 0);
}


// Member functions
bool Plane::operator==(Plane const& other) const {
    return (RayObject::operator==(other)) && 
        (m_normal == other.m_normal);
}

Plane& Plane::operator=(Plane const& other) {
    if (this != &other) {
        RayObject::operator=(other); // Appelle l'opérateur d'affectation par copie de la classe mère
        m_normal = other.m_normal;
    }
    return *this;
}

Plane& Plane::operator=(Plane&& other) noexcept {
    if (this != &other) {
        RayObject::operator=(std::move(other)); // Appelle l'opérateur d'affectation par déplacement de la classe mère
        m_normal = std::move(other.m_normal);
        other.m_normal = Vector(0, 1, 0);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& flux, Plane const& plane) {
    plane.afficher(flux);
    return flux;
}

void Plane::afficher(std::ostream& flux) const {
    flux << "Plane (id: " << m_id << ", Normal: " << m_normal << ", Position: " << GetPosition() << ")";
}

std::vector<Intersection> Plane::Intersect(Ray const& ray) {
    std::vector<Intersection> intersectionPoints;

    Ray localRay = RayToObjectSpace(ray);

    if (std::abs(localRay.getDirection().getY()) < Utils::GetEpsilon()) {
        return intersectionPoints;
    }

    // NOTE: pour optimiser encore on pourrait regarder le signe de t1 et ne renvoyer que les valeur positives
    intersectionPoints.push_back(Intersection(*this, -localRay.getOrigin().getY() / localRay.getDirection().getY()));

    return intersectionPoints;
}

Vector Plane::GetNormal(Point const& worldPoint, Intersection const& i) const {
    Point localPoint = WorldToObject(worldPoint);
    Vector localNormal = CalculateLocalNormal(localPoint, i);
    Vector worldNormal = NormalToWorld(localNormal);
    return worldNormal;
}

Vector Plane::CalculateLocalNormal(Point const& localPoint, Intersection const& i) const {
    //Vector normal = this.GetMatrix() * (-this.normal);
            //return this.GetMatrix() * normal;

            // là ça a l'air de marché pusque nous somme deja dans le local space,
            // il n'y a donc pas besoin de faire GetMatrix() * normal
            // de plus le signe de la normal ne semble pas impacter le resultat
            // (c-a-d si on voit le plan par dessus ou par dessous).
    return m_normal;

    /*if (this.GetMatrix() * new Vector(0, 1, 0) <0)
    {
        async = 1;
    }
    if (localPoint.y > 0)   //le rayon arrive par dessus
    {
        Console.WriteLine("localNormal >0 = " + this.GetMatrix() * new Vector(0, 1, 0));
        return this.GetMatrix() * new Vector(0, 1, 0);
    }
    else if (localPoint.y < 0)  //le rayon arrive par dessous
    {
        Console.WriteLine("localNormal <0 = " + this.GetMatrix() * new Vector(0, -1, 0));
        return this.GetMatrix() * new Vector(0, -1, 0);
    }
    else    // WARNING : cas litigieux, il faut regardr l'origine du rayon! A regler plus tard
    {
        Console.WriteLine("localNormal =0 = " + this.GetMatrix() * new Vector(12, 12, 12));
        return this.GetMatrix() * new Vector(12, 12, 12);
    }*/
}