#pragma once
#include <iostream>
#include "Vector.h"

class Environment
{
public:
	Vector m_gravity, m_wind;

	Environment(Vector gravity, Vector wind);
};

