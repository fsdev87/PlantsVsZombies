#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class FontManager {
	Font fonts[4];

public:
	FontManager() {
		if (!fonts[0].loadFromFile("assets/fonts/burbank.otf")) {
			cout << "burbank.otf NOT FOUND\n";
		}
		if (!fonts[1].loadFromFile("assets/fonts/Samdan.ttf")) {
			cout << "Samdan.ttf NOT FOUND\n";
		}
		if (!fonts[2].loadFromFile("assets/fonts/SamdanEvil.ttf")) {
			cout << "SamdanEvil.ttf NOT FOUND\n";
		}
		if (!fonts[3].loadFromFile("assets/fonts/serio.TTF")) {
			cout << "serio.TTF NOT FOUND\n";
		}
	}
	Font& get(int n) { return fonts[n]; }
	Font& operator[] (int n) { return fonts[n]; }
};