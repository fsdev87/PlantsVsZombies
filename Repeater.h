#pragma once
#include "Shooter.h"
#include "Bullet.h"
#include "Zombie.h"

class Repeater : public Shooter {
	Bullet bullet[2];

	SoundBuffer shootBuffer1;
	Sound shootSound1;
public:
	Repeater(Texture& tex, int columns, float pos[2], SoundManager* sm) {
		srand(time(0));
		this->sprite.setTexture(tex);
		this->SMptr = sm;
		this->sprite.setTextureRect(IntRect(0, 0, 71, 71));
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->health = 150;
		this->cost = 200;
		this->exists = true;
		this->anim = Animation(71, 71, columns);
		this->sprite.setPosition(xFactor + position[0] * 80, yFactor + position[1] * 96);
		this->bulletDelayClock.restart();
		this->bullet[0].setPosition(this->position[0], this->position[1]);
		this->bullet[1].setPosition(this->position[0] - 0.5, this->position[1]);
		this->bulletDelay = 1.75 + rand() % 2;
		this->anim.setDelay(80.f);
		this->bullet[0].setHitSound(*(this->SMptr->getSound("hit")));
		this->bullet[1].setHitSound(*(this->SMptr->getSound("hit")));

		shootBuffer1.loadFromFile("assets/sounds/plant/shoot.mp3");
		shootSound1.setBuffer(shootBuffer);
		//this->startClock.restart();
	}

	void saveEverything(ofstream& file) {
		file.write(reinterpret_cast<char*>(&position[0]), sizeof(float));
		file.write(reinterpret_cast<char*>(&position[1]), sizeof(float));

		file.write(reinterpret_cast<char*>(&health), sizeof(int));
		file.write(reinterpret_cast<char*>(&exists), sizeof(bool));
		this->anim.saveEverything(file);

		this->bullet[0].saveEverything(file);
		this->bullet[1].saveEverything(file);

	}

	void readEverything(ifstream& file) {
		file.read(reinterpret_cast<char*>(&position[0]), sizeof(float));
		file.read(reinterpret_cast<char*>(&position[1]), sizeof(float));
		this->sprite.setPosition(xFactor + position[0] * 80, yFactor + position[1] * 96);

		file.read(reinterpret_cast<char*>(&health), sizeof(int));

		file.read(reinterpret_cast<char*>(&exists), sizeof(bool));

		this->anim.readEverything(file);

		this->sprite.setTextureRect(IntRect(this->anim.getFrame() * 71, 0, 71, 71));

		this->bullet[0].readEverything(file);
		this->bullet[1].readEverything(file);

	}

	void shoot(Zombie** zomb, int zombiesArrayIndex) {
		/*if (this->startClock.getElapsedTime().asSeconds() < 2) {
			this->bulletDelayClock.restart();
			return;
		}*/
		if (this->exists) {
			/*this->bullet[0].move(zomb, zombiesArrayIndex);
			this->bullet[1].move(zomb, zombiesArrayIndex);*/
			if ((this->bullet[0].getExist() == false || this->bullet[1].getExist() == false) && this->bulletDelayClock.getElapsedTime().asSeconds() > bulletDelay) {
				this->bullet[0].setPosition(this->position[0], this->position[1]);
				this->bullet[0].setExist(true);
				this->shootSound.play();
				Clock* delay = new Clock;
				this->bullet[1].setPosition(this->position[0] - 0.5, this->position[1]);
				this->bullet[1].setExist(true);
				this->bulletDelayClock.restart();
				if (delay->getElapsedTime().asMilliseconds() > 5) {
					this->shootSound1.play();
					delete delay;
				}
			}
		}
	}

	void moveBullets(Zombie** zombies, int zombiesArrayIndex, Scoreboard* scoreboard) {
		if (this->exists) {
			this->bullet[0].move(zombies, zombiesArrayIndex, false, scoreboard);
			this->bullet[1].move(zombies, zombiesArrayIndex, false, scoreboard);
		}
	}

	void restartBulletClock() {
		this->bulletDelayClock.restart();
	}

	void draw(RenderWindow& window) {
		this->bullet[0].draw(window);
		this->bullet[1].draw(window);
		if (this->exists) {
			window.draw(this->sprite);
		}
	}
};