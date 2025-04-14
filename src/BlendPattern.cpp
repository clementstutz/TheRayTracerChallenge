#include "BlendPattern.h"
#include "SolidColorPattern.h"
#include "Utils.h"

// Constructors
BlendPattern::BlendPattern() :
	Pattern(),
	m_patternA(std::make_shared<SolidColorPattern>(Color::white)),
	m_patternB(std::make_shared<SolidColorPattern>(Color::black)),
	m_mixingValue(0.5) {}

BlendPattern::BlendPattern(Pattern const& a, Pattern const& b, double mixingValue) :
	Pattern(),
	m_patternA(a.clone()),
	m_patternB(b.clone()),
	m_mixingValue(mixingValue) {}

BlendPattern::BlendPattern(BlendPattern const& other) :
	Pattern(other),
	m_patternA(other.m_patternA->clone()),
	m_patternB(other.m_patternB->clone()),
	m_mixingValue(other.m_mixingValue) {}

BlendPattern::BlendPattern(BlendPattern&& other) noexcept :
	Pattern(std::move(other)),
	m_patternA(std::move(other.m_patternA)),
	m_patternB(std::move(other.m_patternB)),
	m_mixingValue(std::move(other.m_mixingValue)) {
	// Reset source object pour éviter des doublons
	other.m_patternA = std::make_shared<SolidColorPattern>(Color::white);
	other.m_patternB = std::make_shared<SolidColorPattern>(Color::black);
	other.m_mixingValue = 0.0;
}


// Accessors
double BlendPattern::GetMixingValue() const { return m_mixingValue; }


// Member functions
bool BlendPattern::equals(Pattern const& other) const {
	// Cast sécurisé car operator== vérifie déjà le type
	auto& typedOther = static_cast<const BlendPattern&>(other);
	return Pattern::equals(other) &&
		*m_patternA == *typedOther.m_patternA &&
		*m_patternB == *typedOther.m_patternB;
}

bool BlendPattern::operator==(BlendPattern const& other) const {
	return Pattern::operator==(other) &&
		*m_patternA == *other.m_patternA &&
		*m_patternB == *other.m_patternB &&
		m_mixingValue == other.m_mixingValue;
}

BlendPattern& BlendPattern::operator=(BlendPattern const& other) {
	if (this != &other) {
		Pattern::operator=(other);
		m_patternA = other.m_patternA->clone();
		m_patternB = other.m_patternB->clone();
		m_mixingValue = other.m_mixingValue;
	}
	return *this;
}

BlendPattern& BlendPattern::operator=(BlendPattern&& other) noexcept {
	if (this != &other) {
		Pattern::operator=(std::move(other));
		m_patternA = std::move(other.m_patternA);
		m_patternB = std::move(other.m_patternB);
		m_mixingValue = std::move(other.m_mixingValue);
		// Reset source object
		other.m_patternA = std::make_shared<SolidColorPattern>(Color::white);
		other.m_patternB = std::make_shared<SolidColorPattern>(Color::black);
		other.m_mixingValue = 0.0;
	}
	return *this;
}

Color BlendPattern::patternAt(Point const& objectPoint) const {
	Point patternPoint = m_matrix.inverted() * objectPoint;

	return m_patternA->patternAt(patternPoint) * (1.0 - m_mixingValue) + m_patternB->patternAt(patternPoint) * m_mixingValue;
}

std::shared_ptr<Pattern> BlendPattern::clone() const {
	return std::make_shared<BlendPattern>(*this);
}


// Non-member functions
bool operator!=(BlendPattern const& a, BlendPattern const& b) {
	return !(a == b);
}
