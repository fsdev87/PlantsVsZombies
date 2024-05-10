#include "ZombieFactory.h"

using namespace std;
using namespace sf;


ZombieFactory::ZombieFactory(TextureManager* tm, SoundManager* SMptr) {
	this->SMptr = SMptr;
	this->zombies = new Zombie * [this->maxZombies] { nullptr };
	this->TMptr = tm;
	this->deadIndex = -1;
	this->zombiesArrayIndex = 0;
	this->spawnClock.restart();
}

void ZombieFactory::getZombieDeadIndex() {
	for (int i = 0; i < this->zombiesArrayIndex; i++) {
		if (this->zombies[i]->getExist() == false) {
			this->deadIndex = i;
			cout << "Found dead index";
			return;
		}
	}
	this->deadIndex = -1;
}

void ZombieFactory::spawnZombie() {
	if (this->spawnClock.getElapsedTime().asSeconds() < 6) return;

	this->pos[1] = rand() % 5;

	if (this->zombiesArrayIndex < this->maxZombies) {

		int zombieType = rand() % 3;

		switch (zombieType) {
		case 0:
			this->zombies[this->zombiesArrayIndex] = new NormalZombie(this->TMptr->getTexture("spritesheet-nZombWalk"), 22, this->pos, this->TMptr, this->SMptr);
			break;
		case 1:
			this->zombies[this->zombiesArrayIndex] = new FootballZombie(this->TMptr->getTexture("football-walk"), 11, this->pos, this->TMptr, this->SMptr);
			break;
		case 2:
			this->zombies[this->zombiesArrayIndex] = new DancingZombie(this->TMptr->getTexture("dancing-walk-1"), 21, this->pos, this->TMptr, this->SMptr);
		}

		this->zombiesArrayIndex++;
	}
	else {
		getZombieDeadIndex();
		if (this->deadIndex != -1) {
			cout << "dead index is not -1\n";
			delete[] this->zombies[this->deadIndex];
			int zombieType = rand() % 3;
			switch (zombieType) {
			case 0:
				this->zombies[this->zombiesArrayIndex] = new NormalZombie(this->TMptr->getTexture("spritesheet-nZombWalk"), 22, this->pos, this->TMptr, this->SMptr);
				break;
			case 1:
				this->zombies[this->zombiesArrayIndex] = new FootballZombie(this->TMptr->getTexture("football-walk"), 11, this->pos, this->TMptr, this->SMptr);
				break;
			case 2:
				this->zombies[this->zombiesArrayIndex] = new DancingZombie(this->TMptr->getTexture("dancing-walk-1"), 21, this->pos, this->TMptr, this->SMptr);
			}
		}
		else {
			cout << "Max zombies reached in spawnZombie function" << endl;
		}
	}

	this->spawnClock.restart();
}

Zombie** ZombieFactory::getZombies() { return this->zombies; }
int& ZombieFactory::getZombiesArrayIndex() { return this->zombiesArrayIndex; }

void ZombieFactory::updateEverything(Plant** plants, int plantsArrayIndex, LawnMower** lawnmowers, Life* lives) {
	for (int i = 0; i < this->zombiesArrayIndex; i++) {
		this->zombies[i]->animate();
		this->zombies[i]->move(plants, plantsArrayIndex);

		this->zombies[i]->spawnZombie(this->zombies, this->zombiesArrayIndex, maxZombies);

		float* position = zombies[i]->getPosition();
		if (position[0] <= -0.5 && position[0] >= -1) {
			if (lawnmowers[(int)position[1]]->getExists() == true) {
				lawnmowers[(int)position[1]]->activate();
			}
			else if (position[0] <= -1) {
				zombies[i]->setExist(false);
				lives->decrementLives();
			}
		}
	}
	spawnZombie();
}

void ZombieFactory::draw(RenderWindow& window) {
	for (int i = 0; i < this->zombiesArrayIndex; i++) {
		this->zombies[i]->draw(window);
	}
}