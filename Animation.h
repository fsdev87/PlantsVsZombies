#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
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
	int getColumns();
	void setColumns(int cols);
	int getFrame();
	void setDelay(float d);

public:
	Animation(int boxX = 0, int boxY = 0, int cols = 0);

	void animate(Sprite& sprite);

	void saveEverything(ofstream& file);

	void readEverything(ifstream& file);

	void setFrame(int f);
};
