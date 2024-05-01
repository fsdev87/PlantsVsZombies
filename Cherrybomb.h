#pragma once
#include "Exploder.h"

class Cherrybomb : public Exploder {
	int columns;

public:
	Cherrybomb(Texture& tex, int columns, float pos[2]) {
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 71, 71));
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->columns = columns; // for checking only if cherrybombs first animation is complete
		this->cost = 150;
		// no amount of zombies can eat it instantly
		this->health = 1000;
		this->exists = true;
		this->anim = Animation(71, 71, columns);
		this->anim.setDelay(150); // for a slower animation
		this->sprite.setPosition(xFactor + position[0] * 80, yFactor + position[1] * 96);
	}

	virtual void explode(Zombie** zombies, int zombiesArrayIndex) {
		if (this->exists) {
			int frame = this->anim.getFrame();
			if (frame == (this->columns - 10)) { // is the last frame

				for (int i = 0; i < zombiesArrayIndex; i++) {
					if (zombies[i]->getExist() && abs(zombies[i]->getPosition()[0] - this->position[0]) <= 1.5 && abs(zombies[i]->getPosition()[1] - this->position[1]) <= 1) {
						zombies[i]->setExist(false);
						zombies[i]->setAshes(true);
					}
				}
			}
			if (frame == (this->columns - 1)) {
				this->exists = false; // cherrybomb exploded
			}
			// this is done so that when one animation is done, the bomb is exploded
		}
	}

};