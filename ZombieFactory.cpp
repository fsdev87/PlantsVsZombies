#include "ZombieFactory.h"

using namespace std;
using namespace sf;


ZombieFactory::ZombieFactory(TextureManager* tm) {
	zombies = new Zombie * [maxZombieCount];
	for (int i = 0; i < zombiesArrayIndex; i++) {
		float pos[2];
		pos[0] = 8 + i % 4, pos[1] = i % 5;

		zombies[i] = new NormalZombie(tm->getTexture("spritesheet-nZombWalk"), 22, pos, tm);
	}
}

Zombie** ZombieFactory::getZombies() { return this->zombies; }
int& ZombieFactory::getZombiesArrayIndex() { return this->zombiesArrayIndex; }

void ZombieFactory::updateEverything(Plant** plants, int plantsArrayIndex) {
	for (int i = 0; i < zombiesArrayIndex; i++) {
		zombies[i]->animate();
		zombies[i]->move(plants, plantsArrayIndex);
	}
}

void ZombieFactory::draw(RenderWindow& window) {
	for (int i = 0; i < zombiesArrayIndex; i++) {
		zombies[i]->draw(window);
	}
}