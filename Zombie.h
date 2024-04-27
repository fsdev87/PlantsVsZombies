#ifndef ZOMBIES_H
#define ZOMBIES_H
#include "Animation.h"
#include "TextureManager.h"

class Plant;
class Zombie {
protected:
	Sprite sprite;
	Animation anim;
	float position[2];
	int health;
	float speed;
	float xFactor, yFactor;
	bool exists;
	Clock moveClock;
	TextureManager* TMptr;
	bool blocked = false;
	bool blockFlag = false;

public:
	Zombie() {
		this->xFactor = 185;
		this->yFactor = 32;
	}
	float* getPosition() {
		return this->position;
	}
	bool getExist() { return this->exists; }

	void changeTexture(Texture& tex) {
		this->sprite = Sprite(tex);
		this->anim = Animation(166, 144, 21);
		this->anim.setFrame(0);
	}

	void animate() {
		this->anim.animate(this->sprite);
	}

	void draw(RenderWindow& window) {
		if (this->exists) {
			this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
			window.draw(this->sprite);
		}
	}

	bool getBlockFlag() { return this->blockFlag; }
	void setBlockFlag(bool val) { this->blockFlag = val; }

	void setExist(bool val) { this->exists = val; }

	int getHealth() { return this->health; }

	void reduceHealth() {
		this->health -= 20;
	}

	virtual void move(Plant** plants, int plantsArrayIndex) {
		for (int i = 0; i < plantsArrayIndex; i++) {

			if (plants[i]->getPosition()[1] != this->position[1]) {
				continue;
			}
			// Taking absolute because on X-Axis
			// plants are on left (-ve side) and this (Zombie) comes from right (+ve side)
			if (plants[i]->getExist()) {
				float dt = abs(plants[i]->getPosition()[0] - this->position[0]);
				if (dt <= 0.6875) {
					this->blocked = true;
					if (!blockFlag) {
						this->changeTexture((*TMptr)["spritesheet-nZombEat"]);
						this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
						this->blockFlag = true;
					}
				}

				if (this->exists && this->blocked && dt <= 0.6875 && plants[i]->getEatClock().getElapsedTime().asMilliseconds() > 500) {
					plants[i]->beEaten();
					plants[i]->getEatClock().restart();
				}

			}
			else {
				if (this->blocked) {
					this->changeTexture((*TMptr)["spritesheet-nZombWalk"]);
					this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
				}
				this->blocked = false;
				this->blockFlag = false;
			}

			// there was a break here before removed it
		}
		if (this->moveClock.getElapsedTime().asMilliseconds() < 250 || blocked) return;
		this->position[0] -= this->speed;
		this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
		this->moveClock.restart();
	}

	virtual void moveDiagonal() {}


	virtual ~Zombie() {}
};

#endif