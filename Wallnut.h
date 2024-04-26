#pragma once
#include "NonShooter.h"

class Wallnut : public NonShooter {

public:
	Wallnut(Texture& tex, int columns, float pos[2]) {
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 71, 71));
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->health = 500;
		this->cost = 100;
		this->exists = true;
		this->anim = Animation(71, 71, columns);
		this->sprite.setPosition(xFactor + position[0] * 80, yFactor + position[1] * 96);
	}

	void animate() {
		this->anim.animate(this->sprite);
	}


	void draw(RenderWindow& window) {
		if (this->exists)
			window.draw(sprite);
	}
};