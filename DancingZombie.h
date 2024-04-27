#pragma once
#include "Zombie.h"

class DancingZombie : public Zombie {
public:
	DancingZombie(Texture& tex, int columns, float pos[2]) {
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->speed = 0.0625;
		this->health = 100;
		this->exists = true;
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->anim = Animation(166, 144, columns);
		this->moveClock.restart();
		this->anim.setDelay(30);
	}
};