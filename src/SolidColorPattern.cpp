#include "SolidColorPattern.h"

// Constructors
SolidColorPattern::SolidColorPattern() :
	Pattern(),
	m_color(Color::black) {}

SolidColorPattern::SolidColorPattern(Color const& color) :
	Pattern(),
	m_color(color) {}

SolidColorPattern::SolidColorPattern(SolidColorPattern const& other) :
	Pattern(other),
	m_color(other.m_color) {}

SolidColorPattern::SolidColorPattern(SolidColorPattern&& other) noexcept :
	Pattern(std::move(other)),
	m_color(std::move(other.m_color)) {
	// Reset source object pour éviter des doublons
	other.m_color = Color::black;
}


// Member functions
bool SolidColorPattern::equals(Pattern const& other) const {
	// Cast sécurisé car operator== vérifie déjà le type
	auto& typedOther = static_cast<const SolidColorPattern&>(other);
	return Pattern::equals(other) &&
		m_color == typedOther.m_color;
}

bool SolidColorPattern::operator==(SolidColorPattern const& other) const {
	return Pattern::operator==(other) &&
		m_color == other.m_color;
}

SolidColorPattern& SolidColorPattern::operator=(SolidColorPattern const& other) {
	if (this != &other) {
		Pattern::operator=(other);
		m_color = other.m_color;
	}
	return *this;
}

SolidColorPattern& SolidColorPattern::operator=(SolidColorPattern&& other) noexcept {
	if (this != &other) {
		Pattern::operator=(std::move(other));
		m_color = std::move(other.m_color);
		// Reset source object
		other.m_color = Color::black;
	}
	return *this;
}

Color SolidColorPattern::patternAt(Point const& objectPoint) const { return m_color; }

std::shared_ptr<Pattern> SolidColorPattern::clone() const {
	return std::make_shared<SolidColorPattern>(*this);
}


// Non-member functions
bool operator!=(SolidColorPattern const& a, SolidColorPattern const& b) {
	return !(a == b);
}