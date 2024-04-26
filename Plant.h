#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "iostream"
using namespace std;
using namespace sf;

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
	virtual void setDelay(float f) = 0;
	virtual void animate() = 0;
	virtual void shoot() = 0;
	virtual void draw(RenderWindow& window) = 0;
	/*virtual void shoot() = 0;
	virtual void repeatShoot() = 0;
	virtual void explode() = 0;
	virtual void makeSun() = 0;*/
};
