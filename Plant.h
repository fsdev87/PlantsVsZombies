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

public:
	Plant() {
		this->xFactor = 260;
		this->yFactor = 90;
	}
	float* getPosition() {
		return this->position;
	}
	bool getExist() { return this->exists; }
	void setExist(bool val) { this->exists = val; }
	virtual void setDelay(float f) {}
	virtual void animate() = 0;
	virtual void draw(RenderWindow& window) {}
	virtual void shoot(Zombie** zomb) {}
	virtual void generateSun() {}
	virtual void explode() {}
	virtual ~Plant() {}
};

#endif