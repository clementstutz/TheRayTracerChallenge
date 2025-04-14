#pragma once
//#include <memory> // Pour std::shared_ptr

#include "Pattern.h"

class RingPattern : public Pattern
{
private:
	std::shared_ptr<Pattern> m_patternA;
	std::shared_ptr<Pattern> m_patternB;

public:
	// Constructors
	RingPattern();
	RingPattern(Pattern const& a, Pattern const& b);
	RingPattern(RingPattern const& other);
	RingPattern(RingPattern&& other) noexcept;

	// Destructor
	~RingPattern() = default;

	// Member functions
	bool equals(Pattern const& other) const override;
	bool operator==(RingPattern const& other) const;
	RingPattern& operator=(RingPattern const& other);
	RingPattern& operator=(RingPattern&& other) noexcept;
	Color patternAt(Point const& objectPoint) const override;
	std::shared_ptr<Pattern> clone() const override;
};

// Non-member functions
bool operator!=(RingPattern const& a, RingPattern const& b);
