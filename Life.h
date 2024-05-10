#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Life {
private:
	Sprite sprites[3];
	Texture texture;
	int lifeIndex = 3;

public:
	Life() {
		this->texture.loadFromFile("assets/Static/life.png");
		float posX = 12.75;
		for (int i = 0; i < 3; i++) {
			this->sprites[i].setTexture(this->texture);
			this->sprites[i].setPosition(posX * 80, 0);
			posX += 0.5;
		}
	}

	void decrementLives() { if (this->lifeIndex == 0) return; this->lifeIndex--; }

	void drawLives(RenderWindow& window) {
		for (int i = 0; i < this->lifeIndex; i++) {
			window.draw(this->sprites[i]);
		}
	}
};