#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Card {
private:
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
private:
    RectangleShape inventoryBack;
    Color darkerShade{ 110, 50, 19, 220 };
    float inventoryHeight = 100;
    float inventoryWidth = 800;
    Card cards[8];
    int index = 0;
    const int maxCards = 8;

public:
    Inventory() : inventoryBack({ 800, 100}) {
        inventoryBack.setFillColor(darkerShade);
        inventoryBack.setPosition(150, 0);
        /* no need to initialize all 8 cards as default constructor automatically calls
        for all cards object in the array */
    }

    void drawInventory(RenderWindow& window) const {
        
        window.draw(inventoryBack);
        for (int i = 0; i < index; i++) {
            cards[i].drawCard(window);
        }
    }

    void addCard(Texture& t) {
        if (index >= maxCards) return;
        cards[index].setCardTexture(t);
        cards[index].setCardPosition((index * 110) + 180, 5);  // Corrected line
        index++;
    }
};