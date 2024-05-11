#pragma once


#include "Level.h"
#include "Garden.h"
#include "LawnMower.h"
#include "Inventory.h"

#include "PlantFactory.h"
#include "ZombieFactory.h"
#include "Background.h"

class LimitedGarden : public Level {
	RectangleShape garden[5][9];

public:


	LimitedGarden(Background& background, PlantFactory* PF, ZombieFactory* ZF, Inventory* Inv, TextureManager* TM, FontManager* FM, SoundManager* SM, Clock* RunClock, Text* TimeText, Text* sunCountText, int& sunCount, LawnMower** lawnmowers, float* lawnMowerPos) :Level(TM, FM, SM) {

		this->resetEverything(PF, ZF);

		this->round = 4;

		this->increaseLevel();
		this->reset();

		background.getSprite().setTexture(this->TMptr->getTexture("limitedbg"));

		RunClock->restart();
		TimeText->setPosition(1300, 550);
		TimeText->setFont(this->FMptr->get(0));
		TimeText->setFillColor(Color::Black);
		TimeText->setCharacterSize(36);

		sunCountText->setFont(this->FMptr->get(0));
		sunCountText->setString(to_string(sunCount));
		sunCountText->setCharacterSize(24);
		sunCountText->setPosition(86, 62);
		sunCountText->setFillColor(Color::Black);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				this->garden[i][j].setSize(Vector2f(80, 96));
				this->garden[i][j].setFillColor(((i + j) % 2) == 0 ? Color(255, 255, 255, 50) : Color(255, 255, 255, 100));
				this->garden[i][j].setPosition(gardenCords.leftX + j * 80, gardenCords.topY + i * 96);
			}
		}

		for (int i = 0; i < 5; i++) {
			lawnMowerPos[1] = i;
			lawnmowers[i] = new LawnMower(this->TMptr, lawnMowerPos);
		}
	}


	void drawEverything(RenderWindow& window, Background& background,
		Inventory* Inv, int& sunCount, PlantFactory* PF, ZombieFactory* ZF, LawnMower** lawnmowers, Life& lives,
		FallingSun* sun, Text& TimeText, Text& sunCountText
	) {
		window.draw(background.getSprite());

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				window.draw(garden[i][j]);
			}
		}

		this->move_draw(window);
		Inv->drawInventory(window, sunCount);

		PF->draw(window);
		ZF->draw(window);

		// draw lawn mowers
		for (int i = 0; i < 5; i++) {
			lawnmowers[i]->draw(window);
		}

		// draw lives
		lives.drawLives(window);

		// draw sun
		sun->draw(window);

		window.draw(TimeText);
		window.draw(sunCountText);
	}



	void updateEverything(string& timeString, Clock& RunClock, float roundTimeLimit, Text& TimeText, PlantFactory* PF, ZombieFactory* ZF,
		LawnMower** lawnmowers, Life& lives, FallingSun& sun
	) {
		timeString = to_string(RunClock.getElapsedTime().asSeconds());

		if (RunClock.getElapsedTime().asSeconds() > roundTimeLimit) {
			//updateRound();
		}

		TimeText.setString(timeString);
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

};