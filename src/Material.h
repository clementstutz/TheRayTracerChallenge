#pragma once
#include "Color.h"
#include "Pattern.h"


namespace RefractiveIndex {
    constexpr double Vacuum = 1.0;
    constexpr double Air = 1.000293;
    constexpr double Water = 1.333;
    constexpr double Glass = 1.52;
    constexpr double Diamond = 2.417;
}

class Material
{
private:
    Color m_color;
    double m_ambient;
    double m_diffuse;
    double m_specular;
    double m_shininess;
    double m_reflectivity;
    double m_refractiveIndex;
    double m_transparency;
    std::shared_ptr<Pattern> m_pattern;

    void afficher(std::ostream& flux) const;

public:
	// Constructors
	Material();
    Material(Color const& color, double ambient=0.1, double diffuse=0.9, double specular = 0.9, double shininess = 200.0, double reflectivity = 0.0, double refractiveIndex = 1.0, double transparency = 0.0, std::shared_ptr<Pattern> pattern=nullptr);
    Material(Material const& other);
	Material(Material&& other) noexcept;


	// Destructor
	~Material() = default;


    // Accessors
    Color GetColor() const;
    double GetAmbient() const;
    double GetDiffuse() const;
    double GetSpecular() const;
    double GetShininess() const;
    double GetReflectivity() const;
    double GetRefractiveIndex() const;
    double GetTransparency() const;
    std::shared_ptr<Pattern> GetPattern() const;
    void SetColor(Color const& color);
    void SetAmbient(double ambient);
    void SetDiffuse(double diffuse);
    void SetSpecular(double specular);
    void SetShininess(double shininess);
    void SetReflectivity(double reflectivity);
    void SetRefractiveIndex(double refractiveIndex);
    void SetTransparency(double transparency);
    void SetPattern(Pattern const& pattern);

    // Member functions
    Material& operator=(Material const& other);
    Material& operator=(Material&& other) noexcept;
    bool operator==(Material const& other) const;
    friend std::ostream& operator<<(std::ostream& flux, Material const& material);
};

// Non-member functions
bool operator!=(Material const& a, Material const& b);