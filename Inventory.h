#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
#include "Plant.h"
#include "Card.h"

#include "Wallnut.h"
#include "Sunflower.h"
#include "Peashooter.h"
#include "Threepeater.h"
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

	SoundManager* SMptr;
	//
	//int plantsArrayIndex = 0;

public:
	Inventory(TextureManager* tm, SoundManager* sm) {
		this->SMptr = sm;
		this->TMptr = tm;
		this->inventorySprite.setTexture(TMptr->getTexture("inventory"));
		this->inventorySprite.setPosition(60, 0);
		this->inventorySprite.setScale(1.1, 1.1);

		this->selectedRect.setSize({ 51, 74 });
		this->selectedRect.setOutlineThickness(4);
		this->selectedRect.setOutlineColor(Color::Green);
		this->selectedRect.setFillColor(Color::Transparent);

	}

	bool hasSelectedSomething() { return this->selected; }

	void addCard(Texture& dim, Texture& bright, string n, int cost) {
		cout << "Added " << n << " at index " << index << "\n";
		if (index >= maxCards) {
			cout << "Inventory is full\n";
			return;
		}
		this->cards[index].setCardTexture(dim, bright, n, cost);
		this->cards[index].setCardPosition(150 + (index * 59), 9);

		this->index++;
	}

	void drawInventory(RenderWindow& window, int& sunCount) {
		window.draw(inventorySprite);
		for (int i = 0; i < index; i++) {
			if (this->cards[i].getCost() > sunCount) {
				this->cards[i].setTexture("dim");
			}
			else {
				this->cards[i].setTexture("bright");
			}
			this->cards[i].drawCard(window);
		}
		if (this->selected)
			window.draw(selectedRect);
	}

	bool validMouseClick(int x, int y, int& sunCount) {
		this->selected = true;

		this->rectIndex = (x) / 64;
		this->rectIndex -= 2;
		if (rectIndex != -1 && rectIndex < index)
			cout << "RectIndex: " << rectIndex << ", cost : " << cards[rectIndex].getCost() << endl;

		if (rectIndex < index) {
			this->selectedRect.setPosition(151 + ((rectIndex) * 59) + 1, 10);
		}
		else {
			this->selected = false;
		}

		if (rectIndex < index && cards[rectIndex].getCost() > sunCount) {
			this->SMptr->playSound("misclick");
			this->selected = false;
		}


		bool a = x >= 150 && x <= 616 && y >= 10 && y <= 84;
		if (a == false) {
			this->selected = false;
		}

		cout << "Selected: " << (this->selected == true ? "True" : "False") << "\n";
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

	void handlePlacing(int gx, int gy, Plant** plants, int& plantsArrayIndex, int& sunCount) {
		if (!this->selected) return;
		float pos[2] = { gx, gy };

		int indexInInventory = rectIndex;
		if (plantsArrayIndex >= 45) return;
		// check if already plant is not there
		for (int i = 0; i < plantsArrayIndex; i++) {
			if (plants[i]->getExist() && plants[i]->getPosition()[0] == gx && plants[i]->getPosition()[1] == gy) {
				this->selected = false;
				return;
			}
		}

		//
		int tempIndex = plantsArrayIndex;
		int deadIndex = getDeadPlantIndex(plants, plantsArrayIndex);
		if (deadIndex != -1 && plants[deadIndex]) {
			delete plants[deadIndex];
			plants[deadIndex] = nullptr;
			tempIndex = deadIndex;
		}

		// only place the plant if the sunCount amount is sufficient
		if (indexInInventory == 0 && sunCount >= 50)
			plants[tempIndex] = new Sunflower(TMptr->getTexture("spritesheet-sunflower"), TMptr->getTexture("icon-sun"), 18, pos);
		else if (indexInInventory == 1 && sunCount >= 100)
			plants[tempIndex] = new Peashooter(TMptr->getTexture("spritesheet-peashooter"), 13, pos);
		else if (indexInInventory == 2 && sunCount >= 200)
			plants[tempIndex] = new Repeater(TMptr->getTexture("spritesheet-repeater"), 15, pos);
		else if (indexInInventory == 3 && sunCount >= 50)
			plants[tempIndex] = new Wallnut(TMptr->getTexture("spritesheet-wallnut"), 16, pos);
		else if (indexInInventory == 4 && sunCount >= 175)
			plants[tempIndex] = new Snowpea(TMptr->getTexture("spritesheet-snowpea"), TMptr->getTexture("bulletIce"), 15, pos);
		else if (indexInInventory == 5 && sunCount >= 150)
			plants[tempIndex] = new Cherrybomb(this->TMptr->getTexture("spritesheet-cherrybomb"), 18, pos);
		else if (indexInInventory == 6 && sunCount >= 325)
			plants[tempIndex] = new Threepeater(this->TMptr->getTexture("spritesheet-threepeater"), 16, pos);
		// otherwise say insufficient amount
		this->SMptr->playSound("place2");


		// added a check here because if it didn't place a plant, there would be nullptr at plants[tempIndex]
		if (plants[tempIndex]) {
			sunCount -= plants[tempIndex]->getPrice();
			if (sunCount < 0) sunCount = 0;
			if (tempIndex == plantsArrayIndex) plantsArrayIndex++;
		}

		this->selected = false;
	}


};