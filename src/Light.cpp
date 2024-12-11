#include "Light.h"
#include "Scene.h"

int Light::m_currentId = 0;

// Constructors
Light::Light() {
    /*if (Scene.current != null) {
        Scene.current.AddLight(this);
    }*/
    m_id = ++m_currentId;
    m_intensity = Color(1, 1, 1);
    m_position = Point(0, 0, 0);
    
    Scene* currentScene = Scene::GetCurrentScene();
    if (currentScene != nullptr) {
        //this.SetParent(Scene::current.root);
        currentScene->AddLight(*this);
    }
}

Light::Light(Point position, Color intensity) {
    /*if (Scene.current != null)
    {
        Scene.current.AddLight(this);
    }*/
    m_id = m_currentId++;
    m_intensity = intensity;
    m_position = position;

    Scene* currentScene = Scene::GetCurrentScene();
    if (currentScene != nullptr) {
        //this.SetParent(Scene::current.root);
        currentScene->AddLight(*this);
    }
}

Light::Light(Light const& other) {
    m_id = ++m_currentId;
    m_intensity = other.m_intensity;
    m_position = other.m_position;

    Scene* currentScene = Scene::GetCurrentScene();
    if (currentScene != nullptr) {
        //this.SetParent(Scene::current.root);
        currentScene->AddLight(*this);
    }
}

Light::Light(Light&& other) noexcept :
    m_id(other.m_id),
    m_intensity(other.m_intensity),
    m_position(other.m_position) {
    // Réinitialise l'objet source pour éviter des doublons
    other.m_id = 0; // Réinitialise l'ID de l'objet source
    other.m_intensity = Color();
    other.m_position = Point();

    Scene* currentScene = Scene::GetCurrentScene();
    if (currentScene != nullptr) {
        //this.SetParent(Scene::current.root);
        currentScene->AddLight(*this);
    }
}


// Destructor
Light::~Light() {
    Scene* currentScene = Scene::GetCurrentScene();
    if (currentScene != nullptr) {
        //this.SetParent(Scene::current.root);
        currentScene->RemoveLight(*this);
    }
}


// Accessors
int Light::GetNbInstances() { return m_currentId; };

int Light::GetId() const { return m_id; }

Color Light::GetIntensity() const { return m_intensity; }

Point Light::GetPosition() const { return m_position; }

void Light::SetIntensity(Color color) { m_intensity = color; }

void Light::SetPosition(Point position) { m_position = position; }


// Operators
Light& Light::operator=(Light const& other) {
    if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
        m_intensity = other.m_intensity;
        m_position = other.m_position;
    }
    return *this;
}

Light& Light::operator=(Light&& other) noexcept {
    if (this != &other) {
        m_intensity = other.m_intensity;
        m_position = other.m_position;
        // Réinitialise l'objet source
        other.m_id = 0;
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


// Member-functions
void Light::afficher(std::ostream& flux) const {
    flux << "Light (id: " << m_id << ", position: " << m_position << ", intensity: " << m_intensity << ")";
}
