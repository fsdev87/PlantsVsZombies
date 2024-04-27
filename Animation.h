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
	float delay = 100;

public:
	int getColumns() { return this->columns; }
	void setColumns(int cols) { this->columns = cols; }
	int getFrame() { return this->frame; }
	void setDelay(float d) { this->delay = d; }

public:
	Animation(int boxX = 0, int boxY = 0, int cols = 0) : boxX(boxX), boxY(boxY), columns(cols), frame(0) {
		animClock.restart();
	}

	void animate(Sprite& sprite) {
		float time = animClock.getElapsedTime().asMilliseconds();
		if (time > delay) {
			sprite.setTextureRect(IntRect(frame * boxX, 0, boxX, boxY));
			this->frame += 1;
			animClock.restart();
		}
		if (frame >= columns) frame = 0;
	}

	void setFrame(int f) { frame = f; animClock.restart(); }
};