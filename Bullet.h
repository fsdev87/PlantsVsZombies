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
		this->position[0] = x, this->position[1] = y;
		if (!texture.loadFromFile("assets/Bullets/peabullet.png")) cout << "Bullet not found\n";
		this->sprite.setTexture(this->texture);
		this->damage = 1;
		this->exists = true;
		this->bulletClock.restart();
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
			if (this->position[0] <= 8.5) {
				this->position[0] += 0.0625;
			}
			else {
				this->exists = false;
			}
		}
		this->bulletClock.restart();
	}

	void draw(RenderWindow& window) {
		if (this->exists) {
			this->sprite.setPosition(305 + position[0] * 80, 95 + position[1] * 96);
			window.draw(sprite);
		}
	}
};