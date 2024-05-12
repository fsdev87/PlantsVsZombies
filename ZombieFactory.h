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

	string* types = new string[maxZombies];

public:
	ZombieFactory(TextureManager* tm, SoundManager* SM);

	Zombie** getZombies();
	int& getZombiesArrayIndex();

	void restartSpawnClock();

	void updateEverything(Plant** plants, int plantsArrayIndex, LawnMower** lawnmowers, Life* lives, int round);

	void reset();

	void saveEverything(ofstream& file) {
		file.write(reinterpret_cast<char*>(&zombiesArrayIndex), sizeof(int));
		for (int i = 0; i < zombiesArrayIndex; i++) {
			file.write(reinterpret_cast<char*>(&types[i]), sizeof(string));
			zombies[i]->saveEverything(file);
		}
	}

	void readEverything(ifstream& file) {
		file.read(reinterpret_cast<char*>(&zombiesArrayIndex), sizeof(int));

		cout << "read index\n";
		for (int i = 0; i < zombiesArrayIndex; i++) {
			float pos[2] = { 0, 0 };
			file.read(reinterpret_cast<char*>(&types[i]), sizeof(string));
			cout << "Type; " << types[i] << endl;
			if (types[i] == "normal") {
				zombies[i] = new NormalZombie(this->TMptr->getTexture("spritesheet-nZombWalk"), 22, this->pos, this->TMptr, this->SMptr);
			}
			else if (types[i] == "dancing") {
				zombies[i] = new DancingZombie(this->TMptr->getTexture("dancing-walk-1"), 21, this->pos, this->TMptr, this->SMptr);
			}
			else if (types[i] == "football") {
				zombies[i] = new FootballZombie(this->TMptr->getTexture("football-walk"), 11, this->pos, this->TMptr, this->SMptr);
			}
			else if (types[i] == "flying") {
				zombies[i] = new FlyingZombie(this->TMptr->getTexture("flying-zombie"), 11, this->pos, this->TMptr, this->SMptr);
			}
			zombies[i]->readEverything(file);
		}
	}

	void spawnZombie(int round);
	void  getZombieDeadIndex();
	void draw(RenderWindow& window);
};

#endif 