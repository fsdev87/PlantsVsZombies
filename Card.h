#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
using namespace sf;
using namespace std;

class Card {
private:
	Sprite spr;
	string name;
	Texture brightTex;
	Texture dimTex;
	int cost;

public:
	Card() = default;

	void setCardTexture(Texture& dim, Texture& bright, string n, int cost) {
		brightTex = bright;
		dimTex = dim;
		this->cost = cost;
		this->spr.setTexture(dimTex);

		this->spr.setScale(0.86, 0.86);
		this->name = n;
	}

	void setCardPosition(int x, int y) {
		this->spr.setPosition(x, y);
	}

	void setTexture(string s) {
		if (s == "dim") {
			spr.setTexture(dimTex);
		}
		else if (s == "bright") {
			spr.setTexture(brightTex);
		}
	}

	void drawCard(RenderWindow& window) const {
		window.draw(spr);
	}

	int getCost() const { return this->cost; }


	string getName() { return this->name; }
};
