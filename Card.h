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
		this->spr.setTexture(t);
		this->spr.setScale(0.86, 0.86);
		this->name = n;
	}

	void setCardPosition(int x, int y) {
		this->spr.setPosition(x, y);
	}

	void drawCard(RenderWindow& window) const {
		window.draw(spr);
	}

	string getName() { return this->name; }
};
