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
	Clock animClock;

public:
	int getColumns() { return columns; }
	void setColumns(int cols) { columns = cols; }

public:
	Animation(int boxX = 0, int boxY = 0, int cols = 0) : boxX(boxX), boxY(boxY), columns(cols), frame(0) {
		animClock.restart();
	}

	void animate(Sprite& sprite) {
		float time = animClock.getElapsedTime().asMilliseconds();
		if (time > 100) {
			sprite.setTextureRect(IntRect(frame * boxX, 0, boxX, boxY));
			frame += 1;
			animClock.restart();
		}
		if (frame >= columns) frame = 0;
	}
};