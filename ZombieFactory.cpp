#include "ZombieFactory.h"

using namespace std;
using namespace sf;


ZombieFactory::ZombieFactory(TextureManager* tm) {
	zombies = new Zombie * [maxZombies] { nullptr };
	this->TMptr = tm;
	deadIndex = -1;
	zombiesArrayIndex = 0;
	spawnClock.restart();
}

void ZombieFactory::getZombieDeadIndex() {
	for (int i = 0; i < zombiesArrayIndex; i++) {
		if (zombies[i]->getExist() == false) {
			deadIndex = i;
			cout << "Found dead index";
			return;
		}
	}
	deadIndex = -1;
}

void ZombieFactory::spawnZombie() {
	if (spawnClock.getElapsedTime().asSeconds() < 5) return;

	getZombieDeadIndex();
	pos[1] = rand() % 5;
	if (deadIndex != -1) {
		cout << "dead index is not -1\n";
		delete[] zombies[deadIndex];
		zombies[deadIndex] = new NormalZombie(TMptr->getTexture("spritesheet-nZombWalk"), 22, pos, TMptr);
	}
	else {
		if (zombiesArrayIndex < maxZombies) {
			zombies[zombiesArrayIndex] = new NormalZombie(TMptr->getTexture("spritesheet-nZombWalk"), 22, pos, TMptr);
			zombiesArrayIndex++;
		}
		else cout << "Max zombies reached in spawnZombie function" << endl;
	}
	spawnClock.restart();
}

Zombie** ZombieFactory::getZombies() { return this->zombies; }
int& ZombieFactory::getZombiesArrayIndex() { return this->zombiesArrayIndex; }

void ZombieFactory::updateEverything(Plant** plants, int plantsArrayIndex) {
	for (int i = 0; i < zombiesArrayIndex; i++) {
		zombies[i]->animate();
		zombies[i]->move(plants, plantsArrayIndex);
	}
	spawnZombie();
}

void ZombieFactory::draw(RenderWindow& window) {
	for (int i = 0; i < zombiesArrayIndex; i++) {
		zombies[i]->draw(window);
	}
}