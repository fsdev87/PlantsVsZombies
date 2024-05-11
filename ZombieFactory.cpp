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

void ZombieFactory::reset() {
	for (int i = 0; i < this->zombiesArrayIndex; i++) {
		if (this->zombies[i]) {
			delete[] zombies[i];
		}
		this->zombies[i] = nullptr;
	}

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

void ZombieFactory::spawnZombie(int round) {
	if (this->spawnClock.getElapsedTime().asSeconds() < 6) return;

	if (round != 1) {
		this->pos[1] = rand() % 5;
	}
	else {
		this->pos[1] = 1 + rand() % 3;
	}
	if (round > 4) round = 4;

	if (this->zombiesArrayIndex < this->maxZombies) {

		int zombieType = rand() % round;

		switch (zombieType) {
		case 0:
			this->zombies[this->zombiesArrayIndex] = new NormalZombie(this->TMptr->getTexture("spritesheet-nZombWalk"), 22, this->pos, this->TMptr, this->SMptr);
			break;
		case 1:
			this->zombies[this->zombiesArrayIndex] = new FootballZombie(this->TMptr->getTexture("football-walk"), 11, this->pos, this->TMptr, this->SMptr);
			break;
		case 2:
			this->zombies[this->zombiesArrayIndex] = new DancingZombie(this->TMptr->getTexture("dancing-walk-1"), 21, this->pos, this->TMptr, this->SMptr);
			break;
		case 3:
			this->zombies[this->zombiesArrayIndex] = new FlyingZombie(this->TMptr->getTexture("flying-zombie"), 11, this->pos, this->TMptr, this->SMptr);
			break;
		}
		this->zombiesArrayIndex++;
	}
	else {
		getZombieDeadIndex();
		if (this->deadIndex != -1) {
			cout << "dead index is not -1\n";
			delete[] this->zombies[this->deadIndex];
			int zombieType = rand() % 4;

			switch (zombieType) {
			case 0:
				this->zombies[this->zombiesArrayIndex] = new NormalZombie(this->TMptr->getTexture("spritesheet-nZombWalk"), 22, this->pos, this->TMptr, this->SMptr);
				break;
			case 1:
				this->zombies[this->zombiesArrayIndex] = new FootballZombie(this->TMptr->getTexture("football-walk"), 11, this->pos, this->TMptr, this->SMptr);
				break;
			case 2:
				this->zombies[this->zombiesArrayIndex] = new DancingZombie(this->TMptr->getTexture("dancing-walk-1"), 21, this->pos, this->TMptr, this->SMptr);
				break;
			case 3:
				this->zombies[this->zombiesArrayIndex] = new FlyingZombie(this->TMptr->getTexture("flying-zombie"), 11, this->pos, this->TMptr, this->SMptr);
				break;
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
void ZombieFactory::restartSpawnClock() { this->spawnClock.restart(); }

void ZombieFactory::updateEverything(Plant** plants, int plantsArrayIndex, LawnMower** lawnmowers, Life* lives, int round) {
	for (int i = 0; i < this->zombiesArrayIndex; i++) {
		this->zombies[i]->animate();
		this->zombies[i]->move(plants, plantsArrayIndex);

		this->zombies[i]->spawnZombie(this->zombies, this->zombiesArrayIndex, maxZombies);

		float* position = this->zombies[i]->getPosition();
		float first = -0.5, last = -1;
		if (this->zombies[i]->isFlying()) {
			first = 0, last = -0.5;
		}
		if (position[0] <= first) {
			if (lawnmowers[(int)position[1]]->getExists() == true) {
				lawnmowers[(int)position[1]]->activate();
			}
			else if (zombies[i]->getExist() && position[0] <= last) {
				zombies[i]->setExist(false);
				lives->decrementLives();
			}
		}
	}
	spawnZombie(round);
}

void ZombieFactory::draw(RenderWindow& window) {
	for (int i = 0; i < this->zombiesArrayIndex; i++) {
		this->zombies[i]->draw(window);
	}
}