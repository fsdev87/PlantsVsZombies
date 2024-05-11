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
#include "Menu.h"
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

	Menu menu;

	float roundTimeLimit = 5;

	bool play = false, showHighScores = false, resume = false, quit = false;

	bool hasStarted = false;

public:
	Game() : window(VideoMode(1400, 600), "game"), level(&FM, &SM), background(&TM), Inv(&TM, &SM), PF(&SM, &TM), ZF(&TM, &SM), menu(&TM, &FM) {
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

	void drawEverything() {
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
	}

	void updateEverything() {
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
	}

	void run() {
		if (this->showHighScores) {
			//menu.showHighScores();
		}

		// resume remains

		while (this->window.isOpen()) {
			Event event;
			while (this->window.pollEvent(event)) {
				if (event.type == Event::Closed)
					this->window.close();
				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Escape) {
						this->menu.setInMenu(true);
						this->menu.handleEnter(this->hasStarted, this->play, this->showHighScores, this->resume, this->quit, 0);
					}
					else if (event.key.code == Keyboard::C) {
						system("cls");
					}

					if (this->menu.inMenu()) {
						if (event.key.code == Keyboard::Up) {
							this->menu.handleUp();
						}
						else if (event.key.code == Keyboard::Down) {
							this->menu.handleDown();
						}
						else if (event.key.code == Keyboard::Enter) {
							this->menu.handleEnter(this->hasStarted, this->play, this->showHighScores, this->resume, this->quit);
							if (this->quit) {
								window.close();
							}
						}
					}
				}
				if (event.type == Event::MouseButtonPressed) {
					if (event.mouseButton.button == Mouse::Left) {
						int mouseX = event.mouseButton.x;
						int mouseY = event.mouseButton.y;

						if (gardenCords.valid(mouseX, mouseY)) {
							cout << "Position on Grid: " << (mouseY - gardenCords.topY) / 96 << ", " << (mouseX - gardenCords.leftX) / 80 << endl;

							// Handle placing of plants
							int gy = (mouseY - gardenCords.topY) / 96;
							int gx = (mouseX - gardenCords.leftX) / 80;

							if (this->play || (this->play == 0 && this->resume == 1)) {
								this->PF.handlePlacing(&this->Inv, gx, gy, this->sunCount, this->round);
								this->PF.handleSunClick(gx, gy, this->sunCountText, this->sunCount);
								this->PF.handleWallnutClick(gx, gy);
								this->PF.handleFallingSun(gx, gy, &this->sun, this->sunCountText, this->sunCount);
							}
						}

						// no need to call in if statement
						if (this->play || (this->play == 0 && this->resume == 1))
							this->Inv.validMouseClick(mouseX, mouseY, this->sunCount);
					}
				}
			}

			this->window.clear();

			if (this->play || (this->play == 0 && this->resume == 1))
				this->updateEverything();

			// Draw everything here...

			if (this->menu.inMenu()) {
				this->menu.display(window);
			}

			if (this->play || (this->play == 0 && this->resume == 1)) {
				this->drawEverything();
			}

			this->window.display();
		}
	}
};
