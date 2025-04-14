#pragma once
//#include <memory> // Pour std::shared_ptr

#include "Pattern.h"

class RadialGradientPattern : public Pattern
{
private:
	std::shared_ptr<Pattern> m_patternA;
	std::shared_ptr<Pattern> m_patternB;

public:
	// Constructors
	RadialGradientPattern();
	RadialGradientPattern(Pattern const& a, Pattern const& b);
	RadialGradientPattern(RadialGradientPattern const& other);
	RadialGradientPattern(RadialGradientPattern&& other) noexcept;

	// Destructor
	~RadialGradientPattern() = default;

	// Member functions
	bool equals(Pattern const& other) const override;
	bool operator==(RadialGradientPattern const& other) const;
	RadialGradientPattern& operator=(RadialGradientPattern const& other);
	RadialGradientPattern& operator=(RadialGradientPattern&& other) noexcept;
	Color patternAt(Point const& objectPoint) const override;
	std::shared_ptr<Pattern> clone() const override;
};

// Non-member functions
bool operator!=(RadialGradientPattern const& a, RadialGradientPattern const& b);
