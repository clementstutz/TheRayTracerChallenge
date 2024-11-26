#include "Canvas.h"

// Constructeurs
Canvas::Canvas(int width, int height, Color color) :
    m_width(width),
    m_height(height),
    m_canvas(height, std::vector<Color>(width, color)) {}

Canvas::Canvas(Canvas const& other) :
    m_width(other.getWidth()),
    m_height(other.getHeight()),
    m_canvas(other.getCanvas()) {}

Canvas& Canvas::operator=(Canvas const& other) {
    if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
        m_width = other.getWidth();
        m_height = other.getHeight();
        m_canvas = other.getCanvas();
    }
    return *this;
}

// Destructeur
Canvas::~Canvas() {}

// Accesseurs
int Canvas::getWidth() const {
	return m_width;
}

int Canvas::getHeight() const {
	return m_height;
}

std::vector<std::vector<Color>> Canvas::getCanvas() const {
    return m_canvas;
}

void Canvas::setPixel(int x, int y, Color color) {
    if (y >= 0 && y < m_height && x >= 0 && x < m_width) {
        m_canvas[y][x] = color;
    }
}

Color Canvas::getPixel(int x, int y) const {
    if (y >= 0 && y < m_height && x >= 0 && x < m_width) {
        return m_canvas[y][x]; // Retourne une copie de l'élément
    }
    return Color::black;
}

// Fonctions membres
void Canvas::fillCanvas(Color color) {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            m_canvas[y][x] = color;
        }
    }
}

void Canvas::afficher(std::ostream& flux) const {
    flux << "Height: " << m_height << ", Width: " << m_width << " (" << m_height * m_width << "px)";
}

std::ostream& operator<<(std::ostream& flux, Canvas const& canvas) {
    canvas.afficher(flux);
    return flux;
}

