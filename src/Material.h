#pragma once
#include "Color.h"

namespace RefractiveIndex {
    constexpr float Vacuum = 1.0;
    constexpr float Air = 1.000293;
    constexpr float Water = 1.333;
    constexpr float Glass = 1.52;
    constexpr float Diamond = 2.417;
}

class Material
{
private:
    Color m_color;
    float m_ambient;
    float m_diffuse;
    float m_specular;
    float m_shininess;
    float m_reflectivity;
    float m_refractiveIndex;
    float m_transparency;
    //Pattern m_pattern = null;

    void afficher(std::ostream& flux) const;

public:
	// Constructors
	Material();
    Material(Color color, float ambient=0.1f, float diffuse=0.9f, float specular = 0.9f, float shininess = 200.0f, float reflectivity = 0.0f, float refractiveIndex = 1.0f, float transparency = 0.0f);//, Pattern pattern);
    Material(Material const& other);
	Material(Material&& other) noexcept;

	// Destructor
	~Material();


    // Accessors
    Color GetColor() const;
    float GetAmbient() const;
    float GetDiffuse() const;
    float GetSpecular() const;
    float GetShininess() const;
    float GetReflectivity() const;
    float GetRefractiveIndex() const;
    float GetTransparency() const;
    //Pattern GetPattern() const;
    void SetColor(Color color);
    void SetAmbient(float ambient);
    void SetDiffuse(float diffuse);
    void SetSpecular(float specular);
    void SetShininess(float shininess);
    void SetReflectivity(float reflectivity);
    void SetRefractiveIndex(float refractiveIndex);
    void SetTransparency(float transparency);
    //void SetPattern(Pattern pattern);

    // Operators
    Material& operator=(Material const& other);
    Material& operator=(Material&& other) noexcept;
    bool operator==(Material const& other) const;
    friend std::ostream& operator<<(std::ostream& flux, Material const& material);
};

