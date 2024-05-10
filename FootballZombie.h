#pragma once
#include "Zombie.h"

class FootballZombie : public Zombie {
private:
	Clock reverseClock;
	float reverseDelay;
	string direction = "left";

public:
	FootballZombie(Texture& tex, int columns, float pos[2], TextureManager* TM, SoundManager* SM) {
		this->SMptr = SM;
		this->TMptr = TM;
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->speed = 0.125;
		this->health = 180;
		this->exists = true;
		this->limit = 40;
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
		if (this->flicker && this->flickerClock.getElapsedTime().asMilliseconds() > 50) {
			this->flicker = false;
			this->sprite.setColor(Color(255, 255, 255, 255));
		}
	}

	void makeDead() {
		if (this->exists == false && this->ashes != true) {
			this->changeTexture(this->TMptr->getTexture("football-die"), 0, 7);
			this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			this->dead = true, this->deadClock.restart();
			this->SMptr->playSound("zombie-fall");
		}
	}

	void handleDeath(RenderWindow& window) {
		if (!this->exists && this->dead) {
			if (this->deadClock.getElapsedTime().asSeconds() > 0.705) {
				this->dead = false;
			}
			this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
			window.draw(this->sprite);
		}
	}

	void checkHealth() {
		if (this->exists) {
			if (this->health == 120) {
				if (this->state == "walk") {
					changeTexture(this->TMptr->getTexture("football-walk-2"), 0, 11);
				}
				else {
					changeTexture(this->TMptr->getTexture("football-eat-2"), 0, 11);
				}
				this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			}
			else if (this->health == this->limit) {
				if (this->state == "walk") {
					changeTexture(this->TMptr->getTexture("football-walk-3"), 0, 10);
				}
				else {
					changeTexture(this->TMptr->getTexture("football-eat-3"), 0, 10);
				}
				setHeadFall(true);
				this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			}
			else if (this->health == 0) {
				this->exists = false;
				this->makeDead();
			}
		}
	}

	void reverseDirection() {
		if (this->reverseClock.getElapsedTime().asSeconds() > this->reverseDelay) {
			this->reverseClock.restart();
			this->speed *= -1;
			this->reverseDelay = 6 + rand() % 5;
			this->direction = this->direction == "left" ? "right" : "left";
		}
	}

	void move(Plant** plants, int plantsArrayIndex) {
		if (this->exists == false) return;


		if (this->moveClock.getElapsedTime().asMilliseconds() < this->moveDelay) return;

		handleFlicker();
		//reverseDirection();

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
				float* plantPos = plants[i]->getPosition();

				if (plantPos[1] == this->position[1]) {
					float dt = plantPos[0] - this->position[0];
					if (dt <= 0 && dt >= -0.6875) {
						this->blocked = true;

						if (this->health > 120) {
							this->changeTexture(this->TMptr->getTexture("football-eat"), 0, 10);
						}
						else if (this->health > this->limit && this->health <= 120) {
							this->changeTexture(this->TMptr->getTexture("football-eat-2"), 0, 11);
						}
						else {
							this->changeTexture(this->TMptr->getTexture("football-eat-3"), 0, 10);
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
				this->changeTexture(this->TMptr->getTexture("football-walk"), 0, 11);
			}
			else if (this->health > this->limit && this->health <= 120) {
				this->changeTexture(this->TMptr->getTexture("football-walk-2"), 0, 11);
			}
			else {
				this->changeTexture(this->TMptr->getTexture("football-walk-3"), 0, 10);
			}

			this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			this->eatIndex = -1;
		}
	}

};