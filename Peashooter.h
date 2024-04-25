#pragma once
#include "Plant.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Peashooter : public Plant {
	Bullet bullet;



public:
	Peashooter(string source, int boxX, int boxY, int col, int x, int y) : bullet(x, y), Plant(source, boxX, boxY, col, x, y) {
		this->health = 100;
		this->cost = 100;
		this->exists = true;
	}

	void shoot() {
		bullet.move();
	}

	void draw(RenderWindow& window) {
		bullet.draw(window);
		window.draw(sprite);
	}
};