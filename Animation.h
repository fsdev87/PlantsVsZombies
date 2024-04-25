#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Animation {
protected:
	int columns;
	int boxX;
	int boxY;
	int frame;
	Texture tex;
	Sprite sprite;
	Clock animClock;
	int xCord, yCord;

public:
	Animation(string source, int boxX, int boxY, int col, int x, int y) : xCord(x), yCord(y), boxX(boxX), boxY(boxY), columns(col), frame(0) {
		if (!tex.loadFromFile(source)) {
			cout << "Error loading texture" << endl;
		}
		sprite.setTexture(tex);
		sprite.setTextureRect(IntRect(0, 0, boxX, boxY));
		sprite.setPosition(185 + yCord * 80, 30 + xCord * 96);
		animClock.restart();
	}

	void animate() {
		float time = animClock.getElapsedTime().asMilliseconds();
		if (time > 100) {
			sprite.setTextureRect(IntRect(frame * boxX, 0, boxX, boxY));
			frame += 1;
			animClock.restart();
		}
		if (frame >= columns) frame = 0;
	}

	void draw(RenderWindow& window) const {
		window.draw(sprite);
	}
};
