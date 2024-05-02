#pragma once
#include "Zombie.h"

class NormalZombie : public Zombie {
public:
	NormalZombie(Texture& tex, int columns, float pos[2], TextureManager* TM) {
		this->TMptr = TM;
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->speed = 0.03125;
		this->health = 100;
		this->exists = true;
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->anim = Animation(166, 144, columns);
		this->moveClock.restart();
	}

	void handleFlicker() {
		if (!this->exists) return;
		if (this->flicker) {
			// Turn off flicker after 150ms and reset appropriate texture
			if (flickerClock.getElapsedTime().asMilliseconds() > 150) {
				this->flicker = false;

				// Reset texture
				if (this->state == "walk") {
					this->changeTexture((*TMptr)["spritesheet-nZombWalk"], this->anim.getFrame(), 22);
				}
				else if (this->state == "eat") {
					this->changeTexture((*TMptr)["spritesheet-nZombEat"], this->anim.getFrame(), 21);
				}
				this->sprite.setTextureRect(IntRect((this->anim.getFrame()) * 166, 0, 166, 144));
				return;
			}

			// Set texture
			if (this->state == "walk") {
				this->changeTexture((*TMptr)["spritesheet-nZombWalkDim"], this->anim.getFrame(), 22);
			}
			else if (this->state == "eat") {
				this->changeTexture((*TMptr)["spritesheet-nZombEatDim"], this->anim.getFrame(), 21);
			}

			this->sprite.setTextureRect(IntRect((this->anim.getFrame()) * 166, 0, 166, 144));
		}
	}

	void move(Plant** plants, int plantsArrayIndex) {
		if (this->exists == false) return;

		if (this->moveClock.getElapsedTime().asMilliseconds() < 250) return;
		if (this->blocked) {
			if (this->eatIndex != -1) {
				this->state = "eat";
				eat(plants[this->eatIndex]);
			}
			return;
		}

		this->moveClock.restart();
		this->position[0] -= this->speed;
		this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);


		for (int i = 0; i < plantsArrayIndex; i++) {
			if (plants[i]->getExist()) {
				if (plants[i]->getPosition()[1] == this->position[1]) {
					float dt = plants[i]->getPosition()[0] - this->position[0];
					if (dt <= 0 && dt >= -0.6875) {
						this->blocked = true;
						this->changeTexture((*TMptr)["spritesheet-nZombEat"], 0, 21);
						this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
						this->eatIndex = i;
						return;
					}
				}
			}
		}
	}

	void eat(Plant* plant) {
		if (plant->getExist()) {
			if (plant->getEatClock().getElapsedTime().asMilliseconds() > 500) {
				plant->beEaten();
				plant->getEatClock().restart();
			}
		}
		else {
			this->blocked = false;
			this->state = "walk";
			this->changeTexture((*(this->TMptr))["spritesheet-nZombWalk"], 0, 22);
			this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			this->eatIndex = -1;
		}
	}
};