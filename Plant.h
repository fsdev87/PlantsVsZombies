#ifndef PLANT_H
#define PLANT_H
#include <SFML/Graphics.hpp>
#include "Animation.h"

#include "iostream"
using namespace std;
using namespace sf;

class Zombie;

class Plant {
protected:
	Sprite sprite;
	float position[2];
	int health;
	int cost;
	bool exists;
	float xFactor, yFactor;
	Clock eatClock;
	Animation anim;

public:
	Plant() {
		this->xFactor = 260;
		this->yFactor = 90;
		this->eatClock.restart();
	}
	float* getPosition() {
		return this->position;
	}
	bool getExist() { return this->exists; }
	void setExist(bool val) { this->exists = val; }
	void beEaten() {
		this->health -= 20;
		if (this->health <= 0) this->exists = false;
	}
	Clock& getEatClock() { return this->eatClock; }

	virtual void animate() {
		this->anim.animate(this->sprite);
	}

	virtual void setDelay(float f) {}
	virtual void draw(RenderWindow& window) {
		if (this->exists)
			window.draw(this->sprite);
	}
	virtual void shoot(Zombie** zomb, int zombiesArrayIndex) {}
	virtual void generateSun() {}
	virtual void explode() {}

	virtual ~Plant() {}
};

#endif