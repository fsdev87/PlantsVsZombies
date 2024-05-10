#pragma once
#include "TextureManager.h"
#include "Animation.h"
#include "Zombie.h"

class LawnMower {
private:
	TextureManager* TMptr;
	Sprite sprite;
	float position[2];
	Clock moveClock;
	bool exists;
	bool active;
	float speed;
	Animation anim;
	float xFactor = 260, yFactor = 90;

public:
	LawnMower(TextureManager* TM, float pos[2]) : TMptr(TM) {
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->sprite.setTexture(this->TMptr->getTexture("image-lawnmowerIdle"));
		this->anim = Animation(71, 71, 13);
		this->anim.setDelay(120.f);
		this->active = false;
		this->exists = true;
		this->speed = 0.03125;
		this->moveClock.restart();
	}
	bool getExists() { return this->exists; }

	void activate() {
		if (this->active) return;
		this->active = true;
		this->sprite = Sprite(this->TMptr->getTexture("spritesheet-lawnmower"));
		this->sprite.setTextureRect(IntRect(0, 0, 71, 71));
		this->anim.setFrame(0);
	}

	void animate() {
		if (!this->active || !this->exists) return;
		this->anim.animate(this->sprite);
		//cout << "Animating" << endl;
	}

	void move(Zombie** zombies, int zombiesArrayIndex) {
		if (!this->active) return;
		if (moveClock.getElapsedTime().asMilliseconds() <= 5) {
			return;
		}

		if (this->exists) {
			for (int i = 0; i < zombiesArrayIndex; i++) {
				if (zombies[i]->getExist() && (this->position[1] == zombies[i]->getPosition()[1]) && (this->position[0] == zombies[i]->getPosition()[0] || this->position[0] == zombies[i]->getPosition()[0] - 0.03125 || this->position[0] == zombies[i]->getPosition()[0] - 0.0625 || this->position[0] == zombies[i]->getPosition()[0] - 0.09375 || this->position[0] == zombies[i]->getPosition()[0] - 0.125 || this->position[0] == zombies[i]->getPosition()[0] - 0.15625 || this->position[0] == zombies[i]->getPosition()[0] - 0.1875 || this->position[0] == zombies[i]->getPosition()[0] - 0.21875 || this->position[0] == zombies[i]->getPosition()[0] - 0.25 || this->position[0] == zombies[i]->getPosition()[0] - 0.28125 || this->position[0] == zombies[i]->getPosition()[0] - 0.3125 || this->position[0] == zombies[i]->getPosition()[0] - 0.34375 || this->position[0] == zombies[i]->getPosition()[0] - 0.375 || this->position[0] == zombies[i]->getPosition()[0] - 0.40625 || this->position[0] == zombies[i]->getPosition()[0] - 0.4375 || this->position[0] == zombies[i]->getPosition()[0] - 0.46875 || this->position[0] == zombies[i]->getPosition()[0] - 0.5 || this->position[0] == zombies[i]->getPosition()[0] - 0.53125 || this->position[0] == zombies[i]->getPosition()[0] - 0.5625)) {
					if (!zombies[i]->getHeadFall()) zombies[i]->setHeadFall(true);
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
				this->exists = false;
				this->active = false;
			}
		}
		this->moveClock.restart();
	}
	void draw(RenderWindow& window) {
		if (this->exists) {
			this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
			window.draw(this->sprite);
		}
	}
};