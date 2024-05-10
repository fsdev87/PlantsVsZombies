#pragma once
#include "Zombie.h"

class NormalZombie : public Zombie {
public:
	NormalZombie(Texture& tex, int columns, float pos[2], TextureManager* TM, SoundManager* SM) {
		this->SMptr = SM;
		this->TMptr = TM;
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->speed = 0.0625;
		this->health = 120;
		this->exists = true;
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->anim = Animation(166, 144, columns);
		this->moveClock.restart();
		this->limit = 60;
		this->anim.setDelay(50);
		// head
		this->headSprite.setTexture(this->TMptr->getTexture("spritesheet-head"));
		this->headSprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->headAnim = Animation(150, 186, 12);
	}

	void handleFlicker() {
		if (!this->exists) return;

		if (this->flicker) {
			// Turn off flicker after 150ms and reset appropriate texture
			if (flickerClock.getElapsedTime().asMilliseconds() > 150) {
				this->flicker = false;
				// Reset texture
				if (this->state == "walk") {

					if (this->health > this->limit) {
						this->changeTexture((*TMptr)["spritesheet-nZombWalk"], this->anim.getFrame(), 22);
					}
					else {
						this->changeTexture((*(this->TMptr))["spritesheet-headLessWalk"], this->anim.getFrame(), 18);
					}

				}
				else if (this->state == "eat") {

					if (this->health > this->limit) {
						this->changeTexture((*TMptr)["spritesheet-nZombEat"], this->anim.getFrame(), 21);
					}
					else {
						this->changeTexture((*TMptr)["spritesheet-headLessEat"], this->anim.getFrame(), 11);
					}

				}

				this->sprite.setTextureRect(IntRect((this->anim.getFrame()) * 166, 0, 166, 144));
				return;
			}

			// Set texture
			if (this->state == "walk") {

				if (this->health > this->limit) {
					this->changeTexture((*TMptr)["spritesheet-nZombWalkDim"], this->anim.getFrame(), 22);
				}
				else {
					this->changeTexture((*(this->TMptr))["spritesheet-headLessWalkDim"], this->anim.getFrame(), 18);
				}

			}
			else if (this->state == "eat") {

				if (this->health > this->limit) {
					this->changeTexture((*TMptr)["spritesheet-nZombEatDim"], this->anim.getFrame(), 21);
				}
				else {
					this->changeTexture((*TMptr)["spritesheet-headLessEatDim"], this->anim.getFrame(), 11);
				}

			}

			this->sprite.setTextureRect(IntRect((this->anim.getFrame()) * 166, 0, 166, 144));
		}
	}

	void move(Plant** plants, int plantsArrayIndex) {
		if (this->exists == false) return;


		if (this->moveClock.getElapsedTime().asMilliseconds() < this->moveDelay) return;
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

						if (this->health > this->limit) {
							this->changeTexture((*TMptr)["spritesheet-nZombEat"], 0, 21);
						}
						else {
							this->changeTexture((*TMptr)["spritesheet-headLessEat"], 0, 11);
						}

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

			if (this->health > this->limit) {
				this->changeTexture((*(this->TMptr))["spritesheet-nZombWalk"], 0, 22);
			}
			else {
				this->changeTexture((*(this->TMptr))["spritesheet-headLessWalk"], 0, 18);
			}

			this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			this->eatIndex = -1;
		}
	}
};