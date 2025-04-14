#include "RingPattern.h"
#include "SolidColorPattern.h"

// Constructors
RingPattern::RingPattern() :
	Pattern(),
	m_patternA(std::make_shared<SolidColorPattern>(Color::white)),
	m_patternB(std::make_shared<SolidColorPattern>(Color::black)) {}

RingPattern::RingPattern(Pattern const& a, Pattern const& b) :
	Pattern(),
	m_patternA(a.clone()),
	m_patternB(b.clone()) {}

RingPattern::RingPattern(RingPattern const& other) :
	Pattern(other),
	m_patternA(other.m_patternA->clone()),
	m_patternB(other.m_patternB->clone()) {}

RingPattern::RingPattern(RingPattern&& other) noexcept :
	Pattern(std::move(other)),
	m_patternA(std::move(other.m_patternA)),
	m_patternB(std::move(other.m_patternB)) {
	// Reset source object pour éviter des doublons
	other.m_patternA = std::make_shared<SolidColorPattern>(Color::white);
	other.m_patternB = std::make_shared<SolidColorPattern>(Color::black);
}


// Member functions
bool RingPattern::equals(Pattern const& other) const {
	// Cast sécurisé car operator== vérifie déjà le type
	auto& typedOther = static_cast<const RingPattern&>(other);
	return Pattern::equals(other) &&
		*m_patternA == *typedOther.m_patternA &&
		*m_patternB == *typedOther.m_patternB;
}

bool RingPattern::operator==(RingPattern const& other) const {
	return Pattern::operator==(other) &&
		*m_patternA == *other.m_patternA &&
		*m_patternB == *other.m_patternB;
}

RingPattern& RingPattern::operator=(RingPattern const& other) {
	if (this != &other) {
		Pattern::operator=(other);
		m_patternA = other.m_patternA->clone();
		m_patternB = other.m_patternB->clone();
	}
	return *this;
}

RingPattern& RingPattern::operator=(RingPattern&& other) noexcept {
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

Color RingPattern::patternAt(Point const& objectPoint) const {
	Point patternPoint = m_matrix.inverted() * objectPoint;

	if (
		static_cast<int>(
			std::floor(
				std::sqrt(patternPoint.getX() * patternPoint.getX() + patternPoint.getZ() * patternPoint.getZ())
			)
		) % 2 == 0.0
	) {
		return m_patternA->patternAt(patternPoint);
	}
	return m_patternB->patternAt(patternPoint);
}

std::shared_ptr<Pattern> RingPattern::clone() const {
	return std::make_shared<RingPattern>(*this);
}


// Non-member functions
bool operator!=(RingPattern const& a, RingPattern const& b) {
	return !(a == b);
}
