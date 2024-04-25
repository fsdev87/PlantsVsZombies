#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Animation.h"
using namespace sf;

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

	bool& getExist() { return exists; }

	void setPosition(float position[2]) {
		this->position[0] = position[0];
		this->position[1] = position[1];
	}

	void move() {
		if (bulletClock.getElapsedTime().asMilliseconds() <= 8) {
			return;
		}
		if (exists) {
			if (position[0] <= 8) {
				position[0] += 0.125;
			}
			else {
				exists = false;
			}
		}
		bulletClock.restart();
	}

	void draw(RenderWindow& window) {
		if (exists) {
			sprite.setPosition(305 + position[0] * 80, 95 + position[1] * 96);
			window.draw(sprite);
		}
	}
};
