#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
using namespace sf;
using namespace std;

class Card {
private:
	Sprite spr;
	string name;

public:
	Card() = default;

	void setCardTexture(Texture& t, string n) {
		spr.setTexture(t);
		spr.setScale(0.86, 0.86);
		name = n;
	}

	void setCardPosition(int x, int y) {
		spr.setPosition(x, y);
	}

	void drawCard(RenderWindow& window) const {
		window.draw(spr);
	}

	string getName() { return name; }
};
