#pragma once


#include "Plant.h"
#include "Bullet.h"

class Snowpea : public Plant {
	bool shooting;
	Animation anim;
	Bullet bullet;
	Clock bulletDelayClock;
	Clock startClock;

public:
	Snowpea(Texture& tex, Texture& itex, int columns, float pos[2]) : bullet(pos[0], pos[1]) {
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 71, 71));
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->health = 100;
		shooting = true;
		this->cost = 100;
		this->exists = true;
		this->anim = Animation(71, 71, columns);
		this->sprite.setPosition(xFactor + position[0] * 80, yFactor + position[1] * 96);

		bullet.changeSprite(itex);
		bulletDelayClock.restart();
		startClock.restart();
	}

	void setDelay(float f) {
		anim.setDelay(f);
	}

	void shoot() {
		bullet.move();
		if (bullet.getExist() == false && bulletDelayClock.getElapsedTime().asSeconds() > 2) {
			bullet.setPosition(position[0], position[1]);
			bullet.setExist(true);
			bulletDelayClock.restart();
		}
	}

	void animate() {
		this->anim.animate(this->sprite);
	}

	void draw(RenderWindow& window) {
		if (exists) {
			if (bullet.getExist() == true && startClock.getElapsedTime().asSeconds() > 2) {
				bullet.draw(window);
			}
			window.draw(this->sprite);
		}
	}
};