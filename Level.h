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
	float levelPosition[2];
	const float middle1 = 450, middle2 = 550;
	float speed;
	bool midWay;
	Clock levelClock;
	int level;
	bool exists;

public:
	Level(FontManager* FM) {
		this->levelText.setFont(FM->operator[](2));
		this->levelText.setCharacterSize(120);
		this->levelText.setString("LEVEL 1");
		this->levelText.setFillColor(Color(16, 12, 12));
		this->levelPosition[0] = -250, levelPosition[1] = 250;
		this->levelText.setPosition(levelPosition[0], levelPosition[1]);
		this->speed = 50;
		this->midWay = false;
		this->level = 1;
		this->exists = true;
	}
	void reset() {
		this->levelPosition[0] = -250, levelPosition[1] = 250;
		this->levelText.setPosition(levelPosition[0], levelPosition[1]);
		this->levelClock.restart();
		this->midWay = false;
		this->exists = true;
	}
	void increaseLevel() {
		this->level++;
		this->levelText.setString("LEVEL " + to_string(level));
	}
	void move_draw(RenderWindow& window) {
		if (this->exists) {
			if (this->levelClock.getElapsedTime().asMilliseconds() > 15) {
				this->levelPosition[0] += speed;
				if (this->levelPosition[0] >= this->middle1 && this->levelPosition[1] <= this->middle2 && !this->midWay) {
					this->speed = 1.5;
				}
				if (this->levelText.getPosition().x > this->middle2 && !this->midWay) {
					this->midWay = true;
					this->speed = 50;
				}

				this->levelClock.restart();
			}
			this->levelText.setPosition(levelPosition[0], levelPosition[1]);
			if (this->levelPosition[0] >= 1400) exists = false;
			window.draw(levelText);
		}
	}
};