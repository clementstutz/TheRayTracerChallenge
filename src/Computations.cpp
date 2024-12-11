#include "Computations.h"
#include "Utils.h"
#include "Material.h"
#include "RayObject.h"

// Constructors
Computations::Computations() :
    m_rayObject(nullptr),
    m_t(0.0f),
    m_point(Point()),
    m_eye(Vector()),
    m_normal(Vector()),
    m_inside(false),
    m_n1(RefractiveIndex::Vacuum),
    m_n2(RefractiveIndex::Vacuum)
{}

Computations::Computations(RayObject& rayObject, float& t, Point& point, Vector& eye, Vector& normal, bool inside) {
    m_rayObject = &rayObject;
    m_t = t;
    m_point = point;
    m_eye = eye;
    m_normal = normal;
    m_inside = inside;
    m_n1 = RefractiveIndex::Vacuum;
    m_n2 = RefractiveIndex::Vacuum;
}

// Destructor
Computations::~Computations() {}


// Accessors
float Computations::GetLength() const {return m_t;}

const RayObject* Computations::GetRayObjectPtr() const { return m_rayObject; }

const RayObject& Computations::GetRayObject() const {
    if (!m_rayObject) {
        throw std::runtime_error("m_rayObject is null. Invalid access.");
    }
    return *m_rayObject; // Déréférencement du pointeur
}

Point Computations::GetPoint() const { return m_point; }

Vector Computations::GetEye() const { return m_eye; }

Vector Computations::GetNormal() const { return m_normal; }

bool Computations::GetInside() const { return m_inside; }

Point Computations::GetOverPoint() const { return m_overPoint; }

Point Computations::GetUnderPoint() const { return m_underPoint; }

Vector Computations::GetReflectVector() const { return m_reflectVector; }

float Computations::GetN1() const { return m_n1; }

float Computations::GetN2() const { return m_n2; }


// Member-functions
Computations Computations::Prepare(Intersection const& i, Ray const& ray, std::vector<Intersection> const* xs) {
    Computations c;
    c.m_rayObject = i.getObjPtr();
    c.m_t = i.getLength();
    c.m_point = ray.position(i.getLength());
    c.m_eye = -ray.getDirection().Normalized();
    c.m_normal = i.getObj().GetNormal(c.m_point, i).Normalized();
    c.m_n1 = RefractiveIndex::Vacuum;
    c.m_n2 = RefractiveIndex::Vacuum;

    if (c.m_normal.Dot(c.m_eye) < 0) {
        c.m_inside = true;
        c.m_normal = -c.m_normal;
    }
    else {
        c.m_inside = false;
    }

    // Transparency Intersections algorithm
    if (xs != nullptr) {
        std::vector<const RayObject*> container;

        for (Intersection const& intersection : *xs) {
            // Déterminer m_n1
            if (&intersection == &i) {
                c.m_n1 = container.empty() ? RefractiveIndex::Vacuum : container.back()->GetMaterial().GetRefractiveIndex();
            }

            // Mettre à jour containers
            const RayObject* obj = intersection.getObjPtr();
            auto it = std::find(container.begin(), container.end(), obj);
            if (it != container.end()) {
                container.erase(it);
            }
            else {
                container.push_back(obj);
            }

            // Déterminer m_n2
            if (&intersection == &i) {
                c.m_n2 = container.empty() ? RefractiveIndex::Vacuum : container.back()->GetMaterial().GetRefractiveIndex();
                break;
            }
        }
    }
    

    c.m_reflectVector = Vector::Reflect(ray.getDirection(), c.m_normal);
    c.m_overPoint = c.m_point + c.m_normal * Utils::GetEpsilon();
    c.m_underPoint = c.m_point - c.m_normal * Utils::GetEpsilon();
    return c;
}
