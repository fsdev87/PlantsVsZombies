#pragma once
#include "Zombie.h"

class NormalZombie : public Zombie {
public:
	NormalZombie(Texture& tex, int columns, float pos[2], TextureManager* TM, SoundManager* SM) {
		this->SMptr = SM;
		this->TMptr = TM;
		this->type = "normal";
		this->sprite.setTexture(tex);
		this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
		this->speed = 0.0625;
		this->health = 120;
		this->exists = true;
		this->position[0] = pos[0], this->position[1] = pos[1];
		this->anim = Animation(166, 144, columns);
		this->moveClock.restart();
		this->limit = 20;
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


	}

	void checkHealth() {
		if (this->exists) {
			if (this->health == this->limit) {
				setHeadFall(true);
				if (this->state == "walk") {
					changeTexture(this->TMptr->getTexture("spritesheet-headLessWalk"), 0, 18);
				}
				else {
					changeTexture(this->TMptr->getTexture("spritesheet-headLessEat"), 0, 11);
				}
				this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			}
			else if (this->health == 0) {
				this->exists = false;
				makeDead();
			}
		}
	}

	void move(Plant** plants, int plantsArrayIndex) {
		if (this->exists == false) return;


		if (this->moveClock.getElapsedTime().asMilliseconds() < this->moveDelay) return;
		handleFlicker();

		if (this->blocked) {
			if (this->eatIndex != -1) {
				this->state = "eat";
				eat(plants[this->eatIndex]);
			}
			return;
		}

		this->moveClock.restart();
		this->position[0] -= this->speed;
		this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);



		for (int i = 0; i < plantsArrayIndex; i++) {
			if (plants[i]->getExist()) {
				float* plantPos = plants[i]->getPosition();

				if (plantPos[1] == this->position[1]) {
					float dt = plantPos[0] - this->position[0];
					if (dt <= 0 && dt >= -0.6875) {
						this->blocked = true;

						if (this->health > this->limit) {
							this->changeTexture(this->TMptr->getTexture("spritesheet-nZombEat"), 0, 21);
						}
						else {
							this->changeTexture(this->TMptr->getTexture("spritesheet-headLessEat"), 0, 11);
						}

						this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
						this->eatIndex = i;
						return;
					}
				}
			}
		}
	}

	void eat(Plant* plant) {
		if (plant->getExist()) {
			if (plant->getEatClock().getElapsedTime().asMilliseconds() > 500) {
				plant->beEaten();
				plant->getEatClock().restart();

			}
		}
		else {
			this->blocked = false;

			this->state = "walk";

			if (this->health > this->limit) {
				this->changeTexture(this->TMptr->getTexture("spritesheet-nZombWalk"), 0, 22);
			}
			else {
				this->changeTexture(this->TMptr->getTexture("spritesheet-headLessWalk"), 0, 18);
			}

			this->sprite.setTextureRect(IntRect(0, 0, 166, 144));
			this->eatIndex = -1;
		}
	}
};