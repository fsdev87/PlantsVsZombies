#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Card {
private:
	Sprite spr;

public:
	Card() {

	}

	void setCardTexture(Texture& t) {
		spr.setTexture(t);
	}

	void setCardPosition(int x, int y) {
		spr.setPosition(x, y);
	}

	void drawCard(RenderWindow& window) const {
		window.draw(spr);
	}
};

class Inventory {
private:
	float inventoryHeight = 100;
	float inventoryWidth = 800;
	Card cards[8];
	int index = 0;
	const int maxCards = 8;
	Sprite inventorySprite;


public:
	Inventory(Texture& tex) {
		inventorySprite.setTexture(tex);
		inventorySprite.setPosition(60, 2);
		inventorySprite.setScale(1.15, 1.15);
	}

	void drawInventory(RenderWindow& window) const {
		window.draw(inventorySprite);
		for (int i = 0; i < index; i++) {
			cards[i].drawCard(window);
		}
	}

	void addCard(Texture& t) {
		cout << "Added card\n";
		if (index >= maxCards) return;
		cards[index].setCardTexture(t);
		cards[index].setCardPosition(130 + (index * 64) + 5, 2);  // Corrected line
		index++;
	}
};