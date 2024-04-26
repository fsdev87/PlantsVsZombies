#pragma once
#include "Animation.h"

class Zombie {
protected:
	Sprite sprite;
	float position[2];
	int health;
	float speed;
	float xFactor, yFactor;
	bool exists;

public:
	Zombie() {
		this->xFactor = 185;
		this->yFactor = 32;
	}
	bool getExist() { return this->exists; }
	void changeTexture(Texture& tex) {
		this->sprite = Sprite(tex);
	}

	virtual void move() {}
	virtual void moveDiagonal() {}


	virtual ~Zombie() {}
};