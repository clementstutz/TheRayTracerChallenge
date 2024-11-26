#pragma once
#include <iostream>
#include "Point.h"
#include "Vector.h"

class Projectile
{
public:
	Point m_position;
	Vector m_velocity;

	Projectile(Point position, Vector velocity);
};

