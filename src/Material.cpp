#include <algorithm> // Pour std::max

#include "Material.h"

// Constructors
Material::Material() :
    m_color(Color::white),
    m_ambient(0.1),            // [0; 1] normalement
    m_diffuse(0.9),            // [0; 1] normalement
    m_specular(0.9),           // [0; 1] normalement
    m_shininess(200.0),        // [10; 200] normalement
    m_reflectivity(0.0),       // [0; 1] normalement
    m_refractiveIndex(1.0),    // RefractiveIndex.Air;
    m_transparency(0.0)        // [0; 1] normalement
    //m_pattern(null)
{}

Material::Material(Color const& color, double ambient, double diffuse, double specular, double shininess, double reflectivity, double refractiveIndex, double transparency) :
    m_color(color),
    m_ambient(ambient),
    m_diffuse(diffuse),
    m_specular(specular),
    m_shininess(shininess),
    m_reflectivity(reflectivity),
    m_refractiveIndex(refractiveIndex),
    m_transparency(transparency)
    //m_pattern(null)
{}

Material::Material(Material const& other) :
    m_color(other.m_color),
    m_ambient(other.m_ambient),
    m_diffuse(other.m_diffuse),
    m_specular(other.m_specular),
    m_shininess(other.m_shininess),
    m_reflectivity(other.m_reflectivity),
    m_refractiveIndex(other.m_refractiveIndex),
    m_transparency(other.m_transparency)
    //m_pattern = other.m_pattern
{}

Material::Material(Material&& other) noexcept :
    m_color(std::move(other.m_color)),
    m_ambient(std::move(other.m_ambient)),
    m_diffuse(std::move(other.m_diffuse)),
    m_specular(std::move(other.m_specular)),
    m_shininess(std::move(other.m_shininess)),
    m_reflectivity(std::move(other.m_reflectivity)),
    m_refractiveIndex(std::move(other.m_refractiveIndex)),
    m_transparency(std::move(other.m_transparency))
    //m_pattern(std::move(other.m_pattern)) 
    {
    // Reset source object pour éviter des doublons
    other.m_color = Color();
    other.m_ambient = 0.0;
    other.m_diffuse = 0.0;
    other.m_specular = 0.0;
    other.m_shininess = 0.0;
    other.m_reflectivity = 0.0;
    other.m_refractiveIndex = 0.0;
    other.m_transparency = 0.0;
    //other.m_pattern = nullptr;
}


// Accessors
Color Material::GetColor() const {return m_color;}
double Material::GetAmbient() const {return m_ambient;}
double Material::GetDiffuse() const {return m_diffuse;}
double Material::GetSpecular() const {return m_specular;}
double Material::GetShininess() const {return m_shininess;}
double Material::GetReflectivity() const {return m_reflectivity;}
double Material::GetRefractiveIndex() const {return m_refractiveIndex;}
double Material::GetTransparency() const {return m_transparency;}
//Pattern Material::GetPattern() const {return m_pattern;}

void Material::SetColor(Color const& color) {m_color = color;}

void Material::SetAmbient(double ambient) {
    if (ambient < 0.0) { m_ambient = 0.0; }
    else if (ambient > 1.0) { m_ambient = 1.0; }
    else { m_ambient = ambient; }
}

void Material::SetDiffuse(double diffuse) {
    if (diffuse < 0.0) { m_diffuse = 0.0; }
    else if (diffuse > 1.0) { m_diffuse = 1.0; }
    else { m_diffuse = diffuse; }
}

void Material::SetSpecular(double specular) {
    if (specular < 0.0) { m_specular = 0.0; }
    else if (specular > 1.0) { m_specular = 1.0; }
    else { m_specular = specular; }
}

void Material::SetShininess(double shininess) {
    if (shininess < 10.0) {m_shininess = 10.0;}
    else if (shininess > 200.0) {m_shininess = 200.0;}
    else {m_shininess = shininess;}
}

void Material::SetReflectivity(double reflectivity) {
    if (reflectivity < 0.0) { m_reflectivity = 0.0; }
    else if (reflectivity > 1.0) { m_reflectivity = 1.0; }
    else { m_reflectivity = reflectivity; }
}

void Material::SetRefractiveIndex(double refractiveIndex) {m_specular = refractiveIndex;}

void Material::SetTransparency(double transparency) {
    if (transparency < 0.0) { m_transparency = 0.0; }
    else if (transparency > 1.0) { m_transparency = 1.0; }
    else { m_transparency = transparency; }
}


// Member functions
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
        // Reset source object
        other.m_color = Color();
        other.m_ambient = 0.0;
        other.m_diffuse = 0.0;
        other.m_specular = 0.0;
        other.m_shininess = 0.0;
        other.m_reflectivity = 0.0;
        other.m_refractiveIndex = 0.0;
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