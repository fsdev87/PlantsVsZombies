#pragma once
#include "Animation.h"


class Zombie {
protected:
	Sprite sprite;
	float position[2];
	int health;
	float xFactor, yFactor;
	bool exists;

public:
	Zombie() {
		this->xFactor = 185;
		this->yFactor = 32;
	}
};