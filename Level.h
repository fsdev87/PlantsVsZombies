#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "FontManager.h"
#include <fstream>
#include "SoundManager.h"
#include "Scoreboard.h"
#include "PlantFactory.h"
#include "ZombieFactory.h"
#include "Background.h"
#include "Inventory.h"


using namespace std;
using namespace sf;

class Level {
protected:
	Text levelText;
	Text levelTextS;
	float levelPosition[2];
	const float middle1 = 450, middle2 = 620;
	float speed;
	bool midWay;
	Clock levelClock;
	bool exists;

	SoundManager* SMptr;
	FontManager* FMptr;
	TextureManager* TMptr;
	Scoreboard* SBptr;
	int round;
public:
	Level(TextureManager* TM, FontManager* FM, SoundManager* SM, Scoreboard* scoreboard) {
		this->SMptr = SM;
		this->FMptr = FM;
		this->TMptr = TM;
		this->SBptr = scoreboard;

		this->levelText.setFont(FM->get(2));
		this->levelText.setCharacterSize(150);
		this->levelText.setString("LEVEL 1");
		this->levelText.setFillColor(Color::White);
		this->levelPosition[0] = -250, levelPosition[1] = 250;
		this->levelText.setPosition(levelPosition[0], levelPosition[1]);

		this->levelTextS.setFont(FM->get(2));
		this->levelTextS.setCharacterSize(151);
		this->levelTextS.setString("LEVEL 1");
		this->levelTextS.setFillColor(Color(89, 46, 12));
		this->levelTextS.setPosition(levelPosition[0], levelPosition[1] + 8);
		this->speed = 50;
		this->midWay = false;
		this->exists = true;
		//this->SMptr->playSound("round1");

	}


	void saveEverything(ofstream& file) {
		file.write(reinterpret_cast<char*>(&levelPosition[0]), sizeof(float));
		file.write(reinterpret_cast<char*>(&levelPosition[1]), sizeof(float));
		file.write(reinterpret_cast<char*>(&speed), sizeof(float));

		file.write(reinterpret_cast<char*>(&midWay), sizeof(bool));
		file.write(reinterpret_cast<char*>(&exists), sizeof(bool));
	}

	void readEverything(ifstream& file) {
		file.read(reinterpret_cast<char*>(&levelPosition[0]), sizeof(float));
		file.read(reinterpret_cast<char*>(&levelPosition[1]), sizeof(float));
		this->levelText.setPosition(levelPosition[0], levelPosition[1]);


		file.read(reinterpret_cast<char*>(&speed), sizeof(float));

		file.read(reinterpret_cast<char*>(&midWay), sizeof(bool));
		file.read(reinterpret_cast<char*>(&exists), sizeof(bool));
	}

	void reset() {
		this->levelPosition[0] = -250, levelPosition[1] = 250;
		this->levelText.setPosition(levelPosition[0], levelPosition[1]);
		this->levelTextS.setPosition(levelPosition[0], levelPosition[1]);
		this->levelClock.restart();
		this->midWay = false;
		this->exists = true;
	}
	void increaseLevel() {
		this->levelText.setString("LEVEL " + to_string(round));
		this->levelTextS.setString("LEVEL " + to_string(round));
	}

	virtual void drawEverything(RenderWindow& window, Background& background,
		Inventory* Inv, int& sunCount, PlantFactory* PF, ZombieFactory* ZF, LawnMower** lawnmowers, Life& lives,
		FallingSun* sun, Text& sunCountText) = 0;

	void updateEverything(PlantFactory* PF, ZombieFactory* ZF, LawnMower** lawnmowers, Life& lives, FallingSun& sun) {

		// Update everything here
		// check for collisions, animation, shooting, everything
		PF->updateEverything(ZF->getZombies(), ZF->getZombiesArrayIndex(), this->SBptr);

		ZF->updateEverything(PF->getPlants(), PF->getPlantsArrayIndex(), lawnmowers, &lives, this->round);

		// call all functions of sun
		sun.generate();
		sun.moveSun();

		for (int i = 0; i < 5; i++) {
			lawnmowers[i]->move(ZF->getZombies(), ZF->getZombiesArrayIndex(), this->SBptr);
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
			this->levelTextS.setPosition(levelPosition[0], levelPosition[1] + 8);
			this->levelText.setPosition(levelPosition[0], levelPosition[1]);
			if (this->levelPosition[0] >= 1400) exists = false;
			window.draw(levelTextS);
			window.draw(levelText);
		}
	}
	virtual ~Level() {}
};