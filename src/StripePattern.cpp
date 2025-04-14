#include "StripePattern.h"
#include "SolidColorPattern.h"
#include "Utils.h"

// Constructors
StripePattern::StripePattern() :
	Pattern(),
	m_patternA(std::make_shared<SolidColorPattern>(Color::white)),
	m_patternB(std::make_shared<SolidColorPattern>(Color::black)) {}

StripePattern::StripePattern(Pattern const& a, Pattern const& b) :
	Pattern(),
	m_patternA(a.clone()),
	m_patternB(b.clone()) {}

StripePattern::StripePattern(StripePattern const& other) :
	Pattern(other),
	m_patternA(other.m_patternA->clone()),
	m_patternB(other.m_patternB->clone()) {}

StripePattern::StripePattern(StripePattern&& other) noexcept :
	Pattern(std::move(other)),
	m_patternA(std::move(other.m_patternA)),
	m_patternB(std::move(other.m_patternB)) {
	// Reset source object pour éviter des doublons
	other.m_patternA = std::make_shared<SolidColorPattern>(Color::white);
	other.m_patternB = std::make_shared<SolidColorPattern>(Color::black);
}


// Member functions
bool StripePattern::equals(Pattern const& other) const {
	// Cast sécurisé car operator== vérifie déjà le type
	auto& typedOther = static_cast<const StripePattern&>(other);
	return Pattern::equals(other) &&
		*m_patternA == *typedOther.m_patternA &&
		*m_patternB == *typedOther.m_patternB;
}

bool StripePattern::operator==(StripePattern const& other) const {
	return Pattern::operator==(other) &&
		*m_patternA == *other.m_patternA &&
		*m_patternB == *other.m_patternB;
}

StripePattern& StripePattern::operator=(StripePattern const& other) {
	if (this != &other) {
		Pattern::operator=(other);
		m_patternA = other.m_patternA->clone();
		m_patternB = other.m_patternB->clone();
	}
	return *this;
}

StripePattern& StripePattern::operator=(StripePattern&& other) noexcept {
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

Color StripePattern::patternAt(Point const& objectPoint) const {
	Point patternPoint = m_matrix.inverted() * objectPoint;

	if (static_cast<int>(std::floor(patternPoint.getX())) % 2 == 0.0) {
		return m_patternA->patternAt(patternPoint);
	}
	return m_patternB->patternAt(patternPoint);
}

std::shared_ptr<Pattern> StripePattern::clone() const {
	return std::make_shared<StripePattern>(*this);
}


// Non-member functions
bool operator!=(StripePattern const& a, StripePattern const& b) {
	return !(a == b);
}