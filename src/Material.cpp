#include <algorithm> // Pour std::max
#include "Material.h"

// Constructors
Material::Material() :
    m_color(Color::white),
    m_ambient(0.1),            // [0; 1] normalement
    m_diffuse(0.9),            // [0; 1] normalement
    m_specular(0.9),           // [0; 1] normalement
    m_shininess(200),          // [10; 200] normalement
    m_reflectivity(0.0),       // [0; 1] normalement
    m_refractiveIndex(1.0f),   // RefractiveIndex.Air;
    m_transparency(0.0)       // [0; 1] normalement
    //m_pattern(null),
{}

Material::Material(Color color, float ambient, float diffuse, float specular, float shininess, float reflectivity, float refractiveIndex, float transparency) :
    m_color(color),
    m_ambient(ambient),            // [0; 1] normalement
    m_diffuse(diffuse),            // [0; 1] normalement
    m_specular(specular),           // [0; 1] normalement
    m_shininess(shininess),          // [10; 200] normalement
    m_reflectivity(reflectivity),       // [0; 1] normalement
    m_refractiveIndex(refractiveIndex),   // RefractiveIndex.Air;
    m_transparency(transparency)       // [0; 1] normalement
    //m_pattern(null),
{}

Material::Material(Material const& other) {
    m_color = other.m_color;
    m_ambient = other.m_ambient;
    m_diffuse = other.m_diffuse;
    m_specular = other.m_specular;
    m_shininess = other.m_shininess;
    m_reflectivity = other.m_reflectivity;
    m_refractiveIndex = other.m_refractiveIndex;
    m_transparency = other.m_transparency;
    //m_pattern = other.m_pattern;
}

Material::Material(Material&& other) noexcept :
    m_color(other.m_color),
    m_ambient(other.m_ambient),
    m_diffuse(other.m_diffuse),
    m_specular(other.m_specular),
    m_shininess(other.m_shininess),
    m_reflectivity(other.m_reflectivity),
    m_refractiveIndex(other.m_refractiveIndex),
    m_transparency(other.m_transparency)
    //m_pattern(other.m_pattern) 
    {
    // Réinitialise l'objet source pour éviter des doublons
    other.m_color = Color();
    other.m_ambient = 0.1;
    other.m_diffuse = 0.9;
    other.m_specular = 0.9;
    other.m_shininess = 200;
    other.m_reflectivity = 0.0;
    other.m_refractiveIndex = 1.0;
    other.m_transparency = 0.0;
    //other.m_pattern = null;
}


// Destructors
Material::~Material() {}


// Accessors
Color Material::GetColor() const {return m_color;}
float Material::GetAmbient() const {return m_ambient;}
float Material::GetDiffuse() const {return m_diffuse;}
float Material::GetSpecular() const {return m_specular;}
float Material::GetShininess() const {return m_shininess;}
float Material::GetReflectivity() const {return m_reflectivity;}
float Material::GetRefractiveIndex() const {return m_refractiveIndex;}
float Material::GetTransparency() const {return m_transparency;}
//Pattern Material::GetPattern() const {return m_pattern;}


void Material::SetColor(Color color) {m_color = color;}

void Material::SetAmbient(float ambient) {m_ambient = std::max(ambient, 0.0f);}

void Material::SetDiffuse(float diffuse) {m_diffuse = std::max(diffuse, 0.0f);}

void Material::SetSpecular(float specular) {m_specular = std::max(specular, 0.0f);}

void Material::SetShininess(float shininess) {
    if (shininess < 10.0f) {m_shininess = 10.0f;}
    else if (shininess > 200.0f) {m_shininess = 200.0f;}
    else {m_shininess = shininess;}
}

void Material::SetReflectivity(float reflectivity) {
    if (reflectivity < 0.0f) { m_reflectivity = 0.0f; }
    else if (reflectivity > 1.0f) { m_reflectivity = 1.0f; }
    else { m_reflectivity = reflectivity; }
}

void Material::SetRefractiveIndex(float refractiveIndex) {m_specular = refractiveIndex;}

void Material::SetTransparency(float transparency) {
    if (transparency < 0.0f) { m_transparency = 0.0f; }
    else if (transparency > 1.0f) { m_transparency = 1.0f; }
    else { m_transparency = transparency; }
}


// Operators
Material& Material::operator=(Material const& other) {
    if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
        m_color = other.m_color;
        m_ambient = other.m_ambient;
        m_diffuse = other.m_diffuse;
        m_specular = other.m_specular;
        m_shininess = other.m_shininess;
        m_reflectivity = other.m_reflectivity;
        m_refractiveIndex = other.m_refractiveIndex;
        m_transparency = other.m_transparency;
        //m_pattern = other.m_pattern;
    }
    return *this;
}

Material& Material::operator=(Material&& other) noexcept {
    if (this != &other) {
        m_color = other.m_color;
        m_ambient = other.m_ambient;
        m_diffuse = other.m_diffuse;
        m_specular = other.m_specular;
        m_shininess = other.m_shininess;
        m_reflectivity = other.m_reflectivity;
        m_refractiveIndex = other.m_refractiveIndex;
        m_transparency = other.m_transparency;
        //m_pattern = other.m_pattern;
        // Réinitialise l'objet source
        other.m_color = Color();
        other.m_ambient = 0.1;
        other.m_diffuse = 0.9;
        other.m_specular = 0.9;
        other.m_shininess = 200;
        other.m_reflectivity = 0.0;
        other.m_refractiveIndex = 1.0;
        other.m_transparency = 0.0;
        //other.m_pattern = null;
    }
    return *this;
}

bool Material::operator==(Material const& other) const {
    return (m_color == other.m_color) &&
           (m_ambient == other.m_ambient) &&
           (m_diffuse == other.m_diffuse) &&
           (m_specular == other.m_specular) &&
           (m_shininess == other.m_shininess) &&
           (m_reflectivity == other.m_reflectivity) &&
           (m_refractiveIndex == other.m_refractiveIndex) &&
           (m_transparency == other.m_transparency);//&&
           //(m_pattern == other.m_pattern);
}

std::ostream& operator<<(std::ostream& flux, Material const& material) {
    material.afficher(flux);
    return flux;
}


// Member-functions
void Material::afficher(std::ostream& flux) const {
    flux << "Material -> Color : " << m_color <<
        ", Ambient: " << m_ambient <<
        ", Diffuse: " << m_diffuse <<
        ", Specular: " << m_specular <<
        ", Shinniness: " << m_shininess <<
        ", Reflectivity: " << m_reflectivity <<
        ", Refractive Index: " << m_refractiveIndex <<
        ", Transparency: " << m_transparency <<
        ")";
}