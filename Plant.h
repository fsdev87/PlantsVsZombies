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
	bool exists;

public:
	Plant(string source, int boxX, int boxY, int col, int x, int y) : Animation(source, boxX, boxY, col, x, y, 260, 90) {

		position[0] = x;
		position[1] = y;
	}
	/*virtual void shoot() = 0;
	virtual void repeatShoot() = 0;
	virtual void explode() = 0;
	virtual void makeSun() = 0;*/
};
