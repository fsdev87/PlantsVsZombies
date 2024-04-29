#ifndef ZOMBIE_FAC_H
#define ZOMBIE_FAC_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include "NormalZombie.h"

class ZombieFactory {
	Zombie** zombies;
	const int maxZombieCount = 20;
	int zombiesArrayIndex = 10;

public:
	ZombieFactory(TextureManager* tm);

	Zombie** getZombies();
	int& getZombiesArrayIndex();

	void updateEverything(Plant** plants, int plantsArrayIndex);

	void draw(RenderWindow& window);
};

#endif 