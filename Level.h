#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "FontManager.h"
#include "SoundManager.h"
using namespace std;
using namespace sf;

class Level {
protected:
	string str;
	Text levelText;
	float levelPosition[2];
	const float middle1 = 450, middle2 = 620;
	float speed;
	bool midWay;
	Clock levelClock;
	bool exists;

	SoundManager* SMptr;
	FontManager* FMptr;
	TextureManager* TMptr;

	int round;
public:
	Level(TextureManager* TM, FontManager* FM, SoundManager* SM) {
		this->SMptr = SM;
		this->FMptr = FM;
		this->TMptr = TM;

		this->levelText.setFont(FM->operator[](2));
		this->levelText.setCharacterSize(120);
		this->levelText.setString("LEVEL 1");
		this->levelText.setFillColor(Color(16, 12, 12));
		this->levelPosition[0] = -250, levelPosition[1] = 250;
		this->levelText.setPosition(levelPosition[0], levelPosition[1]);
		this->speed = 50;
		this->midWay = false;
		this->exists = true;
		//this->SMptr->playSound("round1");

	}
	void reset() {
		this->levelPosition[0] = -250, levelPosition[1] = 250;
		this->levelText.setPosition(levelPosition[0], levelPosition[1]);
		this->levelClock.restart();
		this->midWay = false;
		this->exists = true;
	}
	void increaseLevel() {
		this->levelText.setString("LEVEL " + to_string(round));
	}

	virtual void drawEverything(RenderWindow& window, Background& background,
		Inventory* Inv, int& sunCount, PlantFactory* PF, ZombieFactory* ZF, LawnMower** lawnmowers, Life& lives,
		FallingSun* sun, Text& sunCountText) = 0;

	void updateEverything(string& timeString, Clock* runClock, PlantFactory* PF, ZombieFactory* ZF,
		LawnMower** lawnmowers, Life& lives, FallingSun& sun) {

		// Update everything here
		// check for collisions, animation, shooting, everything
		PF->updateEverything(ZF->getZombies(), ZF->getZombiesArrayIndex());

		ZF->updateEverything(PF->getPlants(), PF->getPlantsArrayIndex(), lawnmowers, &lives, this->round);

		// call all functions of sun
		sun.generate();
		sun.moveSun();

		for (int i = 0; i < 5; i++) {
			lawnmowers[i]->move(ZF->getZombies(), ZF->getZombiesArrayIndex());
			lawnmowers[i]->animate();
		}
	}

	void resetEverything(PlantFactory* PF, ZombieFactory* ZF) {
		PF->reset();
		ZF->reset();
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