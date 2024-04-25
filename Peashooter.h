#pragma once
#include "Plant.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Peashooter : public Plant {
	Bullet bullet;
	bool shootBullet = false;
public:
	Peashooter(string source, int boxX, int boxY, int col, int x, int y, int h, int c) : bullet(x, y), Plant(source, boxX, boxY, col, x, y, h, c) {}
	void setShoot() {
		shootBullet = true;
	}
	void shoot() {
		if (shootBullet) {
			bullet.move();
		}
	}
	void draw(RenderWindow& window) {
		bullet.draw(window);
		window.draw(sprite);
	}
};