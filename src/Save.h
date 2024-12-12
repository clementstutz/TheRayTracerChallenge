#pragma once
#include <string>
#include <fstream>

#include "Canvas.h"

class Save
{
public:
	static void saveCanvas(Canvas const& canvas, std::string filename);

private:
	static void createPPM(Canvas const& canvas, std::string& filename);

	static void writePPMHead(Canvas const&, int maxValue, std::ofstream& flux);

	static void writePPMBody(Canvas const& canvas, int maxValue, std::ofstream& flux);

	static int clamp(float channelColor, int maxValue, int minValue = 0);
};

