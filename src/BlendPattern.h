#pragma once
//#include <memory> // Pour std::shared_ptr

#include "Pattern.h"

class BlendPattern : public Pattern
{
private:
	std::shared_ptr<Pattern> m_patternA;
	std::shared_ptr<Pattern> m_patternB;
	double m_mixingValue;

public:
	// Constructors
	BlendPattern();
	BlendPattern(Pattern const& a, Pattern const& b, double mixingValue =0.5);
	BlendPattern(BlendPattern const& other);
	BlendPattern(BlendPattern&& other) noexcept;

	// Destructor
	~BlendPattern() = default;

	// Accessors
	double GetMixingValue() const;

	// Member functions
	bool equals(Pattern const& other) const override;
	bool operator==(BlendPattern const& other) const;
	BlendPattern& operator=(BlendPattern const& other);
	BlendPattern& operator=(BlendPattern&& other) noexcept;
	Color patternAt(Point const& objectPoint) const override;
	// Clone implementation
	std::shared_ptr<Pattern> clone() const override;
};

// Non-member functions
bool operator!=(BlendPattern const& a, BlendPattern const& b);