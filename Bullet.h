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
<<<<<<< HEAD
			sprite.setPosition(305 + position[0] * 80, 95 + position[1] * 96);
=======
			sprite.setPosition(310 + position[0] * 80, 95 + position[1] * 96);
>>>>>>> b5028d43d5995e87d64a3ddd8feb6814b0ce170b
			window.draw(sprite);
		}
	}
	Sprite& getSprite() { return sprite; }
};
