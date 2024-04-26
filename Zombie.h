#pragma once
#include "Animation.h"


class Zombie {
protected:
	Sprite sprite;
	float position[2];
	int health;
	float xFactor, yFactor;

public:
	Zombie() {
		this->xFactor = 185, this->yFactor = 32;
	}
};


class NormalZombie : public Zombie {
private:
	float speed;
	bool exists;
	Animation anim;

public:
	NormalZombie(Texture& tex, int columns, float pos[2]) {
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->speed = 0.25;
		this->health = 100;
		this->exists = true;
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->anim = Animation(166, 144, columns);
	}

	void draw(RenderWindow& window) {
		if (exists) {
			this->sprite.setPosition(xFactor + position[0] * 80, yFactor + position[1] * 96);
			window.draw(this->sprite);
		}
	}

	void animate() {
		this->anim.animate(this->sprite);
	}

};