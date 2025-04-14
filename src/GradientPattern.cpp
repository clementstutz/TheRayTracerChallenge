#include "GradientPattern.h"
#include "SolidColorPattern.h"

// Constructors
GradientPattern::GradientPattern() :
	Pattern(),
	m_patternA(std::make_shared<SolidColorPattern>(Color::white)),
	m_patternB(std::make_shared<SolidColorPattern>(Color::black)) {}

GradientPattern::GradientPattern(Pattern const& a, Pattern const& b) :
	Pattern(),
	m_patternA(a.clone()),
	m_patternB(b.clone()) {}

GradientPattern::GradientPattern(GradientPattern const& other) :
	Pattern(other),
	m_patternA(other.m_patternA->clone()),
	m_patternB(other.m_patternB->clone()) {}

GradientPattern::GradientPattern(GradientPattern&& other) noexcept :
	Pattern(std::move(other)),
	m_patternA(std::move(other.m_patternA)),
	m_patternB(std::move(other.m_patternB)) {
	// Reset source object pour éviter des doublons
	other.m_patternA = std::make_shared<SolidColorPattern>(Color::white);
	other.m_patternB = std::make_shared<SolidColorPattern>(Color::black);
}


// Member functions
bool GradientPattern::equals(Pattern const& other) const {
	// Cast sécurisé car operator== vérifie déjà le type
	auto& typedOther = static_cast<const GradientPattern&>(other);
	return Pattern::equals(other) &&
		*m_patternA == *typedOther.m_patternA &&
		*m_patternB == *typedOther.m_patternB;
}

bool GradientPattern::operator==(GradientPattern const& other) const {
	return Pattern::operator==(other) &&
		*m_patternA == *other.m_patternA &&
		*m_patternB == *other.m_patternB;
}

GradientPattern& GradientPattern::operator=(GradientPattern const& other) {
	if (this != &other) {
		Pattern::operator=(other);
		m_patternA = other.m_patternA->clone();
		m_patternB = other.m_patternB->clone();
	}
	return *this;
}

GradientPattern& GradientPattern::operator=(GradientPattern&& other) noexcept {
	if (this != &other) {
		Pattern::operator=(std::move(other));
		m_patternA = std::move(other.m_patternA);
		m_patternB = std::move(other.m_patternB);
		// Reset source object
		other.m_patternA = std::make_shared<SolidColorPattern>(Color::white);
		other.m_patternB = std::make_shared<SolidColorPattern>(Color::black);
	}
	return *this;
}

Color GradientPattern::patternAt(Point const& objectPoint) const {
	Point patternPoint = m_matrix.inverted() * objectPoint;

	return m_patternA->patternAt(patternPoint) + (m_patternB->patternAt(patternPoint) - m_patternA->patternAt(patternPoint)) * (patternPoint.getX() - std::floor(patternPoint.getX()));

	// pour un grandiant en miroir
	//if (std::abs(patternPoint.getX() - std::floor(patternPoint.getX())) < 0.5) {
	//    return m_patternA->patternAt(patternPoint) + (m_patternB->patternAt(patternPoint) - m_patternA->patternAt(patternPoint)) * (2 * patternPoint.getX() - std::floor(2 * patternPoint.getX()));
	//}
	//else {
	//    return m_patternB->patternAt(patternPoint) + (m_patternA->patternAt(patternPoint) - m_patternB->patternAt(patternPoint)) * (2 * patternPoint.getX() - std::floor(2 * patternPoint.getX()));
	//}
}

std::shared_ptr<Pattern> GradientPattern::clone() const {
	return std::make_shared<GradientPattern>(*this);
}


// Non-member functions
bool operator!=(GradientPattern const& a, GradientPattern const& b) {
	return !(a == b);
}
