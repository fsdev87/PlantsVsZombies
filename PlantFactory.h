#ifndef PLANT_FAC_H
#define PLANT_FAC_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "SoundManager.h"
#include "Inventory.h"
#include "FallingSun.h"
#include "Scoreboard.h"

class PlantFactory {
	Plant** plants;
	int plantsArrayIndex;
	const int maxPlants = 45;
	SoundManager* SMptr;
	TextureManager* TMptr;

	string* types = new string[maxPlants]{};

public:
	PlantFactory(SoundManager* SM, TextureManager* TMptr);
	Plant** getPlants();
	int getPlantsArrayIndex();
	int& getPlantsArrayIndexByRef();

	// Handle placing of plant from inventory
	void handlePlacing(Inventory* Inv, int gx, int gy, int& sunCount, int round);

	void reset();

	// handles clicking of player on sun
	void handleSunClick(int gx, int gy, Text& sunCountText, int& sunCount);

	void handleWallnutClick(int gx, int gy);

	void handleFallingSun(int gx, int gy, FallingSun* sun, Text& sunCountText, int& sunCount);

	void updateEverything(Zombie** zombies, int zombiesArrayIndex, Scoreboard* scoreboard);

	void saveEverything(ofstream& file) {
		file.write(reinterpret_cast<char*>(&plantsArrayIndex), sizeof(int));
		for (int i = 0; i < plantsArrayIndex; i++) {
			file.write(reinterpret_cast<char*>(&types[i]), sizeof(string));
			plants[i]->saveEverything(file);
		}
	}

	void readEverything(ifstream& file) {
		file.read(reinterpret_cast<char*>(&plantsArrayIndex), sizeof(int));

		for (int i = 0; i < plantsArrayIndex; i++) {
			file.read(reinterpret_cast<char*>(&types[i]), sizeof(string));
			float pos[2] = { 0,0 };
			if (this->types[i] == "sunflower") {
				plants[i] = new Sunflower(TMptr->getTexture("spritesheet-sunflower"), TMptr->getTexture("icon-sun"), 18, pos);
			}
			else if (this->types[i] == "peashooer") {
				plants[i] = new Peashooter(TMptr->getTexture("spritesheet-peashooter"), 13, pos);
			}
			else if (this->types[i] == "repeater") {
				plants[i] = new Repeater(TMptr->getTexture("spritesheet-repeater"), 15, pos);
			}
			else if (this->types[i] == "wallnut") {
				plants[i] = new Wallnut(TMptr->getTexture("spritesheet-wallnut"), 16, pos);
			}
			else if (this->types[i] == "cherrybomb") {
				plants[i] = new Cherrybomb(this->TMptr->getTexture("spritesheet-cherrybomb"), 18, pos);

			}
			else if (this->types[i] == "snowpea") {
				plants[i] = new Snowpea(TMptr->getTexture("spritesheet-snowpea"), TMptr->getTexture("bulletIce"), 15, pos);
			}

			plants[i]->readEverything(file);
		}
	}

	void draw(RenderWindow& window);

};
#endif