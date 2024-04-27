#pragma once
#include "Animation.h"

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
	virtual void move() {
		if (this->moveClock.getElapsedTime().asMilliseconds() < 250) return;
		this->position[0] -= this->speed;
		this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
		this->moveClock.restart();
	}
	virtual void moveDiagonal() {}


	virtual ~Zombie() {}
};