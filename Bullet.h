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
		if (!texture.loadFromFile("assets/Bullets/peabullet.png")) cout << "Bullet not found\n";
		sprite.setTexture(texture);
		damage = 1;
		exists = true;
		bulletClock.restart();
	}

	void changeSprite(Texture& tex) {
		this->sprite = Sprite(tex);
	}

	bool getExist() { return exists; }
	void setExist(bool val) { exists = val; }

	void setPosition(float x, float y) {
		this->position[0] = x;
		this->position[1] = y;
	}

	void move() {
		if (bulletClock.getElapsedTime().asMilliseconds() <= 5) {
			return;
		}
		if (exists) {
			if (position[0] <= 8.5) {
				position[0] += 0.0625;
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