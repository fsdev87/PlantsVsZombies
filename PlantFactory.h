#ifndef PLANT_FAC_H
#define PLANT_FAC_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "SoundManager.h"
#include "Inventory.h"

class PlantFactory {
	Plant** plants;
	int plantsArrayIndex;
	const int maxPlants = 45;
	SoundManager* SMptr;
public:
	PlantFactory(SoundManager* SM);
	Plant** getPlants();
	int getPlantsArrayIndex();
	int& getPlantsArrayIndexByRef();

	// Handle placing of plant from inventory
	void handlePlacing(Inventory* Inv, int gx, int gy, int& sunCount);

	// handles clicking of player on sun
	void handleSunClick(int gx, int gy, Text& sunCountText, int& sunCount);

	void updateEverything(Zombie** zombies, int zombiesArrayIndex);

	void draw(sf::RenderWindow& window);

};
#endif