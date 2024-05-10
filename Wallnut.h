#pragma once
#include "NonShooter.h"
#include "Zombie.h"

class Wallnut : public NonShooter {
	bool active;
	Clock moveClock;
	float speed = 0.03125;
public:
	Wallnut(Texture& tex, int columns, float pos[2]) {
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 71, 71));
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->health = 500;
		this->cost = 50;
		this->exists = true;
		this->active = false;
		this->moveClock.restart();
		this->anim = Animation(71, 71, columns);
		this->sprite.setPosition(xFactor + position[0] * 80, yFactor + position[1] * 96);
	}

	void activate(Texture& tex) {
		if (this->active || this->moveClock.getElapsedTime().asMilliseconds() < 50) return;
		this->active = true;
		this->sprite = Sprite(tex);
		this->anim = Animation(71, 71, 38);
		this->anim.setDelay(60.0f);
		this->sprite.setTextureRect(IntRect(0, 0, 71, 71));
		this->moveClock.restart();
	}

	void move(Zombie** zombies, int zombiesArrayIndex) {
		if (!this->active) return;
		if (this->moveClock.getElapsedTime().asMilliseconds() <= 20) {
			return;
		}

		if (this->exists) {
			for (int i = 0; i < zombiesArrayIndex; i++) {
				if (zombies[i]->getExist() && (this->position[1] == zombies[i]->getPosition()[1]) && (this->position[0] == zombies[i]->getPosition()[0] || this->position[0] == zombies[i]->getPosition()[0] - 0.03125 || this->position[0] == zombies[i]->getPosition()[0] - 0.0625 || this->position[0] == zombies[i]->getPosition()[0] - 0.09375 || this->position[0] == zombies[i]->getPosition()[0] - 0.125 || this->position[0] == zombies[i]->getPosition()[0] - 0.15625 || this->position[0] == zombies[i]->getPosition()[0] - 0.1875 || this->position[0] == zombies[i]->getPosition()[0] - 0.21875 || this->position[0] == zombies[i]->getPosition()[0] - 0.25 || this->position[0] == zombies[i]->getPosition()[0] - 0.28125 || this->position[0] == zombies[i]->getPosition()[0] - 0.3125 || this->position[0] == zombies[i]->getPosition()[0] - 0.34375 || this->position[0] == zombies[i]->getPosition()[0] - 0.375 || this->position[0] == zombies[i]->getPosition()[0] - 0.40625 || this->position[0] == zombies[i]->getPosition()[0] - 0.4375 || this->position[0] == zombies[i]->getPosition()[0] - 0.46875 || this->position[0] == zombies[i]->getPosition()[0] - 0.5 || this->position[0] == zombies[i]->getPosition()[0] - 0.53125 || this->position[0] == zombies[i]->getPosition()[0] - 0.5625)) {
					zombies[i]->setHeadFall(true);
					zombies[i]->setExist(false);
					zombies[i]->makeDead();
					this->moveClock.restart();

					return;
				}
			}
			if (this->position[0] <= 8.5) {
				this->position[0] += this->speed;
			}
			else {
				cout << "Walnut died from overspeeding\n";
				this->exists = false;
				this->active = false;
			}
		}
		this->moveClock.restart();
	}

};