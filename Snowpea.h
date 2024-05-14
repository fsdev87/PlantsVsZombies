#pragma once
#include "Shooter.h"
#include "Bullet.h"
#include "Zombie.h"

class Snowpea : public Shooter {
	Bullet bullet;

public:
	Snowpea(Texture& tex, Texture& itex, int columns, float pos[2], SoundManager* sm) : bullet(pos[0] - 0.15, pos[1]) {
		srand(time(0));
		this->sprite.setTexture(tex);
		this->SMptr = sm;
		this->sprite.setTextureRect(IntRect(0, 0, 71, 71));
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->health = 100;
		this->cost = 175;
		this->exists = true;
		this->anim = Animation(71, 71, columns);
		this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
		this->bullet.changeSprite(itex);
		this->bulletDelayClock.restart();
		this->bulletDelay = 1.75 + rand() % 2;
		this->anim.setDelay(80.f);
		this->bullet.setHitSound(*(this->SMptr->getSound("hit")));
		//this->startClock.restart();
	}

	void saveEverything(ofstream& file) {
		file.write(reinterpret_cast<char*>(&position[0]), sizeof(float));
		file.write(reinterpret_cast<char*>(&position[1]), sizeof(float));
		file.write(reinterpret_cast<char*>(&health), sizeof(int));
		file.write(reinterpret_cast<char*>(&exists), sizeof(bool));
		this->anim.saveEverything(file);

		this->bullet.saveEverything(file);

	}

	void readEverything(ifstream& file) {
		file.read(reinterpret_cast<char*>(&position[0]), sizeof(float));
		file.read(reinterpret_cast<char*>(&position[1]), sizeof(float));
		this->sprite.setPosition(xFactor + position[0] * 80, yFactor + position[1] * 96);

		file.read(reinterpret_cast<char*>(&health), sizeof(int));

		file.read(reinterpret_cast<char*>(&exists), sizeof(bool));

		this->anim.readEverything(file);

		this->sprite.setTextureRect(IntRect(this->anim.getFrame() * 71, 0, 71, 71));

		this->bullet.readEverything(file);

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

	void moveBullets(Zombie** zombies, int zombiesArrayIndex, Scoreboard* scoreboard) {
		if (this->exists) {
			this->bullet.move(zombies, zombiesArrayIndex, true, scoreboard);
		}
	}

	void restartBulletClock() {
		this->bulletDelayClock.restart();
	}

	void draw(RenderWindow& window) {
		this->bullet.draw(window);
		if (this->exists) {
			window.draw(this->sprite);
		}
	}
};