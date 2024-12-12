#include "Computations.h"
#include "Utils.h"
#include "Material.h"
#include "RayObject.h"

// Constructors
Computations::Computations() :
    m_t(0.0f),
    m_rayObjectPtr(nullptr),
    m_point(Point()),
    m_eye(Vector()),
    m_normal(Vector()),
    m_inside(false),
    m_overPoint(Point()),
    m_underPoint(Point()),
    m_reflectVector(Vector()),
    m_n1(RefractiveIndex::Vacuum),
    m_n2(RefractiveIndex::Vacuum) {}


// Accessors
const float Computations::GetLength() const { return m_t; }

const RayObject* Computations::GetRayObjectPtr() const { return m_rayObjectPtr; }

const RayObject& Computations::GetRayObject() const {
    if (!m_rayObjectPtr) {
        throw std::runtime_error("m_rayObject is null. Invalid access.");
    }
    return *m_rayObjectPtr;
}

const Point Computations::GetPoint() const { return m_point; }

const Vector Computations::GetEye() const { return m_eye; }

const Vector Computations::GetNormal() const { return m_normal; }

const bool Computations::GetInside() const { return m_inside; }

const Point Computations::GetOverPoint() const { return m_overPoint; }

const Point Computations::GetUnderPoint() const { return m_underPoint; }

const Vector Computations::GetReflectVector() const { return m_reflectVector; }

const float Computations::GetN1() const { return m_n1; }

const float Computations::GetN2() const { return m_n2; }


// Member functions
Computations Computations::Prepare(Intersection const& hit, Ray const& ray, std::vector<Intersection> const* xs) {
    Computations c;

    if (hit.IsEmpty()) { return c; }

    c.m_t = hit.getLength();
    c.m_rayObjectPtr = hit.getObjPtr();
    c.m_point = ray.position(hit.getLength());
    c.m_eye = -ray.getDirection().Normalized();
    c.m_normal = hit.getObj().GetNormal(c.m_point, hit).Normalized();
    c.m_inside = false;
    if (c.m_normal.Dot(c.m_eye) < 0) {
        c.m_inside = true;
        c.m_normal = -c.m_normal; }
    c.m_overPoint = c.m_point + c.m_normal * Utils::GetEpsilon();
    c.m_underPoint = c.m_point - c.m_normal * Utils::GetEpsilon();
    c.m_reflectVector = Vector::Reflect(ray.getDirection(), c.m_normal);
    c.m_n1 = RefractiveIndex::Vacuum;
    c.m_n2 = RefractiveIndex::Vacuum;

    // Transparency Intersections algorithm
    if (xs != nullptr) {
        std::vector<const RayObject*> container;
        for (Intersection const& intersection : *xs) {
            // Déterminer m_n1
            if (&intersection == &hit) {
                c.m_n1 = container.empty() ? RefractiveIndex::Vacuum : container.back()->GetMaterial().GetRefractiveIndex();
            }

            // Mettre à jour container
            const RayObject* obj = intersection.getObjPtr();
            auto it = std::find(container.begin(), container.end(), obj);
            if (it != container.end()) {
                container.erase(it);
            }
            else {
                container.push_back(obj);
            }

            // Déterminer m_n2
            if (&intersection == &hit) {
                c.m_n2 = container.empty() ? RefractiveIndex::Vacuum : container.back()->GetMaterial().GetRefractiveIndex();
                break;
            }
        }
    }
    return c;
}
