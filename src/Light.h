#pragma once
#include "Point.h"
#include "Color.h"

class Light
{
private:
	static int m_currentId;
	int m_id;
	Color m_intensity;
	Point m_position;

	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Light();
	Light(Point position, Color intensity);
	Light(Light const& other);
	Light(Light&& other) noexcept;
	

	// Destructor
	~Light();// = default;


	// Accessors
	int static GetNbInstances();
	int GetId() const;
	Color GetIntensity() const;
	Point GetPosition() const;
	void SetIntensity(Color const& color);
	void SetPosition(Point const& position);


	// Member functions
	Light& operator=(Light const& other);
	Light& operator=(Light&& other) noexcept;
	bool operator==(Light const& other) const;
	friend std::ostream& operator<<(std::ostream& flux, Light const& light);
};
