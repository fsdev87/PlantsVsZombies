#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Card {
    Sprite spr;
    Color darkerShade{ 220, 50, 19 };
    RectangleShape rect;
public:
    Card() {
        rect.setSize({ 100, 85 });
        rect.setFillColor(darkerShade);
        spr.setScale({ 0.16, 0.16 });
    }

    void setCardTexture(Texture& t) {
        spr.setTexture(t);
    }

    void setCardPosition(int x, int y) {
        spr.setPosition(x + 5, y);
        rect.setPosition(x, y);
    }

    void drawCard(RenderWindow& window) const {
        window.draw(rect);
        window.draw(spr);
    }
};

class Inventory {
    RectangleShape inventoryPeche;
    Color darkerShade{ 110, 50, 19, 220 };
    float inventoryHeight = 100;
    float inventoryWidth = 800;
    Card* cards;
    int index = 0;
    const int maxCards = 7;

private:
    void fixCards() {
        Card* tempC = new Card[index];
        for (int i = 0; i < index; i++) {
            tempC[i] = cards[i];
        }
        delete[] cards;
        cards = new Card[index + 3];
        for (int i = 0; i < index; i++) {
            cards[i] = tempC[i];
        }
        delete[] tempC;
    }

public:
    Inventory() : inventoryPeche({ 800, 100}) {
        inventoryPeche.setFillColor(darkerShade);
        inventoryPeche.setPosition(150, 0);
        cards = nullptr;
    }

    ~Inventory() {
        delete[] cards;
    }

    void drawInventory(RenderWindow& window) const {
        window.draw(inventoryPeche);
        for (int i = 0; i < index; i++) {
            cards[i].drawCard(window);
        }
    }

    void addCard(Texture& t) {
        if (index >= maxCards) return;
        if (cards != nullptr) fixCards();
        else {
            cards = new Card[index + 1];
        }
        cards[index].setCardTexture(t);
        cards[index].setCardPosition((index * 110) + 180, 5);  // Corrected line
        index++;
    }
};
