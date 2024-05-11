#pragma once


#include "Level.h"
#include "Garden.h"
#include "LawnMower.h"

class BeginnersGarden : public Level {
	RectangleShape garden[5][9];

public:
	BeginnersGarden(Background& background, TextureManager* TM, FontManager* FM, SoundManager* SM, Clock* runClock, Text* sunCountText, int& sunCount, LawnMower** lawnmowers, float* lawnMowerPos) :Level(TM, FM, SM) {
		this->round = 1;


		background.getSprite().setTexture(this->TMptr->getTexture("bgfirst"));

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
			//if (i == 0 || i == 4) continue;
			lawnMowerPos[1] = i;
			lawnmowers[i] = new LawnMower(this->TMptr, lawnMowerPos);
		}
	}

	void drawEverything(RenderWindow& window, Background& background,
		Inventory* Inv, int& sunCount, PlantFactory* PF, ZombieFactory* ZF, LawnMower** lawnmowers, Life& lives,
		FallingSun* sun, Text& sunCountText
	) {
		window.draw(background.getSprite());

		for (int i = 0; i < 5; i++) {
			if (i == 0 || i == 4) continue;
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
			if (i == 0 || i == 4) continue;
			lawnmowers[i]->draw(window);
		}

		// draw lives
		lives.drawLives(window);

		// draw sun
		sun->draw(window);

		window.draw(sunCountText);
	}



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

};