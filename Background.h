#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;


class Background {
	Sprite backgroundSprite;
public:
	Background(TextureManager* tm) {
		backgroundSprite.setTexture(tm->getTexture("bgday"));
	}
	Sprite& getSprite() { return backgroundSprite; }
};