#pragma once

#include "PlantFactory.h"
#include "SoundManager.h"
#include "ZombieFactory.h"
#include "fstream"
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


	Text TimeText;
	string timeString;

	Menu menu;


	bool showMenu = true;
	bool showHighScores = false;
	bool quit = false;

	bool hasStarted = false;


	int highScores[10] = {};
	Text HighScores[10], heading;
	Sprite medals[3];

	// time handling things
	float gameTime;
	Clock* runClock = nullptr;
	float remainingTime = 120;

public:
	Game() : window(VideoMode(1400, 600), "game"), level(&FM, &SM), background(&TM), Inv(&TM, &SM), PF(&SM, &TM), ZF(&TM, &SM), menu(&TM, &FM) {
		medals[0].setTexture(this->TM.getTexture("gold"));
		medals[1].setTexture(this->TM.getTexture("silver"));
		medals[2].setTexture(this->TM.getTexture("bronze"));

		medals[0].setScale(0.2, 0.2);
		medals[1].setScale(0.15, 0.15);
		medals[2].setScale(0.12, 0.12);

		srand((unsigned)time(0));
		//this->runClock.restart();
		this->TimeText.setPosition(1230, 550);
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

		//// time
		//this->minutes = 1;
		//this->seconds = 59;
	}

	void updateRound() {
		this->TimeText.setFillColor(Color::Black);
		this->round += 1;
		this->level.increaseLevel();
		this->level.reset();
		//this->runClock.restart();


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

		calculateTime();
		this->TimeText.setString("TIME: " + this->timeString);

		if (this->gameTime <= 0) {
			this->updateRound();
		}

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

	void sortScores() {
		bool swapped;
		for (int i = 0; i < 9; i++) {
			swapped = false;
			for (int j = 0; j < 10 - i - 1; j++) {
				if (this->highScores[j] < this->highScores[j + 1]) {
					swap(this->highScores[j], this->highScores[j + 1]);
					swapped = true;
				}
			}

			if (swapped == false)
				break;
		}
	}


	void initHighScores() {
		ifstream scores("highscores.txt");
		if (!scores.is_open()) {
			cerr << "error" << endl;
			return;
		}
		for (int i = 0; i < 10; i++) {
			scores >> highScores[i];
		}
		scores.close();

		sortScores();
		heading.setFont(FM[0]);
		heading.setCharacterSize(120);
		heading.setFillColor(Color::White);
		heading.setString("TOP 10 HIGHSCORES");
		heading.setPosition(30, -10);
		int pos = 110;
		for (int i = 0; i < 10; i++) {
			if (i == 0 || i == 1 || i == 2) {
				medals[i].setPosition(420, pos + i * 4);
				HighScores[i].setCharacterSize(48);
			}
			else {
				HighScores[i].setCharacterSize(40);
			}

			HighScores[i].setFont(FM[0]);
			if (i < 9) HighScores[i].setString(to_string(0) + to_string(i + 1) + ". -------------------------- " + to_string(highScores[i]));
			else HighScores[i].setString(to_string(i + 1) + ". -------------------------- " + to_string(highScores[i]));
			HighScores[i].setFillColor(Color{ 255,240, (Uint8)(230 - (Uint8)(20 * i)) });
			HighScores[i].setPosition(40, pos);
			if (i == 0) {
				pos += 65;
			}
			else if (i == 1) {
				pos += 60;
			}
			else if (i == 2) {
				pos += 55;
			}
			else {
				pos += 40;
			}

		}
	}

	void run() {

		// resume remains

		while (this->window.isOpen()) {
			Event event;
			while (this->window.pollEvent(event)) {
				if (event.type == Event::Closed)
					this->window.close();
				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Escape) {
						if (this->showHighScores) {
							this->showHighScores = false;
						}
						else {
							if (!this->showMenu) {
								this->showMenu = true;
								this->remainingTime = this->remainingTime - this->runClock->getElapsedTime().asSeconds();
								delete this->runClock;
								this->runClock = nullptr;
							}
						}
						/*
						this->menu.setInMenu(true);
						this->pausedTime.restart();
						this->menu.handleEnter(this->hasStarted, this->play, this->showHighScores, this->resume, this->quit, 0);*/
					}
					else if (event.key.code == Keyboard::C) {
						system("cls");
					}
					else if (event.key.code == Keyboard::Return) {
						if (this->showMenu) {
							this->menu.handleEnter(this->showMenu, this->showHighScores, this->quit, this->hasStarted, &ZF, &sun);
							if (!this->showMenu) {
								this->runClock = new Clock();
							}
							else if (this->showHighScores) {
								initHighScores();
							}
							else if (this->quit) {
								this->window.close();
							}
						}
					}
					else if (event.key.code == Keyboard::Up) {
						if (this->showMenu && !this->showHighScores) {
							this->menu.handleUp();
						}
					}
					else if (event.key.code == Keyboard::Down) {
						if (this->showMenu && !this->showHighScores) {
							this->menu.handleDown();
						}
					}

					/*if (this->menu.inMenu()) {
						if (event.key.code == Keyboard::Up) {
							this->menu.handleUp();
						}
						else if (event.key.code == Keyboard::Down) {
							this->menu.handleDown();
						}
						else if (event.key.code == Keyboard::Enter) {
							this->menu.handleEnter(this->hasStarted, this->play, this->showHighScores, this->resume, this->quit);
							if (!this->hasStarted) {
								this->runClock.restart();
							}
							if (this->quit) {
								window.close();
							}
							if (this->showHighScores) {
								this->initHighScores();
							}

						}
					}*/
				}
				if (event.type == Event::MouseButtonPressed) {
					if (!this->showMenu && !this->showHighScores) {
						if (event.mouseButton.button == Mouse::Left) {
							int mouseX = event.mouseButton.x;
							int mouseY = event.mouseButton.y;

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
			}



			if (this->showMenu) {
				this->window.clear();
				this->menu.display(this->window);
				if (this->showHighScores) {
					this->window.draw(this->menu.getHSSprite());
					this->window.draw(this->heading);
					for (int i = 0; i < 10; i++) {
						if (i < 3) {
							this->window.draw(medals[i]);
						}
						this->window.draw(this->HighScores[i]);
					}
				}
				this->window.display();
			}

			else {
				this->window.clear();
				this->updateEverything();
				this->drawEverything();
				this->window.display();
			}



		}
	}

	void calculateTime() {
		if (this->runClock == nullptr) return;
		this->gameTime = this->remainingTime - this->runClock->getElapsedTime().asSeconds();

		string minutes = "0" + to_string((int)(this->gameTime) / 60);
		string seconds = "";
		if (((int)(this->gameTime) % 60) / 10 == 0) {
			seconds += '0';
		}
		seconds += to_string((int)(this->gameTime) % 60);
		this->timeString = minutes + ":" + seconds;
		if ((int)(this->gameTime) / 60 == 0 && (int)(this->gameTime) % 60 == 10) {
			this->TimeText.setFillColor(Color::Red);
		}
	}

};
