#pragma once
#include <string>
#include <fstream>
#include "Canvas.h"

class Save
{
public:
	// M�thode publique statique pour sauvegarder un Canvas dans un fichier PPM
	static void saveCanvas(Canvas const& canvas, std::string const& filename = "temp");

private:
	// M�thodes priv�es pour g�rer les �tapes de la cr�ation et �criture du fichier
	static void createPPM(Canvas const& canvas, std::string filename);

	static void writePPMHead(Canvas const&, int maxValue, std::ofstream& flux);

	static void writePPMBody(Canvas const& canvas, int maxValue, std::ofstream& flux);

	// Utilitaire pour limiter les valeurs d'une couleur
	static int clamp(float channelColor, int maxValue, int minValue = 0);
};

