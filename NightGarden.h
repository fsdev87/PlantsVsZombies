#pragma once


#include "Level.h"
#include "Garden.h"
#include "LawnMower.h"
#include "Inventory.h"

#include "PlantFactory.h"
#include "ZombieFactory.h"
#include "Background.h"

class NightGarden : public Level {
	RectangleShape garden[5][9];

public:
	NightGarden(Background& background, PlantFactory* PF, ZombieFactory* ZF, Inventory* Inv, TextureManager* TM, FontManager* FM, SoundManager* SM, Clock* runClock, Text* sunCountText, int& sunCount, LawnMower** lawnmowers, float* lawnMowerPos, Scoreboard* scoreboard) : Level(TM, FM, SM, scoreboard) {

		this->resetEverything(PF, ZF);

		this->round = 3;

		this->increaseLevel();
		this->reset();

		background.getSprite().setTexture(this->TMptr->getTexture("bgnight"));



		Inv->addCard(this->TMptr->getTexture("card-snowpea_dim"), this->TMptr->getTexture("card-snowpea"), "snowpea", 175);
		Inv->addCard(this->TMptr->getTexture("card-cherrybomb_dim"), this->TMptr->getTexture("card-cherrybomb"), "cherrybomb", 150);
		Inv->addCard(this->TMptr->getTexture("shovel"), this->TMptr->getTexture("shovel"), "shovel", 0);

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
		FallingSun* sun, Text& sunCountText) {
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

		window.draw(sunCountText);
	}





};