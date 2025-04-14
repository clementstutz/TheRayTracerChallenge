#include "Pattern.h"

// Constructors
Pattern::Pattern() :
	m_matrix(Mat4()) {}

Pattern::Pattern(Pattern const& other) :
	m_matrix(other.m_matrix) {
}

Pattern::Pattern(Pattern&& other) noexcept :
	m_matrix(std::move(other.m_matrix)) {
	// Reset source object pour éviter des doublons
	other.m_matrix = Mat4();
}


// Accessors
Mat4 Pattern::GetMatrix() const { return m_matrix; }

void Pattern::SetMatrix(Mat4 const& mat) { m_matrix = mat; }


// Member functions
bool Pattern::equals(Pattern const& other) const {
	return m_matrix == other.m_matrix;
}

bool Pattern::operator==(Pattern const& other) const {
	// Vérification de type avec typeid
	if (typeid(*this) != typeid(other)) return false;
	return equals(other);
}

Pattern& Pattern::operator=(Pattern const& other) {
	if (this != &other) {
		m_matrix = other.m_matrix;
	}
	return *this;
}

Pattern& Pattern::operator=(Pattern&& other) noexcept {
	if (this != &other) {
		m_matrix = std::move(other.m_matrix);
		// Reset source object
		other.m_matrix = Mat4();
	}
	return *this;
}

Color Pattern::PatternAtObject(Point const& objectPoint) const {
	// à déplacer dans patternAt pour que les transformations de chaque sous-pattern soient aussi prises en compte.
	// Le point est déjà converti de l'espace global vers l'espace local de l'objet.
	 /*Point patternPoint = m_matrix.inverted() * objectPoint;*/
	// Appelle le PatternAt virtuel
    return patternAt(objectPoint);
}


// Non-member functions
bool operator!=(Pattern const& a, Pattern const& b) {
	return !(a == b);
}