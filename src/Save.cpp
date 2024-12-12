#include <iostream>

#include "Save.h"

void Save::saveCanvas(Canvas const& canvas, std::string filename) {
	createPPM(canvas, filename);
	//ffmpeg -y -loglevel 0 -i filename + '.ppm' filename + '.png';
}

void Save::createPPM(Canvas const& canvas, std::string& filename) {
	filename += ".ppm";
	std::ofstream file(filename, std::ios::out | std::ios::trunc);  //On essaye d'ouvrir le fichier

	if (!file) {	//On teste si tout est OK avant d'utiliser le fichier
		std::cerr << "ERREUR: Impossible de cr�er ou d'ouvrir le fichier " << filename << "." << std::endl;
		return;
	}

	int maxValue = 255;

	// �crit l'en-t�te du fichier PPM
	writePPMHead(canvas, maxValue, file);

	// �crit les donn�es du Canvas
	writePPMBody(canvas, maxValue, file);

	file.close();
	if (!file) {
		std::cerr << "ERREUR: Probl�me lors de la fermeture du fichier " << filename << "." << std::endl;
	}
}

void Save::writePPMHead(Canvas const& canvas, int maxValue, std::ofstream& flux) {
	flux << "P3\n";
	flux << canvas.getWidth() << " " << canvas.getHeight() << "\n";
	flux << maxValue << "\n";
}

void Save::writePPMBody(Canvas const& canvas, int maxValue, std::ofstream& flux) {
	int height = canvas.getHeight();
	int width = canvas.getWidth();
	const int maxLineLength = 70; // Limitation des lignes � 70 caract�res
	std::string currentLine;      // Accumule les pixels pour la ligne actuelle

	for (int y = 0; y < height; ++y) {  // 1: (int y = 0; y < height; ++y) -or-  2 :(int y = height-1; y >= 0; --y)
		for (int x = 0; x < width; ++x) {
			const Color& pixel = canvas.getPixel(x, y);

			// Convertit les valeurs de couleur en entiers (clamp�es entre 0 et maxValue)
			int r = clamp(pixel.getR() * maxValue, maxValue);
			int g = clamp(pixel.getG() * maxValue, maxValue);
			int b = clamp(pixel.getB() * maxValue, maxValue);

			// Ajoute les valeurs RGB au texte de la ligne courante
			std::string pixelText = std::to_string(r) + " " +
				std::to_string(g) + " " +
				std::to_string(b) + " ";

			// V�rifie si l'ajout du pixel d�passerait 70 caract�res
			if (currentLine.size() + pixelText.size() > maxLineLength) {
				flux << currentLine << "\n"; // �crit la ligne actuelle dans le fichier
				currentLine.clear();         // R�initialise la ligne
			}

			currentLine += pixelText; // Ajoute le texte du pixel � la ligne
		}

		// �crit les pixels restants de la ligne
		if (!currentLine.empty()) {
			flux << currentLine << "\n";
			currentLine.clear();
		}
	}
}

int Save::clamp(float channelColor, int maxValue, int minValue) {
	int value = static_cast<int>(channelColor + 0.5f); // Arrondi au plus proche
	if (value > maxValue) return maxValue;
	else if(value < minValue) return minValue;
	else return value;
}
