#ifndef ZOMBIE_FAC_H
#define ZOMBIE_FAC_H


#include <SFML/Graphics.hpp>
#include "SoundManager.h"
#include "NormalZombie.h"
#include "DancingZombie.h"
#include "FootballZombie.h"
#include "FlyingZombie.h"
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

	void restartSpawnClock();

	void updateEverything(Plant** plants, int plantsArrayIndex, LawnMower** lawnmowers, Life* lives, int round);

	void reset();

	void spawnZombie(int round);
	void  getZombieDeadIndex();
	void draw(RenderWindow& window);
};

#endif 