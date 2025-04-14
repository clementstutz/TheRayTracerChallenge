#pragma once
//#include <memory> // Pour std::shared_ptr

#include "Pattern.h"

class Pattern_for_Test : public Pattern
{
public:
	// public attributs for test purpose only !
	std::shared_ptr<Pattern> m_patternA;
	std::shared_ptr<Pattern> m_patternB;

	// Constructors
	Pattern_for_Test();
	Pattern_for_Test(Pattern const& a, Pattern const& b);
	Pattern_for_Test(Pattern_for_Test const& other);
	Pattern_for_Test(Pattern_for_Test&& other) noexcept;

	// Destructor
	~Pattern_for_Test() = default;

	// Member functions
	bool equals(Pattern const& other) const override;
	bool operator==(Pattern_for_Test const& other) const;
	Pattern_for_Test& operator=(Pattern_for_Test const& other);
	Pattern_for_Test& operator=(Pattern_for_Test&& other) noexcept;
	Color patternAt(Point const& objectPoint) const override;
	// Clone pattern - Design pattern Prototype
	std::shared_ptr<Pattern> clone() const override;
};

// Non-member functions
bool operator!=(Pattern_for_Test const& a, Pattern_for_Test const& b);
