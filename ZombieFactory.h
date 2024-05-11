#ifndef ZOMBIE_FAC_H
#define ZOMBIE_FAC_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include "NormalZombie.h"
#include "SoundManager.h"
#include "DancingZombie.h"
#include "FootballZombie.h"
#include "LawnMower.h"
#include "Life.h"

class ZombieFactory {
	Zombie** zombies;
	int deadIndex = -1;

	const int maxZombies = 100;
	int zombiesArrayIndex = 0;
	const float x = 14;
	float pos[2] = { x, 0 };
	
	TextureManager* TMptr;

	// Zombie factory has it's own SMptr, just in case
	// we will give each zombie its own SMptr
	SoundManager* SMptr;
	Clock spawnClock;

public:
	ZombieFactory(TextureManager* tm, SoundManager* SM);

	Zombie** getZombies();
	int& getZombiesArrayIndex();

	void updateEverything(Plant** plants, int plantsArrayIndex, LawnMower** lawnmowers, Life* lives);

	void spawnZombie();
	void  getZombieDeadIndex();
	void draw(RenderWindow& window);
};

#endif 