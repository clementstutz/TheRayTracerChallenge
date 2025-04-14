#pragma once
//#include <memory> // Pour std::shared_ptr

#include "Pattern.h"

class SolidColorPattern : public Pattern
{
protected:
	Color m_color;


public:
	// Constructors
	SolidColorPattern();
	SolidColorPattern(Color const& color);
	SolidColorPattern(SolidColorPattern const& other);
	SolidColorPattern(SolidColorPattern&& other) noexcept;

	// Destructor
	~SolidColorPattern() = default;

	// Member functions
	bool equals(Pattern const& other) const override;
	bool operator==(SolidColorPattern const& other) const;
	SolidColorPattern& operator=(SolidColorPattern const& other);
	SolidColorPattern& operator=(SolidColorPattern&& other) noexcept;
	Color patternAt(Point const& objectPoint) const override;
	std::shared_ptr<Pattern> clone() const override;
};

// Non-member functions
bool operator!=(SolidColorPattern const& a, SolidColorPattern const& b);
