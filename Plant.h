#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "iostream"
using namespace std;
using namespace sf;

class Plant : public Animation {
protected:
	float position[2];
	int health;
	int cost;

public:
	Plant(string source, int boxX, int boxY, int col, int x, int y, int h, int c) : Animation(source, boxX, boxY, col, x, y) {
		health = h;
		cost = c;
		position[0] = x;
		position[1] = y;
	}
	/*virtual void shoot() = 0;
	virtual void repeatShoot() = 0;
	virtual void explode() = 0;
	virtual void makeSun() = 0;*/
};
