#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "FontManager.h"
using namespace std;
using namespace sf;

class Level {
private:
	string str;
	Text levelText;
	FontManager FM;
	float levelPosition[2];
	const float middle1 = 450, middle2 = 600;
	float speed;
	bool midWay;
	Clock levelClock;
	int level;
	bool exists;

public:
	Level() {
		levelText.setFont(FM[0]);
		levelText.setCharacterSize(100);
		levelText.setString("LEVEL 1");
		levelText.setFillColor(Color(153, 0, 26));
		levelPosition[0] = -250, levelPosition[1] = 250;
		levelText.setPosition(levelPosition[0], levelPosition[1]);
		speed = 50;
		midWay = false;
		level = 1;
		exists = true;
	}
	void reset() {
		levelPosition[0] = -250, levelPosition[1] = 250;
		levelText.setPosition(levelPosition[0], levelPosition[1]);
		levelClock.restart();
		midWay = false;
		exists = true;
	}
	void increaseLevel() {
		level++;
		levelText.setString("LEVEL " + to_string(level));
	}
	void move(RenderWindow& window) {
		if (exists) {
			if (levelClock.getElapsedTime().asMilliseconds() > 15) {
				levelPosition[0] += speed;
				if (levelPosition[0] >= middle1 && levelPosition[1] <= middle2 && !midWay) {
					speed = 1.5;
				}
				if (levelText.getPosition().x > middle2 && !midWay) {
					midWay = true;
					speed = 50;
				}

				levelClock.restart();
			}
			levelText.setPosition(levelPosition[0], levelPosition[1]);
			if (levelPosition[0] >= 1400) exists = false;
			window.draw(levelText);
		}
	}
};