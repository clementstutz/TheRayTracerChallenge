#include "Canvas.h"

// Constructors
Canvas::Canvas(int const& width, int const& height, Color const& color) :
    m_width(width),
    m_height(height),
    m_canvas(height, std::vector<Color>(width, color)) {}

Canvas::Canvas(Canvas const& other) :
    m_width(other.m_width),
    m_height(other.m_height),
    m_canvas(other.m_canvas) {}


// Accesseurs
int Canvas::getWidth() const { return m_width; }

int Canvas::getHeight() const { return m_height; }

Color Canvas::getPixel(int x, int y) const {
    if (y >= 0 && y < m_height && x >= 0 && x < m_width) {
        return m_canvas[y][x]; // Retourne une copie de l'élément
    }
    return Color::black;
}

void Canvas::setPixel(int x, int y, Color const &color) {
    if (y >= 0 && y < m_height && x >= 0 && x < m_width) {
        m_canvas[y][x] = color;
    }
}


// Member functions
Canvas& Canvas::operator=(Canvas const& other) {
    if (this != &other) {
        m_width = other.m_width;
        m_height = other.m_height;
        m_canvas = other.m_canvas;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& flux, Canvas const& canvas) {
    canvas.afficher(flux);
    return flux;
}

void Canvas::afficher(std::ostream& flux) const {
    flux << "Canvas : (Height: " << m_height << ", Width: " << m_width << ", " << m_height * m_width << "px)";
}

void Canvas::fillCanvas(Color const& color) {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            m_canvas[y][x] = color;
        }
    }
}

void Canvas::drawCircle(int cx, int cy, int radius, Color const& color) {
    // Creat a block to iterate over.
    int xStart = cx - radius;
    int xEnd = cx + radius;
    int yStart = cy - radius;
    int yEnd = cy + radius;

    // Iterate over every element of the block and test if it is within the radius.
    for (int y = yStart; y <= yEnd; y++) {
        for (int x = xStart; x <= xEnd; x++) {
            // Calculate distance to center, use square as it is faster that root.
            int squareRadius = radius * radius;
            double distance = (x - cx) * (x - cx) + (y - cy) * (y - cy);
            if (static_cast<int>(distance) < squareRadius) {
                // Draw to location, which tests to see if it is even possible.
                setPixel(x, y, color);
            }
        }
    }
}
