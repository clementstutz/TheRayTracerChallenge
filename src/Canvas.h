#pragma once
#include <vector>
#include "Color.h"

class Canvas
{
private:
	int m_width, m_height;
	std::vector<std::vector<Color>> m_canvas;	//peut être utiliser une map ? (cf. https://openclassrooms.com/fr/courses/7137751-programmez-en-oriente-objet-avec-c/7532251-utilisez-les-conteneurs)

	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Canvas(int const& width, int const& height, Color const& color=Color::black);
	Canvas(Canvas const& other);
	

	// Destructor
	~Canvas() = default;


	// Accesseurs
	int getWidth() const;
	int getHeight() const;
	Color getPixel(int x, int y) const;
	void setPixel(int x, int y, Color const &color);
	

	// Member functions
	Canvas& operator=(Canvas const& other);
	friend std::ostream& operator<<(std::ostream& flux, Canvas const& canvas);
	void fillCanvas(Color const& color);
	void drawCircle(int cx, int cy, int radius, Color const& color);
};

