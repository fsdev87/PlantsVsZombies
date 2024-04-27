#pragma once
#include "Zombie.h"

class NormalZombie : public Zombie {
private:
	float speed;
	Animation anim;

	Clock moveClock;

public:
	NormalZombie(Texture& tex, int columns, float pos[2]) {
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->speed = 0.25;
		this->health = 100;
		this->exists = true;
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->anim = Animation(166, 144, columns);
		this->moveClock.restart();
	}

	void draw(RenderWindow& window) {
		if (exists) {
			this->sprite.setPosition(xFactor + position[0] * 80, yFactor + position[1] * 96);
			window.draw(this->sprite);
		}
	}

	void move() {
		if (moveClock.getElapsedTime().asMilliseconds() < 250) return;
		this->position[0] -= 0.01;
		this->sprite.setPosition(xFactor + this->position[0] * 80, yFactor + this->position[1] * 96);
		this->moveClock.restart();
	}

	void animate() {
		this->anim.animate(this->sprite);
	}

};