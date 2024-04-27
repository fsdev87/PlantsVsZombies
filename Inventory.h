#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
#include "Plant.h"
#include "Card.h"

#include "Wallnut.h"
#include "Sunflower.h"
#include "Peashooter.h"
#include "Repeater.h"
#include "Snowpea.h"
#include "Cherrybomb.h"

using namespace sf;
using namespace std;


class Inventory {
private:
	float inventoryHeight = 100;
	float inventoryWidth = 800;
	Card cards[8];
	int index = 0;
	const int maxCards = 8;
	Sprite inventorySprite;
	TextureManager* TMptr;


	// Selection
	bool selected = false;
	int rectIndex;
	RectangleShape selectedRect;


	//
	//int plantsArrayIndex = 0;

public:
	Inventory(TextureManager* tm) {
		this->TMptr = tm;
		this->inventorySprite.setTexture(TMptr->getTexture("inventory"));
		this->inventorySprite.setPosition(60, 0);
		this->inventorySprite.setScale(1.1, 1.1);

		this->selectedRect.setSize({ 51, 75 });
		this->selectedRect.setOutlineThickness(4);
		this->selectedRect.setOutlineColor(Color::Green);
		this->selectedRect.setFillColor(Color::Transparent);

	}

	void drawInventory(RenderWindow& window) const {
		window.draw(inventorySprite);
		for (int i = 0; i < index; i++) {
			this->cards[i].drawCard(window);
		}
		if (this->selected)
			window.draw(selectedRect);
	}

	bool validMouseClick(int x, int y) {
		this->rectIndex = (x) / 64;
		this->selected = true;
		if (rectIndex - 2 < index)
			this->selectedRect.setPosition(151 + ((rectIndex - 2) * 59), 9);
		else this->selected = false;

		bool a = x >= 150 && x <= 616 && y >= 10 && y <= 84;
		if (!a) this->selected = false;
		return a;
	}

	int getDeadPlantIndex(Plant** plants, int plantsArrayIndex) {
		for (int i = 0; i < plantsArrayIndex; i++) {
			if (plants[i]->getExist() == false) return i;
		}
		return -1;
	}

	void showPlantIndex(Plant** plants, int plantsArrayIndex) {
		cout << "Plants alive or dead: \n";
		for (int i = 0; i < plantsArrayIndex; i++) {
			cout << i << " = " << plants[i]->getExist() << endl;
		}
	}

	void handlePlacing(int gx, int gy, Plant** plants, int& plantsArrayIndex) {
		float pos[2] = { gx, gy };
		int indexInInventory = rectIndex - 2;
		if (plantsArrayIndex >= 45) return;
		// check if already plant is not there
		for (int i = 0; i < plantsArrayIndex; i++) {
			if (plants[i]->getExist() && plants[i]->getPosition()[0] == gx && plants[i]->getPosition()[1] == gy) {
				selected = false;
				return;
			}
		}

		//
		int tempArrayIndex = plantsArrayIndex;
		int deadIndex = getDeadPlantIndex(plants, plantsArrayIndex);
		if (deadIndex != -1) {
			delete plants[deadIndex];
			plants[deadIndex] = nullptr;
			tempArrayIndex = deadIndex;
		}

		if (indexInInventory == 0)
			plants[tempArrayIndex] = new Sunflower(TMptr->getTexture("spritesheet-sunflower"), TMptr->getTexture("spritesheet-sun"), 18, pos);
		else if (indexInInventory == 1)
			plants[tempArrayIndex] = new Peashooter(TMptr->getTexture("spritesheet-peashooter"), 13, pos);
		else if (indexInInventory == 2)
			plants[tempArrayIndex] = new Repeater(TMptr->getTexture("spritesheet-repeater"), 15, pos);
		else if (indexInInventory == 3)
			plants[tempArrayIndex] = new Wallnut(TMptr->getTexture("spritesheet-wallnut"), 16, pos);
		else if (indexInInventory == 4)
			plants[tempArrayIndex] = new Snowpea(TMptr->getTexture("spritesheet-snowpea"), TMptr->getTexture("bulletIce"), 15, pos);
		else if (indexInInventory == 5) {
			plants[tempArrayIndex] = new Cherrybomb(this->TMptr->getTexture("spritesheet-cherrybomb"), 7, pos);
		}

		if (deadIndex == -1) {
			cout << "Incremented plant index\n";
			plantsArrayIndex++;
		}
		this->selected = false;
	}

	bool hasSelectedSomething() { return this->selected; }

	void addCard(Texture& t, string n) {
		cout << "Added card\n";
		if (index >= maxCards) {
			cout << "Inventory is full\n";
			return;
		}
		this->cards[index].setCardTexture(t, n);
		this->cards[index].setCardPosition(150 + (index * 59), 9);

		this->index++;
	}
};