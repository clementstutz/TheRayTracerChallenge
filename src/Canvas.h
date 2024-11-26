#pragma once
#include "Color.h"
#include <vector>

class Canvas
{
private:
	int m_width, m_height;
	std::vector<std::vector<Color>> m_canvas;	//peut être utiliser une map ? (cf. https://openclassrooms.com/fr/courses/7137751-programmez-en-oriente-objet-avec-c/7532251-utilisez-les-conteneurs)

	void afficher(std::ostream& flux) const;

public:
	// Constructeurs
	Canvas(int width, int height, Color color=Color::black);
	Canvas(Canvas const& other);
	Canvas& operator=(Canvas const& other);

	// Destructeur
	~Canvas();

	// Accesseurs
	int getWidth() const;
	int getHeight() const;
	std::vector<std::vector<Color>> getCanvas() const;
	void setPixel(int x, int y, Color color);
	Color getPixel(int x, int y) const;

	void fillCanvas(Color color);

	//opérateurs
	friend std::ostream& operator<<(std::ostream& flux, Canvas const& canvas);
};

