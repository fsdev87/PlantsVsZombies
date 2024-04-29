#pragma once
#include "Shooter.h"
#include "Bullet.h"
#include "Zombie.h"

class Snowpea : public Shooter {
	Bullet bullet;

public:
	Snowpea(Texture& tex, Texture& itex, int columns, float pos[2]) : bullet(pos[0] - 0.15, pos[1]) {
		srand(time(0));
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 71, 71));
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->health = 100;
		this->cost = 175;
		this->exists = true;
		this->anim = Animation(71, 71, columns);
		this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
		this->bullet.changeSprite(itex);
		this->bulletDelayClock.restart();
		this->bulletDelay = 2 + rand() % 3;
		//this->startClock.restart();
	}


	void shoot(Zombie** zomb, int zombiesArrayIndex) {
		/*if (this->startClock.getElapsedTime().asSeconds() < 2) {
			this->bulletDelayClock.restart();
			return;
		}*/
		if (this->exists) {
			//this->bullet.move(zomb, zombiesArrayIndex);
			if (this->bullet.getExist() == false && this->bulletDelayClock.getElapsedTime().asSeconds() > bulletDelay) {
				this->bullet.setPosition(position[0], position[1]);
				this->bullet.setExist(true);
				this->bulletDelayClock.restart();
			}
		}
	}

	void moveBullets(Zombie** zombies, int zombiesArrayIndex) {
		if (this->exists) {
			this->bullet.move(zombies, zombiesArrayIndex);
		}
	}

	void restartBulletClock() {
		this->bulletDelayClock.restart();
	}

	void draw(RenderWindow& window) {
		if (this->exists) {
			window.draw(this->sprite);
		}
		if (this->startClock.getElapsedTime().asSeconds() > 2) {
			this->bullet.draw(window);
		}
	}
};