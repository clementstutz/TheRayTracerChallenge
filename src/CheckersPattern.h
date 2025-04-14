#pragma once
//#include <memory> // Pour std::shared_ptr

#include "Pattern.h"

class CheckersPattern : public Pattern
{
private:
	std::shared_ptr<Pattern> m_patternA;
	std::shared_ptr<Pattern> m_patternB;

public:
	// Constructors
	CheckersPattern();
	CheckersPattern(Pattern const& a, Pattern const& b);
	CheckersPattern(CheckersPattern const& other);
	CheckersPattern(CheckersPattern&& other) noexcept;

	// Destructor
	~CheckersPattern() = default;

	// Member functions
	bool equals(Pattern const& other) const override;
	bool operator==(CheckersPattern const& other) const;
	CheckersPattern& operator=(CheckersPattern const& other);
	CheckersPattern& operator=(CheckersPattern&& other) noexcept;
	Color patternAt(Point const& objectPoint) const override;
	// Clone implementation
	std::shared_ptr<Pattern> clone() const override;
};

// Non-member functions
bool operator!=(CheckersPattern const& a, CheckersPattern const& b);
