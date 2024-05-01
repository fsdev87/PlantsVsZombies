#ifndef ZOMBIE_FAC_H
#define ZOMBIE_FAC_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include "NormalZombie.h"

class ZombieFactory {
	Zombie** zombies;
	int deadIndex = -1;

	const int maxZombies = 50;
	int zombiesArrayIndex = 0;
	const float x = 14;
	float pos[2] = { x, 0 };

	TextureManager* TMptr;
	Clock spawnClock;

public:
	ZombieFactory(TextureManager* tm);

	Zombie** getZombies();
	int& getZombiesArrayIndex();

	void updateEverything(Plant** plants, int plantsArrayIndex);

	void spawnZombie();
	void  getZombieDeadIndex();
	void draw(RenderWindow& window);
};

#endif 