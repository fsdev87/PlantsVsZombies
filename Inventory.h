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
	int plantIndex = 0;

public:
	Inventory(TextureManager* tm) {
		TMptr = tm;
		inventorySprite.setTexture(TMptr->getTexture("inventory"));
		inventorySprite.setPosition(60, 0);
		inventorySprite.setScale(1.1, 1.1);

		selectedRect.setSize({ 51, 75 });
		selectedRect.setOutlineThickness(4);
		selectedRect.setOutlineColor(Color::Green);
		selectedRect.setFillColor(Color::Transparent);

	}

	void drawInventory(RenderWindow& window) const {
		window.draw(inventorySprite);
		for (int i = 0; i < index; i++) {
			cards[i].drawCard(window);
		}
		if (selected)
			window.draw(selectedRect);
	}

	bool validMouseClick(int x, int y) {
		rectIndex = (x) / 64;
		selected = true;
		if (rectIndex - 2 < index)
			selectedRect.setPosition(151 + ((rectIndex - 2) * 59), 9);
		else selected = false;

		cout << rectIndex << " ";
		bool a = x >= 150 && x <= 616 && y >= 10 && y <= 84;
		if (!a) selected = false;
		return a;
	}

	void handlePlacing(int gx, int gy, Plant** plants) {
		cout << "Placed selected plant\n";
		float pos[2] = { gx, gy };
		int indexInInventory = rectIndex - 2;
		cout << "Index in inventory = " << indexInInventory << ", index of plant = " << plantIndex << endl;
		if (plantIndex >= 45) return;
		// check if already plant is not there
		for (int i = 0; i < plantIndex; i++) {
			if (plants[i]->getExist() && plants[i]->getPosition()[0] == gx && plants[i]->getPosition()[1] == gy) {
				selected = false;
				return;
			}
			/*else if (plants[i]->getExist() == false) {
				delete[] plants[i];
				plants[i] = nullptr;
			}*/
		}
		//
		if (indexInInventory == 0)
			plants[plantIndex] = new Sunflower(TMptr->getTexture("spritesheet-sunflower"), TMptr->getTexture("spritesheet-sun"), 18, pos);
		else if (indexInInventory == 1)
			plants[plantIndex] = new Peashooter(TMptr->getTexture("spritesheet-peashooter"), 13, pos);
		else if (indexInInventory == 2)
			plants[plantIndex] = new Repeater(TMptr->getTexture("spritesheet-repeater"), 15, pos);
		else if (indexInInventory == 3)
			plants[plantIndex] = new Wallnut(TMptr->getTexture("spritesheet-wallnut"), 16, pos);
		else if (indexInInventory == 4)
			plants[plantIndex] = new Snowpea(TMptr->getTexture("spritesheet-snowpea"), TMptr->getTexture("bulletIce"), 15, pos);
		else if (indexInInventory == 5)
			plants[plantIndex] = new Cherrybomb(this->TMptr->getTexture("spritesheet-cherrybomb"), 7, pos);

		plantIndex++;
		selected = false;
	}

	int getPlantIndex() { return plantIndex; }

	bool hasSelectedSomething() { return selected; }

	void addCard(Texture& t, string n) {
		cout << "Added card\n";
		if (index >= maxCards) {
			cout << "Inventory is full\n";
			return;
		}
		cards[index].setCardTexture(t, n);
		cards[index].setCardPosition(150 + (index * 59), 9);

		index++;
	}
};