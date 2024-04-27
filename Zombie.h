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


	virtual void move(Plant** plants, int plantsArrayIndex) {
		for (int i = 0; i < plantsArrayIndex; i++) {

			if (plants[i]->getPosition()[1] != this->position[1]) {
				continue;
			}
			// Taking absolute because on X-Axis
			// plants are on left (-ve side) and this (Zombie) comes from right (+ve side)
			if (plants[i]->getExist()) {
				float dt = (plants[i]->getPosition()[0] - this->position[0]);
				if (dt >= -0.6875 && dt <= 0) this->blocked = true;
			}
			else {
				this->blocked = false;
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