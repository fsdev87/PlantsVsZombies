#pragma once
#include "Zombie.h"

// 88 x 140
// 11 cols
class FlyingZombie : public Zombie {
public:
	FlyingZombie(Texture& tex, int columns, float pos[2], TextureManager* TM, SoundManager* SM) {
		this->SMptr = SM;
		this->type = "flying";
		this->TMptr = TM;
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 88, 140));
		this->speed = 0.0625;
		this->health = 120;
		this->exists = true;
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->anim = Animation(88, 140, columns);
		this->moveClock.restart();
		this->anim.setDelay(50);
		// head
		this->headSprite.setTexture(this->TMptr->getTexture("spritesheet-head"));
		this->headSprite.setTextureRect(IntRect(0, 0, 150, 186));
		this->headAnim = Animation(150, 186, 12);
	}

	void saveEverything(ofstream& file) {
		file.write(reinterpret_cast<char*>(&position[0]), sizeof(float));
		file.write(reinterpret_cast<char*>(&position[1]), sizeof(float));
		file.write(reinterpret_cast<char*>(&health), sizeof(int));
		file.write(reinterpret_cast<char*>(&exists), sizeof(bool));
		this->anim.saveEverything(file);

		this->headAnim.saveEverything(file);

		file.write(reinterpret_cast<char*>(&speed), sizeof(float));
		file.write(reinterpret_cast<char*>(&moveDelay), sizeof(float));
		file.write(reinterpret_cast<char*>(&limit), sizeof(float));

		file.write(reinterpret_cast<char*>(&state), sizeof(string));

		file.write(reinterpret_cast<char*>(&eatIndex), sizeof(int));

		file.write(reinterpret_cast<char*>(&flicker), sizeof(bool));
		file.write(reinterpret_cast<char*>(&ashes), sizeof(bool));
		file.write(reinterpret_cast<char*>(&dead), sizeof(bool));
		file.write(reinterpret_cast<char*>(&blocked), sizeof(bool));
		file.write(reinterpret_cast<char*>(&headFall), sizeof(bool));
		file.write(reinterpret_cast<char*>(&headOnceFell), sizeof(bool));

	}

	void readEverything(ifstream& file) {
		file.read(reinterpret_cast<char*>(&position[0]), sizeof(float));
		file.read(reinterpret_cast<char*>(&position[1]), sizeof(float));
		file.read(reinterpret_cast<char*>(&health), sizeof(int));
		file.read(reinterpret_cast<char*>(&exists), sizeof(bool));
		this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
		this->headSprite.setPosition(this->xFactor + 50 + this->position[0] * 80, this->yFactor - 10 + this->position[1] * 96);


		this->anim.readEverything(file);

		this->headAnim.readEverything(file);

		file.read(reinterpret_cast<char*>(&speed), sizeof(float));
		file.read(reinterpret_cast<char*>(&moveDelay), sizeof(float));
		file.read(reinterpret_cast<char*>(&limit), sizeof(float));

		file.read(reinterpret_cast<char*>(&state), sizeof(string));

		file.read(reinterpret_cast<char*>(&eatIndex), sizeof(int));

		file.read(reinterpret_cast<char*>(&flicker), sizeof(bool));
		file.read(reinterpret_cast<char*>(&ashes), sizeof(bool));
		file.read(reinterpret_cast<char*>(&dead), sizeof(bool));
		file.read(reinterpret_cast<char*>(&blocked), sizeof(bool));
		file.read(reinterpret_cast<char*>(&headFall), sizeof(bool));
		file.read(reinterpret_cast<char*>(&headOnceFell), sizeof(bool));

		if (this->exists) {
			this->sprite = Sprite(this->TMptr->getTexture("flying-zombie"));
			this->sprite.setTextureRect(IntRect(this->anim.getFrame() * 88, 0, 88, 140));
		}

		if (this->dead) {
			this->sprite = Sprite(this->TMptr->getTexture("spritesheet-headLessDeath"));
			this->sprite.setTextureRect(IntRect(this->anim.getFrame() * 166, 0, 166, 144));
		}
		if (this->ashes) {
			this->sprite = Sprite(this->TMptr->getTexture("spritesheet-zombieAshes"));
			this->sprite.setTextureRect(IntRect(this->anim.getFrame() * 166, 0, 166, 144));
		}
	}

	virtual bool isFlying() { return true; }

	virtual void setAshes(bool value) {
		this->changeTexture(this->TMptr->getTexture("spritesheet-zombieAshes"), 0, 20);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->ashes = value, this->ashesClock.restart();
		this->xFactor -= 40;
	}

	virtual void makeDead() {
		if (this->exists == false && this->ashes != true) {
			this->changeTexture(this->TMptr->getTexture("spritesheet-zombieDeath"), 0, 10);
			this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			this->dead = true, this->deadClock.restart();
			this->SMptr->playSound("zombie-fall");
			this->xFactor -= 40;
		}
	}

	void move(Plant** plants, int plantsArrayIndex) {
		if (this->exists == false) return;
		if (this->moveClock.getElapsedTime().asMilliseconds() < this->moveDelay) return;
		this->moveClock.restart();

		this->position[0] -= this->speed;
		this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
	}

	virtual void draw(RenderWindow& window) {

		if (this->exists) {
			// Draw
			if (this->ashes) {
				this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
			}
			else {
				this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor - 40 + this->position[1] * 96);
			}

			window.draw(this->sprite);
		}

		handleAshes(window);

		handleDeath(window);
		if (this->headFall) {
			window.draw(this->headSprite);
		}
	}
};