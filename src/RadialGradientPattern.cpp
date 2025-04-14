#include "RadialGradientPattern.h"
#include "SolidColorPattern.h"

// Constructors
RadialGradientPattern::RadialGradientPattern() :
	Pattern(),
	m_patternA(std::make_shared<SolidColorPattern>(Color::white)),
	m_patternB(std::make_shared<SolidColorPattern>(Color::black)) {}

RadialGradientPattern::RadialGradientPattern(Pattern const& a, Pattern const& b) :
	Pattern(),
	m_patternA(a.clone()),
	m_patternB(b.clone()) {}

RadialGradientPattern::RadialGradientPattern(RadialGradientPattern const& other) :
	Pattern(other),
	m_patternA(other.m_patternA->clone()),
	m_patternB(other.m_patternB->clone()) {}

RadialGradientPattern::RadialGradientPattern(RadialGradientPattern&& other) noexcept :
	Pattern(std::move(other)),
	m_patternA(std::move(other.m_patternA)),
	m_patternB(std::move(other.m_patternB)) {
	// Reset source object pour éviter des doublons
	other.m_patternA = std::make_shared<SolidColorPattern>(Color::white);
	other.m_patternB = std::make_shared<SolidColorPattern>(Color::black);
}


// Member functions
bool RadialGradientPattern::equals(Pattern const& other) const {
	// Cast sécurisé car operator== vérifie déjà le type
	auto& typedOther = static_cast<const RadialGradientPattern&>(other);
	return Pattern::equals(other) &&
		*m_patternA == *typedOther.m_patternA &&
		*m_patternB == *typedOther.m_patternB;
}

bool RadialGradientPattern::operator==(RadialGradientPattern const& other) const {
	return Pattern::operator==(other) &&
		*m_patternA == *other.m_patternA &&
		*m_patternB == *other.m_patternB;
}

RadialGradientPattern& RadialGradientPattern::operator=(RadialGradientPattern const& other) {
	if (this != &other) {
		Pattern::operator=(other);
		m_patternA = other.m_patternA->clone();
		m_patternB = other.m_patternB->clone();
	}
	return *this;
}

RadialGradientPattern& RadialGradientPattern::operator=(RadialGradientPattern&& other) noexcept {
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

Color RadialGradientPattern::patternAt(Point const& objectPoint) const {
	Point patternPoint = m_matrix.inverted() * objectPoint;

	// Ring pattern.
	double distance = std::sqrt(patternPoint.getX() * patternPoint.getX() + patternPoint.getZ() * patternPoint.getZ());

	// Gradient pattern.
	return m_patternA->patternAt(patternPoint) + (m_patternB->patternAt(patternPoint) - m_patternA->patternAt(patternPoint)) * (distance - std::floor(distance));

	// pour un grandiant en miroir
	//if (std::abs(patternPoint.getX() - std::floor(patternPoint.getX())) < 0.5) {
	//    return m_patternA->patternAt(patternPoint) + (m_patternB->patternAt(patternPoint) - m_patternA->patternAt(patternPoint)) * (2 * distance - std::floor(2 * distance));
	//}
	//else {
	//    return m_patternB->patternAt(patternPoint) + (m_patternA->patternAt(patternPoint) - m_patternB->patternAt(patternPoint)) * (2 * distance - std::floor(2 * distance));
	//}
}

std::shared_ptr<Pattern> RadialGradientPattern::clone() const {
	return std::make_shared<RadialGradientPattern>(*this);
}


// Non-member functions
bool operator!=(RadialGradientPattern const& a, RadialGradientPattern const& b) {
	return !(a == b);
}
