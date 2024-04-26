#pragma once
#include "Plant.h"

class Sunflower : public Plant {
	Animation anim;
	Clock sunClock;

	Animation sunAnim;
	Sprite sunSprite;
	bool showSun = false;
	Clock showSunClock;

public:
	Sunflower(Texture& tex, Texture& sunT, int columns, float pos[2]) {
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 71, 71));
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->health = 100;
		this->cost = 100;
		this->exists = true;
		this->anim = Animation(71, 71, columns);
		this->sprite.setPosition(xFactor + position[0] * 80, yFactor + position[1] * 96);

		// Everything sun related
		this->sunAnim = Animation(71, 71, 22);
		this->sunSprite.setTexture(sunT);
		this->sunSprite.setScale(0.7, 0.7);
		sunSprite.setPosition(xFactor + 35 + position[0] * 80, yFactor + position[1] * 96 - 15);
		this->showSunClock.restart();

	}

	void generateSun() {
		if (showSunClock.getElapsedTime().asSeconds() < 5.0) return;
		this->showSun = true;
	}

	void animate() {
		this->anim.animate(this->sprite);
		if (this->showSun) this->sunAnim.animate(this->sunSprite);
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
		if (this->showSun) window.draw(sunSprite);
	}
};