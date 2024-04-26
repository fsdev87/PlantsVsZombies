#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
#include "Plant.h"
#include "Card.h"
#include "Peashooter.h"
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
		int indexInInvetory = rectIndex - 2;
		cout << gx << ", " << gy << endl;
		float pos[2] = { gx, gy };

		plants[1] = new Peashooter(TMptr->getTexture("spritesheet-peashooter"), 13, pos);

		selected = false;
	}

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