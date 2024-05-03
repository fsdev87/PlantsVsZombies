#pragma once
#include "Shooter.h"
#include "Bullet.h"
#include "Zombie.h"

class Threepeater : public Shooter {
	Bullet bullet[3];

public:
	Threepeater(Texture& tex, int columns, float pos[2]) {
		srand(time(0));
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 73, 80));
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->health = 150;
		this->cost = 325;
		this->exists = true;
		this->anim = Animation(73, 80, columns);
		this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
		this->bulletDelayClock.restart();
		this->bullet[0].setPosition(this->position[0], this->position[1]);
		this->bullet[1].setPosition(this->position[0] - 0.75, this->position[1]);
		this->bullet[2].setPosition(this->position[0] - 1, this->position[1]);
		this->bulletDelay = 2 + rand() % 2;
		this->anim.setDelay(105.f);
		//this->startClock.restart();
	}

	void shoot(Zombie** zombies, int zombiesArrayIndex) {
		if (this->exists) {
			if ((this->bullet[0].getExist() == false || this->bullet[1].getExist() == false || this->bullet[2].getExist() == false) && this->bulletDelayClock.getElapsedTime().asSeconds() > bulletDelay) {
				this->bullet[0].setPosition(this->position[0], this->position[1]);
				this->bullet[0].setExist(true);


				this->bullet[1].setPosition(this->position[0] - 0.5, this->position[1]);
				this->bullet[1].setExist(true);

				this->bullet[2].setPosition(this->position[0] - 0.75, this->position[1]);
				this->bullet[2].setExist(true);

				this->bulletDelayClock.restart();
			}
		}
	}

	void moveBullets(Zombie** zombies, int zombiesArrayIndex) {
		if (this->exists) {
			this->bullet[0].move(zombies, zombiesArrayIndex);
			this->bullet[1].move(zombies, zombiesArrayIndex);
			this->bullet[2].move(zombies, zombiesArrayIndex);
		}
	}

	void restartBulletClock() {
		this->bulletDelayClock.restart();
	}

	void draw(RenderWindow& window) {
		this->bullet[0].draw(window);
		this->bullet[1].draw(window);
		this->bullet[2].draw(window);
		if (this->exists) {
			window.draw(this->sprite);
		}
	}
};