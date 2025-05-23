#pragma once
//#include <memory> // Pour std::shared_ptr

#include "Pattern.h"

class GradientPattern : public Pattern
{
private:
	std::shared_ptr<Pattern> m_patternA;
	std::shared_ptr<Pattern> m_patternB;

public:
	// Constructors
	GradientPattern();
	GradientPattern(Pattern const& a, Pattern const& b);
	GradientPattern(GradientPattern const& other);
	GradientPattern(GradientPattern&& other) noexcept;

	// Destructor
	~GradientPattern() = default;

	// Member functions
	bool equals(Pattern const& other) const override;
	bool operator==(GradientPattern const& other) const;
	GradientPattern& operator=(GradientPattern const& other);
	GradientPattern& operator=(GradientPattern&& other) noexcept;
	Color patternAt(Point const& objectPoint) const override;
	// Clone implementation
	std::shared_ptr<Pattern> clone() const override;
};

// Non-member functions
bool operator!=(GradientPattern const& a, GradientPattern const& b);
