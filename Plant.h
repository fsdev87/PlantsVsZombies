#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Animation.h"
using namespace sf;

class Plant : public Animation {
protected:
	float position[2];
	int health;
	int cost;

public:
	virtual void shoot() = 0;
	virtual void repeatShoot() = 0;
	virtual void explode() = 0;
	virtual void makeSun() = 0;
};

class Bullet {
	Texture texture;
	Sprite sprite;
	float position[2];
	int damage;
	Clock bulletClock;
	bool exists;

public:
	Bullet(int x = 0, int y = 0) {
		position[0] = x, position[1] = y;
		texture.loadFromFile("assets/Bullets/PeaNormal/pea.png");
		sprite.setTexture(texture);
		damage = 1;
		exists = true;
		bulletClock.restart();
	}
	void move() {
		if (bulletClock.getElapsedTime().asMilliseconds() <= 8) {
			return;
		}
		if (exists && position[0] <= 10) {
			position[0] += 0.125;
		}
		else {
			exists = false;
		}
		bulletClock.restart();
	}
	void draw(RenderWindow& window) {
		if (exists) {
			sprite.setPosition(310 + position[0] * 80, 110 + position[1] * 96);
			window.draw(sprite);
		}
	}
};

class Peashooter : public Plant {
private:


};