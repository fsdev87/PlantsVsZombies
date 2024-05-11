#pragma once

#include "PlantFactory.h"
#include "SoundManager.h"
#include "ZombieFactory.h"

#include "FontManager.h"
#include "TextureManager.h"
#include "Background.h"
#include "Inventory.h"
#include "Life.h"
#include "Level.h"
#include "Garden.h"
#include "FallingSun.h"

#include <cmath>

class Game {
	// window
	RenderWindow window;
	TextureManager TM;
	SoundManager SM;
	FontManager FM;
	Level level;
	Background background;
	Inventory Inv;

	int sunCount = 10000;
	Text sunCountText;

	RectangleShape garden[5][9];

	PlantFactory PF;
	ZombieFactory ZF;

	LawnMower* lawnmowers[5]{ nullptr };
	float lawnMowerPos[2] = { -1, 0 };

	Life lives;

	int round;

	FallingSun sun;

	Clock RunClock;
	Text TimeText;
	string timeString;

	float roundTimeLimit = 20;

public:
	Game() :window(VideoMode(1400, 600), "game"), level(&FM, &SM), background(&TM), Inv(&TM, &SM), PF(&SM, &TM), ZF(&TM, &SM) {
		srand((unsigned)time(0));
		this->RunClock.restart();
		this->TimeText.setPosition(1300, 550);
		this->TimeText.setFont(FM[0]);
		this->TimeText.setFillColor(Color::Black);
		this->TimeText.setCharacterSize(36);

		this->round = 1;

		this->sunCountText.setFont(FM[0]);
		this->sunCountText.setString(to_string(this->sunCount));
		this->sunCountText.setCharacterSize(24);
		this->sunCountText.setPosition(86, 62);
		this->sunCountText.setFillColor(Color::Black);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				this->garden[i][j].setSize(Vector2f(80, 96));
				this->garden[i][j].setFillColor(((i + j) % 2) == 0 ? Color(255, 255, 255, 50) : Color(255, 255, 255, 100));
				this->garden[i][j].setPosition(gardenCords.leftX + j * 80, gardenCords.topY + i * 96);
			}
		}

		for (int i = 0; i < 5; i++) {
			this->lawnMowerPos[1] = i;
			this->lawnmowers[i] = new LawnMower(&TM, this->lawnMowerPos);
		}
	}

	void updateRound() {
		this->round += 1;
		this->level.increaseLevel();
		this->level.reset();
		this->RunClock.restart();


		if (round == 2) {
			this->Inv.addCard(TM.getTexture("card-repeater_dim"), TM.getTexture("card-repeater"), "repeater", 200);
			this->background.getSprite().setTexture(TM.getTexture("bgnight"));
		}
		else if (round == 3) {
			this->Inv.addCard(TM.getTexture("card-wallnut_dim"), TM.getTexture("card-wallnut"), "wallnut", 50);
			this->Inv.addCard(TM.getTexture("card-snowpea_dim"), TM.getTexture("card-snowpea"), "snowpea", 175);
		}
		else if (round == 4) {
			this->Inv.addCard(TM.getTexture("card-cherrybomb_dim"), TM.getTexture("card-cherrybomb"), "cherrybomb", 150);
			this->Inv.addCard(TM.getTexture("shovel"), TM.getTexture("shovel"), "shovel", 0);
			this->background.getSprite().setTexture(TM.getTexture("limitedbg"));
		}
	}

	void run() {
		while (this->window.isOpen()) {
			Event event;
			while (this->window.pollEvent(event)) {
				if (event.type == Event::Closed)
					this->window.close();
				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Escape) {
						this->window.close();
					}
					else if (event.key.code == Keyboard::C) {
						system("cls");
					}
				}
				if (event.type == Event::MouseButtonPressed) {
					if (event.mouseButton.button == Mouse::Left) {
						int mouseX = event.mouseButton.x;
						int mouseY = event.mouseButton.y;
						cout << "Mouse X: " << mouseX << " Mouse Y: " << mouseY << endl;
						if (gardenCords.valid(mouseX, mouseY)) {
							cout << "Position on Grid: " << (mouseY - gardenCords.topY) / 96 << ", " << (mouseX - gardenCords.leftX) / 80 << endl;

							// Handle placing of plants
							int gy = (mouseY - gardenCords.topY) / 96;
							int gx = (mouseX - gardenCords.leftX) / 80;

							this->PF.handlePlacing(&this->Inv, gx, gy, this->sunCount, this->round);
							this->PF.handleSunClick(gx, gy, this->sunCountText, this->sunCount);
							this->PF.handleWallnutClick(gx, gy);
							this->PF.handleFallingSun(gx, gy, &this->sun, this->sunCountText, this->sunCount);
						}

						// no need to call in if statement
						this->Inv.validMouseClick(mouseX, mouseY, this->sunCount);
					}
				}
			}

			this->window.clear();

			this->timeString = to_string(this->RunClock.getElapsedTime().asSeconds());

			if (this->RunClock.getElapsedTime().asSeconds() > this->roundTimeLimit) {
				this->updateRound();
			}

			this->TimeText.setString(this->timeString);
			// Update everything here
			// check for collisions, animation, shooting, everything
			this->PF.updateEverything(this->ZF.getZombies(), this->ZF.getZombiesArrayIndex());

			this->ZF.updateEverything(this->PF.getPlants(), this->PF.getPlantsArrayIndex(), this->lawnmowers, &this->lives, this->round);

			// call all functions of sun
			this->sun.generate();
			this->sun.moveSun();

			for (int i = 0; i < 5; i++) {
				this->lawnmowers[i]->move(this->ZF.getZombies(), this->ZF.getZombiesArrayIndex());
				this->lawnmowers[i]->animate();
			}

			// Draw everything here...
			this->window.draw(this->background.getSprite());

			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 9; j++) {
					this->window.draw(this->garden[i][j]);
				}
			}

			this->level.move_draw(this->window);
			this->Inv.drawInventory(this->window, this->sunCount);

			this->PF.draw(this->window);
			this->ZF.draw(this->window);

			// draw lawn mowers
			for (int i = 0; i < 5; i++) {
				this->lawnmowers[i]->draw(this->window);
			}

			// draw lives
			this->lives.drawLives(this->window);

			// draw sun
			this->sun.draw(this->window);

			this->window.draw(this->TimeText);
			this->window.draw(this->sunCountText);
			this->window.display();
		}
	}
};
