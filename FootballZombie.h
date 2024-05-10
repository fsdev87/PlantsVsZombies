#pragma once
#include "Zombie.h"

class FootballZombie : public Zombie {
private:
	Clock reverseClock;
	float reverseDelay;

public:
	FootballZombie(Texture& tex, int columns, float pos[2], TextureManager* TM, SoundManager* SM) {
		this->SMptr = SM;
		this->TMptr = TM;
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->speed = 0.125;
		this->health = 180;
		this->exists = true;
		this->limit = 60;
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->anim = Animation(166, 144, columns);
		this->moveClock.restart(), this->reverseClock.restart();
		this->anim.setDelay(80);
		this->reverseDelay = 6 + rand() % 5;
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

					if (this->health > 120) {
						this->changeTexture((*TMptr)["football-walk"], 0, 11);
					}
					else if (this->health > 60 && this->health <= 120) {
						this->changeTexture((*TMptr)["football-walk-2"], 0, 11);
					}
					else {
						this->changeTexture((*TMptr)["football-walk-3"], 0, 10);
					}

				}
				else if (this->state == "eat") {

					if (this->health > 120) {
						this->changeTexture((*TMptr)["football-eat"], 0, 10);
					}
					else if (this->health > 60 && this->health <= 120) {
						this->changeTexture((*TMptr)["football-eat-2"], 0, 11);
					}
					else {
						this->changeTexture((*TMptr)["football-eat-3"], 0, 10);
					}

				}

				this->sprite.setTextureRect(IntRect((this->anim.getFrame()) * 166, 0, 166, 144));
				return;
			}

			// Set DIM texture
			if (this->state == "walk") {

				if (this->health > 120) {
					this->changeTexture((*TMptr)["football-walk-dim"], 0, 11);
				}
				else if (this->health > 60 && this->health <= 120) {
					this->changeTexture((*TMptr)["football-walk-2-dim"], 0, 11);
				}
				else {
					this->changeTexture((*TMptr)["football-walk-3-dim"], 0, 10);
				}

			}
			else if (this->state == "eat") {

				if (this->health > 120) {
					this->changeTexture((*TMptr)["football-eat-dim"], 0, 10);
				}
				else if (this->health > 60 && this->health <= 120) {
					this->changeTexture((*TMptr)["football-eat-2-dim"], 0, 11);
				}
				else {
					this->changeTexture((*TMptr)["football-eat-3-dim"], 0, 10);
				}

			}

			this->sprite.setTextureRect(IntRect((this->anim.getFrame()) * 166, 0, 166, 144));
		}
	}

	void reverseDirection() {
		if (this->reverseClock.getElapsedTime().asSeconds() > this->reverseDelay) {
			this->reverseClock.restart();
			this->speed *= -1;
			this->reverseDelay = 6 + rand() % 5;
		}
	}

	void move(Plant** plants, int plantsArrayIndex) {
		if (this->exists == false) return;


		if (this->moveClock.getElapsedTime().asMilliseconds() < this->moveDelay) return;

		reverseDirection();


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

						if (this->health > 120) {
							this->changeTexture((*TMptr)["football-eat"], 0, 10);
						}
						else if (this->health > 60 && this->health <= 120) {
							this->changeTexture((*TMptr)["football-eat-2"], 0, 11);
						}
						else {
							this->changeTexture((*TMptr)["football-eat-3"], 0, 10);
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

			if (this->health > 120) {
				this->changeTexture((*TMptr)["football-walk"], 0, 11);
			}
			else if (this->health > 60 && this->health <= 120) {
				this->changeTexture((*TMptr)["football-walk-2"], 0, 11);
			}
			else {
				this->changeTexture((*TMptr)["football-walk-3"], 0, 10);
			}

			this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			this->eatIndex = -1;
		}
	}

};


