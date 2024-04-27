#pragma once
#include "Shooter.h"
#include "Bullet.h"
#include "Zombie.h"

class Repeater : public Shooter {
	Bullet bullet[2];

public:
	Repeater(Texture& tex, int columns, float pos[2]) {
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 71, 71));
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->health = 100;
		this->shooting = true;
		this->cost = 100;
		this->exists = true;
		this->anim = Animation(71, 71, columns);
		this->sprite.setPosition(xFactor + position[0] * 80, yFactor + position[1] * 96);
		this->bulletDelayClock.restart();

		this->bullet[0].setPosition(this->position[0], this->position[1]);
		this->bullet[1].setPosition(this->position[0] - 0.5, this->position[1]);
		this->startClock.restart();
	}

	void shoot(Zombie** zomb) {
		this->bullet[0].move(zomb);
		this->bullet[1].move(zomb);
		if ((this->bullet[0].getExist() == false || this->bullet[1].getExist() == false) && this->bulletDelayClock.getElapsedTime().asSeconds() > 2) {
			this->bullet[0].setPosition(this->position[0], this->position[1]);
			this->bullet[0].setExist(true);

			this->bullet[1].setPosition(this->position[0] - 0.5, this->position[1]);
			this->bullet[1].setExist(true);
			this->bulletDelayClock.restart();
		}
	}

	void animate() {
		this->anim.animate(this->sprite);
	}

	void draw(RenderWindow& window) {
		if (this->exists) {
			if (this->bullet[0].getExist() && this->startClock.getElapsedTime().asSeconds() > 2) {
				this->bullet[0].draw(window);
			}
			if (this->bullet[1].getExist() && this->startClock.getElapsedTime().asSeconds() > 2) {
				this->bullet[1].draw(window);
			}
			window.draw(this->sprite);
		}
	}
};