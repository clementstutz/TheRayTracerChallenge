#pragma once
#include "Point.h"
#include "Mat4.h"
#include "Color.h"

class Pattern
{
protected:
	Mat4 m_matrix;

public:
	// Constructors
	Pattern();
	Pattern(Pattern const& other);
	Pattern(Pattern&& other) noexcept;

	// Destructor
	virtual ~Pattern() = default;

	// Accessors
	Mat4 GetMatrix() const;
	void SetMatrix(Mat4 const& mat);

	// Member functions
	virtual bool equals(Pattern const& other) const;
	bool operator==(Pattern const& other) const;
	Pattern& operator=(Pattern const& other);
	Pattern& operator=(Pattern&& other) noexcept;
	Color PatternAtObject(Point const& objectPoint) const;
	virtual Color patternAt(Point const& patternPoint) const = 0;
	// Clone pattern - Design pattern Prototype
	virtual std::shared_ptr<Pattern> clone() const = 0;
};

// Non-member functions
bool operator!=(Pattern const& a, Pattern const& b);