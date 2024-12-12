#include "Light.h"
#include "Scene.h"

int Light::m_currentId = 0;

// Constructors
Light::Light() :
    m_id(++m_currentId),
    m_intensity(Color(1, 1, 1)),
    m_position(Point(0, 0, 0)) {
    if (Scene::GetCurrentScene() != nullptr) {
        Scene::GetCurrentScene()->AddLight(*this);
    }
}

Light::Light(Point position, Color intensity) :
    m_id(++m_currentId),
    m_intensity(intensity),
    m_position(position) {
    if (Scene::GetCurrentScene() != nullptr) {
        Scene::GetCurrentScene()->AddLight(*this);
    }
}

Light::Light(Light const& other) :
    m_id(++m_currentId),
    m_intensity(other.m_intensity),
    m_position(other.m_position) {
    if (Scene::GetCurrentScene() != nullptr) {
        Scene::GetCurrentScene()->AddLight(*this);
    }
}

Light::Light(Light&& other) noexcept :
    m_id(std::move(other.m_id)),
    m_intensity(std::move(other.m_intensity)),
    m_position(std::move(other.m_position)) {
    // Reset source object pour éviter des doublons
    other.m_id = 0;
    other.m_intensity = Color();
    other.m_position = Point();
    if (Scene::GetCurrentScene() != nullptr) {
        Scene::GetCurrentScene()->AddLight(*this);
    }
}


// Destructor
Light::~Light() {
    if (Scene::GetCurrentScene() != nullptr) {
        Scene::GetCurrentScene()->RemoveLight(*this);
    }
}


// Accessors
int Light::GetNbInstances() { return m_currentId; };
int Light::GetId() const { return m_id; }
Color Light::GetIntensity() const { return m_intensity; }
Point Light::GetPosition() const { return m_position; }
void Light::SetIntensity(Color const& color) { m_intensity = color; }
void Light::SetPosition(Point const& position) { m_position = position; }


// Member functions
Light& Light::operator=(Light const& other) {
    if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
        m_intensity = other.m_intensity;
        m_position = other.m_position;
    }
    return *this;
}

Light& Light::operator=(Light&& other) noexcept {
    if (this != &other) {
        m_intensity = std::move(other.m_intensity);
        m_position = std::move(other.m_position);
        // Reset source object
        other.m_intensity = Color();
        other.m_position = Point();
    }
    return *this;
}

bool Light::operator==(Light const& other) const {
    return (m_id == other.m_id) &&
           (m_intensity == other.m_intensity) &&
           (m_position == other.m_position);
}

std::ostream& operator<<(std::ostream& flux, Light const& light) {
    light.afficher(flux);
    return flux;
}

void Light::afficher(std::ostream& flux) const {
    flux << "Light (id: " << m_id << ", position: " << m_position << ", intensity: " << m_intensity << ")";
}
