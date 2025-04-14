#include "CheckersPattern.h"
#include "SolidColorPattern.h"
#include "Utils.h"

// Constructors
CheckersPattern::CheckersPattern() :
	Pattern(),
	m_patternA(std::make_shared<SolidColorPattern>(Color::white)),
	m_patternB(std::make_shared<SolidColorPattern>(Color::black)) {}

CheckersPattern::CheckersPattern(Pattern const& a, Pattern const& b) :
	Pattern(),
	m_patternA(a.clone()),
	m_patternB(b.clone()) {}

CheckersPattern::CheckersPattern(CheckersPattern const& other) :
	Pattern(other),
	m_patternA(other.m_patternA->clone()),
	m_patternB(other.m_patternB->clone()) {}

CheckersPattern::CheckersPattern(CheckersPattern&& other) noexcept :
	Pattern(std::move(other)),
	m_patternA(std::move(other.m_patternA)),
	m_patternB(std::move(other.m_patternB)) {
	// Reset source object pour éviter des doublons
	other.m_patternA = std::make_shared<SolidColorPattern>(Color::white);
	other.m_patternB = std::make_shared<SolidColorPattern>(Color::black);
}


// Member functions
bool CheckersPattern::equals(Pattern const& other) const {
	// Cast sécurisé car operator== vérifie déjà le type
	auto& typedOther = static_cast<const CheckersPattern&>(other);
	return Pattern::equals(other) &&
		*m_patternA == *typedOther.m_patternA &&
		*m_patternB == *typedOther.m_patternB;
}

bool CheckersPattern::operator==(CheckersPattern const& other) const {
	return Pattern::operator==(other) &&
		*m_patternA == *other.m_patternA &&
		*m_patternB == *other.m_patternB;
}

CheckersPattern& CheckersPattern::operator=(CheckersPattern const& other) {
	if (this != &other) {
		Pattern::operator=(other);
		m_patternA = other.m_patternA->clone();
		m_patternB = other.m_patternB->clone();
	}
	return *this;
}

CheckersPattern& CheckersPattern::operator=(CheckersPattern&& other) noexcept {
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

Color CheckersPattern::patternAt(Point const& objectPoint) const {
	Point patternPoint = m_matrix.inverted() * objectPoint;

	if ((static_cast<int>(std::floor(patternPoint.getX())) + 
		static_cast<int>(std::floor(patternPoint.getY())) + 
		static_cast<int>(std::floor(patternPoint.getZ()))) % 2 == 0.0) {
		return m_patternA->patternAt(patternPoint);
	}
	return m_patternB->patternAt(patternPoint);
}

std::shared_ptr<Pattern> CheckersPattern::clone() const {
	return std::make_shared<CheckersPattern>(*this);
}


// Non-member functions
bool operator!=(CheckersPattern const& a, CheckersPattern const& b) {
	return !(a == b);
}
