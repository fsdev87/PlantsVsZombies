#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Background {
    Texture backgroundTexture;
    Sprite backgroundSprite;
public:
    Background() {
        if (!backgroundTexture.loadFromFile("assets/images/bg.jpg")) {
            cout << "BG.jpg NOT FOUND\n";
        }
        backgroundSprite.setTexture(backgroundTexture);
    }
    Sprite& getSprite() { return backgroundSprite; }
};