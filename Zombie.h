#ifndef ZOMBIES_H
#define ZOMBIES_H
#include "Animation.h"
#include "TextureManager.h"
#include "Plant.h"

class Zombie {
protected:
	Sprite sprite;
	Animation anim;
	float position[2];
	int health;
	float speed;
	float xFactor, yFactor;
	bool exists;
	Clock moveClock;
	float moveDelay = 250;
	TextureManager* TMptr;
	bool blocked = false;
	int eatIndex = -1;

	Sprite headSprite;
	Animation headAnim;
	Clock headClock;
	bool headFall = false;
	bool headOnceFell = false;

	float limit;


	string state;
	bool flicker = false;
	Clock flickerClock;

	bool ashes = false;
	Clock ashesClock;

	bool dead = false;
	Clock deadClock;

	SoundManager* SMptr;


public:
	Zombie() {
		this->xFactor = 185;
		this->yFactor = 32;
		this->state = "walk";
	}
	/*float getSpeed() { return this->speed; }
	void setSpeed(float val) { this->speed = val; }*/

	void setAnimDelay(float val) { this->anim.setDelay(val); }
	void setMoveDelay(float val) { this->moveDelay = val; }
	float* getPosition() {
		return this->position;
	}
	bool getExist() { return this->exists; }

	bool getDead() { return this->dead; }
	virtual float getLimit() { return this->limit; }

	void changeTexture(Texture& tex, int frame = 0, int columns = 21) {
		this->sprite = Sprite(tex);
		this->anim = Animation(166, 144, columns);
		this->anim.setFrame(frame);
	}

	void animate() {
		this->anim.animate(this->sprite);
		if (this->headFall) {
			if (this->headAnim.getFrame() < this->headAnim.getColumns()) {
				this->headAnim.animate(this->headSprite);
			}
			if (this->headClock.getElapsedTime().asSeconds() >= 1.205) {
				this->headFall = false;
				this->headOnceFell = true;
			}
		}
	}

	void setFlicker(bool value) {
		/*if (this->flicker != true) {
			this->SMptr->getSound("hit")->setPlayingOffset(sf::Time(sf::seconds(0.70)));
			this->SMptr->getSound("hit")->setVolume(50.0f);
			this->SMptr->playSound("hit");
		}*/

		this->flicker = value, this->flickerClock.restart();
	}

	void setHeadFall(bool val) {
		this->headFall = val;
		this->headOnceFell = val;
		this->headClock.restart();
		this->headSprite.setPosition(this->xFactor + 50 + this->position[0] * 80, this->yFactor - 10 + this->position[1] * 96);
	}

	bool getHeadFall() {
		return this->headOnceFell;
	}

	virtual void spawnZombie(Zombie** zombies, int& zombiesArrayIndex, const int maxZombies) {}

	// changes sprite texture to ashes
	// restarts ashes clock
	void setAshes(bool value) {
		this->changeTexture((*TMptr)["spritesheet-zombieAshes"], 0, 20);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->ashes = value, this->ashesClock.restart();
	}

	// should be specific for each zombie
	void handleFlicker() {
		if (!this->exists) return;

		if (this->flicker) {
			// Turn off flicker after 150ms and reset appropriate texture
			if (flickerClock.getElapsedTime().asMilliseconds() > 150) {
				this->flicker = false;
				// Reset texture
				this->sprite.setColor(Color(255, 255, 255, 255));
			}
			else {
				// Set DIM texture
				this->sprite.setColor(Color(255, 255, 255, 255 * 0.6));
			}

		}
	}

	void draw(RenderWindow& window) {
		handleFlicker();


		if (this->exists) {
			// Draw
			this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
			window.draw(this->sprite);
		}

		handleAshes(window);

		handleDeath(window);
		if (this->headFall) {
			window.draw(this->headSprite);
		}
	}

	virtual void makeDead() {
		if (this->exists == false && this->ashes != true) {
			this->changeTexture((*TMptr)["spritesheet-zombieDeath"], 0, 10);
			this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			this->dead = true, this->deadClock.restart();
			this->SMptr->playSound("zombie-fall");
		}
	}

	virtual void handleDeath(RenderWindow& window) {
		if (!this->exists && this->dead) {
			if (this->deadClock.getElapsedTime().asSeconds() > 1.05) {
				this->dead = false;
			}
			this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
			window.draw(this->sprite);
		}
	}

	// same for each zombie
	void handleAshes(RenderWindow& window) {
		// show ashes only when this->exists = false i.e zombie is dead
		if (!this->exists && this->ashes) {
			if (this->ashesClock.getElapsedTime().asSeconds() > 2.05) {
				// there are 20 frames, each frame takes 100ms delay, added 0.05 as padding
				// set ashes to false after 2 seconds so nothing is drawn afterwards
				this->ashes = false;
			}
			this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
			window.draw(this->sprite);
		}
	}

	void setExist(bool val) {
		this->exists = val;
	}



	int getHealth() { return this->health; }

	void reduceHealth(int damage) {
		this->health -= damage;
	}

	// should be specific for each zombie
	virtual void move(Plant** plants, int plantsArrayIndex) = 0;
	//if (this->exists == false) return;
	/*if (this->flicker) {
	//	this->moveClock.restart();
	//	return;
	//}*/
	//if (this->moveClock.getElapsedTime().asMilliseconds() < 250) return;
	//if (this->blocked) {
	//	if (this->eatIndex != -1) {
	//		this->state = "eat";
	//		eat(plants[this->eatIndex]);
	//	}
	//	return;
	//}

	//this->moveClock.restart();
	//this->position[0] -= this->speed;
	//this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);


	//for (int i = 0; i < plantsArrayIndex; i++) {
	//	if (plants[i]->getExist()) {
	//		if (plants[i]->getPosition()[1] == this->position[1]) {
	//			float dt = plants[i]->getPosition()[0] - this->position[0];
	//			if (dt <= 0 && dt >= -0.6875) {
	//				this->blocked = true;
	//				this->changeTexture((*TMptr)["spritesheet-nZombEat"]);
	//				this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
	//				this->eatIndex = i;
	//				return;
	//			}
	//		}
	//	}
	//}

// should be specific for each zombie
	virtual void eat(Plant* plant) = 0;
	/*if (plant->getExist()) {
		if (plant->getEatClock().getElapsedTime().asMilliseconds() > 500) {
			plant->beEaten();
			plant->getEatClock().restart();
		}
	}
	else {
		this->blocked = false;
		this->state = "walk";
		this->changeTexture((*(this->TMptr))["spritesheet-nZombWalk"]);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->eatIndex = -1;
	}*/




	virtual ~Zombie() {}
};

#endif