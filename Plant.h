#ifndef PLANT_H
#define PLANT_H
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <cstdlib>
#include <ctime>

#include "SoundManager.h"
#include "Scoreboard.h"
#include "iostream"
using namespace std;
using namespace sf;

class Zombie;

class Plant {
protected:
	Sprite sprite;
	float position[2];
	int health;
	int cost;
	bool exists;
	float xFactor, yFactor;
	Clock eatClock;
	Animation anim;


public:
	Plant() {
		this->xFactor = 260;
		this->yFactor = 90;
		this->eatClock.restart();
	}
	float* getPosition() {
		return this->position;
	}
	bool getExist() { return this->exists; }
	void setExist(bool val) { this->exists = val; }
	virtual void beEaten() {
		this->health -= 20;
		if (this->health <= 0) this->exists = false;
	}
	Clock& getEatClock() { return this->eatClock; }

	virtual void animate() {
		this->anim.animate(this->sprite);
	}

	virtual bool getDead() { return false; }

	int getPrice() { return this->cost; }

	virtual void setDelay(float f) {}
	virtual void draw(RenderWindow& window) {
		if (this->exists) {
			this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
			window.draw(this->sprite);
		}
	}
	virtual void shoot(Zombie** zombies, int zombiesArrayIndex) {}
	virtual void generateSun() {}
	virtual void explode(Zombie** zombies, int zombiesArrayIndex, SoundManager* SMptr, Scoreboard* scoreboard) {}
	virtual void clickSun(int& sunCount, SoundManager* SMptr) {}
	virtual void moveBullets(Zombie** zombies, int zombiesArrayIndex, Scoreboard* scoreboard) {}
	virtual void restartBulletClock() {}
	virtual void activate(Texture& tex) {}
	virtual void move(Zombie** zombies, int zombiesArrayIndex, Scoreboard* scoreboard) {}

	virtual ~Plant() {}
};

#endif