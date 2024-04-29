#ifndef ZOMBIES_H
#define ZOMBIES_H
#include "Animation.h"
#include "TextureManager.h"
#include "Plant.h"

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
	int eatIndex = -1;

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


	void setExist(bool val) { this->exists = val; }

	int getHealth() { return this->health; }

	void reduceHealth(int damage) {
		this->health -= damage;
	}

	virtual void move(Plant** plants, int plantsArrayIndex) {
		if (this->exists == false) return;
		if (this->moveClock.getElapsedTime().asMilliseconds() < 250) return;
		if (this->blocked) {
			if (this->eatIndex != -1) {
				eat(plants[eatIndex]);
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
						this->changeTexture((*TMptr)["spritesheet-nZombEat"]);
						this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
						this->eatIndex = i;
						return;
					}
				}
			}
		}
	}

	virtual void eat(Plant* plant) {
		if (plant->getExist()) {
			if (plant->getEatClock().getElapsedTime().asMilliseconds() > 500) {
				plant->beEaten();
				plant->getEatClock().restart();
			}
		}
		else {
			this->blocked = false;
			this->changeTexture((*TMptr)["spritesheet-nZombWalk"]);
			this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			this->eatIndex = -1;
		}
	}

	virtual void moveDiagonal() {}


	virtual ~Zombie() {}
};

#endif