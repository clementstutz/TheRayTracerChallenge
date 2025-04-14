#include "Pattern_for_Test.h"
#include "SolidColorPattern.h"

// Constructors
Pattern_for_Test::Pattern_for_Test() :
	Pattern(),
	m_patternA(std::make_shared<SolidColorPattern>(Color::white)),
	m_patternB(std::make_shared<SolidColorPattern>(Color::black)) {}

Pattern_for_Test::Pattern_for_Test(Pattern const& a, Pattern const& b) :
	Pattern(),
	m_patternA(a.clone()),
	m_patternB(b.clone()) {}

Pattern_for_Test::Pattern_for_Test(Pattern_for_Test const& other) :
	Pattern(other),
	m_patternA(other.m_patternA->clone()),
	m_patternB(other.m_patternB->clone()) {}

Pattern_for_Test::Pattern_for_Test(Pattern_for_Test&& other) noexcept :
	Pattern(std::move(other)),
	m_patternA(std::move(other.m_patternA)),
	m_patternB(std::move(other.m_patternB)) {
	// Reset source object pour éviter des doublons
	other.m_patternA = std::make_shared<SolidColorPattern>(Color::white);
	other.m_patternB = std::make_shared<SolidColorPattern>(Color::black);
}


// Member functions
bool Pattern_for_Test::equals(Pattern const& other) const {
	// Cast sécurisé car operator== vérifie déjà le type
	auto& typedOther = static_cast<const Pattern_for_Test&>(other);
	return Pattern::equals(other) &&
		*m_patternA == *typedOther.m_patternA &&
		*m_patternB == *typedOther.m_patternB;
}

bool Pattern_for_Test::operator==(Pattern_for_Test const& other) const {
	return Pattern::operator==(other) &&
		*m_patternA == *other.m_patternA &&
		*m_patternB == *other.m_patternB;
}

Pattern_for_Test& Pattern_for_Test::operator=(Pattern_for_Test const& other) {
	if (this != &other) {
		Pattern::operator=(other);
		m_patternA = other.m_patternA->clone();
		m_patternB = other.m_patternB->clone();
	}
	return *this;
}

Pattern_for_Test& Pattern_for_Test::operator=(Pattern_for_Test&& other) noexcept {
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

Color Pattern_for_Test::patternAt(Point const& objectPoint) const {
	Point patternPoint = m_matrix.inverted() * objectPoint;

	return Color(patternPoint.getX(), patternPoint.getY(), patternPoint.getZ());
}

// Clone pattern - Design pattern Prototype
std::shared_ptr<Pattern> Pattern_for_Test::clone() const {
	return std::make_shared<Pattern_for_Test>(*this);
}


// Non-member functions
bool operator!=(Pattern_for_Test const& a, Pattern_for_Test const& b) {
	return !(a == b);
}