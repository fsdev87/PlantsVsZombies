#pragma once
#include "Zombie.h"

class NormalZombie : public Zombie {
public:
	NormalZombie(Texture& tex, int columns, float pos[2], TextureManager* TM) {
		this->TMptr = TM;
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->speed = 0.03125;
		this->health = 120;
		this->exists = true;
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->anim = Animation(166, 144, columns);
		this->moveClock.restart();
	}
};