#pragma once
#include <memory> // Pour std::shared_ptr

#include "Pattern.h"

class StripePattern : public Pattern
{
private:
	std::shared_ptr<Pattern> m_patternA;
	std::shared_ptr<Pattern> m_patternB;

public:
	// Constructors
	StripePattern();
	StripePattern(Pattern const& a, Pattern const& b);
	StripePattern(StripePattern const& other);
	StripePattern(StripePattern&& other) noexcept;

	// Destructor
	~StripePattern() = default;

	// Member functions
	bool equals(Pattern const& other) const override;
	bool operator==(StripePattern const& other) const;
	StripePattern& operator=(StripePattern const& other);
	StripePattern& operator=(StripePattern&& other) noexcept;
	Color patternAt(Point const& objectPoint) const override;
	std::shared_ptr<Pattern> clone() const override;
};

// Non-member functions
bool operator!=(StripePattern const& a, StripePattern const& b);
