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
#include "Garden.h"
#include "FallingSun.h"
#include "Menu.h"
#include <cmath>
#include "Scoreboard.h"

#include "BeginnersGarden.h"
#include "FullGarden.h"
#include "NightGarden.h"
#include "LimitedGarden.h"
#include "GameOver.h"
#include "NextLevel.h"

class Game {
	// window
	RenderWindow window;
	TextureManager TM;
	SoundManager SM;
	FontManager FM;
	Background background;
	Inventory Inv;

	// gameover things
	GameOver gameover;
	string playerName = "";
	Text nameText;

	Text enterName;
	Text enterNameS;
	Text pressEnter;
	Text pressEnterS;
	//

	// win things
	Sprite winSprite;
	//

	// level delay things
	NextLevel NL;
	float levelDelay = 5;
	Clock levelDelayClock;
	bool nextLevel = false;


	int sunCount = 100;
	Text sunCountText;


	PlantFactory PF;
	ZombieFactory ZF;

	LawnMower* lawnmowers[5]{ nullptr };
	float lawnMowerPos[2] = { -1, 0 };

	Life lives;

	FallingSun sun;


	string timeString;
	Text TimeText;

	Menu menu;

	bool showMenu = true;
	bool showHighScores = false;
	bool quit = false;
	bool restarted = false;
	bool hasStarted = false;
	bool showInstructions = false;
	bool gameOver = false;
	bool hasWon = false;

	bool saveGame = false;
	bool loadGame = false;


	int highScores[10] = {};
	string names[10] = {};
	Text HighScores[10], heading;
	Sprite medals[3];

	Text instructionHeading, instructionHeadingShadow, Instructions[10], pageNumber;
	int instructionStartIndex = 0;
	int instructionEndIndex = 3;
	int pageNo = 1;
	Sprite instructionDecoration[6];

	// time handling things
	float gameTime;
	Clock* runClock = nullptr;
	float remainingTime = 120;
	//float remainingTime = 5; // for testing
	Level** levels = new Level * [4];
	int levelIndex = 0;



	Scoreboard score;


public:
	Game() : window(VideoMode(1400, 600), "game"), background(&TM), Inv(&TM, &SM), PF(&SM, &TM), ZF(&TM, &SM), menu(&TM, &FM, &SM), score(&FM), NL(&TM) {


		levels[0] = new BeginnersGarden{ background, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score };
		levels[1] = nullptr;
		levels[2] = nullptr;
		levels[3] = nullptr;

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

		this->sunCountText.setFont(FM[0]);
		this->sunCountText.setString(to_string(this->sunCount));
		this->sunCountText.setCharacterSize(24);
		this->sunCountText.setPosition(86, 62);
		this->sunCountText.setFillColor(Color::Black);

		for (int i = 0; i < 5; i++) {
			this->lawnMowerPos[1] = i;
			this->lawnmowers[i] = new LawnMower(&TM, this->lawnMowerPos);
		}

		// name text
		this->nameText.setFont(this->FM[3]);
		this->nameText.setCharacterSize(65);
		this->nameText.setPosition(580, 485);
		this->nameText.setString(this->playerName);
		this->nameText.setFillColor(Color::White);

		this->enterName.setFont(this->FM[3]);
		this->enterName.setCharacterSize(50);
		this->enterName.setPosition(100, 500);
		this->enterName.setString("Enter your name: ");
		this->enterName.setFillColor(Color::White);

		this->enterNameS.setFont(this->FM[3]);
		this->enterNameS.setCharacterSize(50);
		this->enterNameS.setPosition(100, 503);
		this->enterNameS.setString("Enter your name: ");
		this->enterNameS.setFillColor(Color::Green);

		this->pressEnter.setFont(this->FM[3]);
		this->pressEnter.setCharacterSize(25);
		this->pressEnter.setPosition(550, 560);
		this->pressEnter.setString("Press enter to continue.");
		this->pressEnter.setFillColor(Color::White);

		this->pressEnterS.setFont(this->FM[3]);
		this->pressEnterS.setCharacterSize(25);
		this->pressEnterS.setPosition(550, 563);
		this->pressEnterS.setString("Press enter to continue.");
		this->pressEnterS.setFillColor(Color::Green);

		initHighScores();

		// win screen
		this->winSprite = Sprite(this->TM.getTexture("win"));
		this->winSprite.setPosition(0, 0);

		this->SM.getMainMusic()->play();
		this->SM.getMainMusic()->setLoop(true);
		this->SM.getMainMusic()->setVolume(40);
	}

private:

	void saveEverything() {

		cout << "Opened file to write\n";
		ofstream file;
		file.open("saved.dat", ios::out | ios::binary);

		file.write(reinterpret_cast<char*>(&levelIndex), sizeof(int));

		file.write(reinterpret_cast<char*>(&sunCount), sizeof(int));

		file.write(reinterpret_cast<char*>(&showMenu), sizeof(bool));
		file.write(reinterpret_cast<char*>(&showHighScores), sizeof(bool));
		file.write(reinterpret_cast<char*>(&quit), sizeof(bool));
		file.write(reinterpret_cast<char*>(&restarted), sizeof(bool));
		file.write(reinterpret_cast<char*>(&hasStarted), sizeof(bool));
		file.write(reinterpret_cast<char*>(&showInstructions), sizeof(bool));
		file.write(reinterpret_cast<char*>(&gameOver), sizeof(bool));
		file.write(reinterpret_cast<char*>(&hasWon), sizeof(bool));
		file.write(reinterpret_cast<char*>(&nextLevel), sizeof(bool));

		file.write(reinterpret_cast<char*>(&gameTime), sizeof(float));
		file.write(reinterpret_cast<char*>(&remainingTime), sizeof(float));

		PF.saveEverything(file);
		ZF.saveEverything(file);
		score.saveEverything(file);
		//Inv.saveEverything(file);
		for (int i = 0; i < 5; i++) lawnmowers[i]->saveEverything(file);
		lives.saveEverything(file);

		sun.saveEverything(file);


		levels[levelIndex]->saveEverything(file);

		file.close();

		cout << "Finished writing\n";

	}

	void readEverything() {
		cout << "Opening to read\n";
		ifstream file;
		file.open("saved.dat", ios::in | ios::binary);

		cout << "Reading game.h primitive data types\n";
		file.read(reinterpret_cast<char*>(&levelIndex), sizeof(int));

		file.read(reinterpret_cast<char*>(&sunCount), sizeof(int));
		this->sunCount = sunCount;
		this->sunCountText.setString(to_string(this->sunCount));

		file.read(reinterpret_cast<char*>(&showMenu), sizeof(bool));
		file.read(reinterpret_cast<char*>(&showHighScores), sizeof(bool));
		file.read(reinterpret_cast<char*>(&quit), sizeof(bool));
		file.read(reinterpret_cast<char*>(&restarted), sizeof(bool));
		file.read(reinterpret_cast<char*>(&hasStarted), sizeof(bool));
		file.read(reinterpret_cast<char*>(&showInstructions), sizeof(bool));
		file.read(reinterpret_cast<char*>(&gameOver), sizeof(bool));
		file.read(reinterpret_cast<char*>(&hasWon), sizeof(bool));
		file.read(reinterpret_cast<char*>(&nextLevel), sizeof(bool));
		this->showMenu = false;
		this->hasStarted = true;

		if (!this->runClock)
			this->runClock = new Clock;

		file.read(reinterpret_cast<char*>(&gameTime), sizeof(float));
		file.read(reinterpret_cast<char*>(&remainingTime), sizeof(float));


		cout << "Reading plant factory\n";
		PF.readEverything(file);

		cout << "Reading zombie factory\n";
		ZF.readEverything(file);


		cout << "Reading scores\n";
		score.readEverything(file);

		cout << "Reading inventory\n";
		//Inv.readEverything(file);

		cout << "Reading lawnmowers\n";
		for (int i = 0; i < 5; i++) lawnmowers[i]->readEverything(file);



		cout << "Reading lives\n";
		lives.readEverything(file);
		// 
		cout << "Reading suns\n";
		sun.readEverything(file);
		// 
		cout << "Reading levels " << levelIndex << "\n";


		if (levels[levelIndex] == nullptr && levelIndex == 0) {

			/*Inv.addCard(this->TM.getTexture("card-sunflower_dim"), this->TM.getTexture("card-sunflower"), "sunflower", 50);
			Inv.addCard(this->TM.getTexture("card-peashooter_dim"), this->TM.getTexture("card-peashooter"), "peashooter", 100);*/
			levels[levelIndex] = new BeginnersGarden{ background, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score };
		}
		else if (levels[levelIndex] == nullptr && levelIndex == 1) {
			//Inv.addCard(this->TM.getTexture("card-sunflower_dim"), this->TM.getTexture("card-sunflower"), "sunflower", 50);
			//Inv.addCard(this->TM.getTexture("card-peashooter_dim"), this->TM.getTexture("card-peashooter"), "peashooter", 100);
			//Inv.addCard(this->TM.getTexture("card-repeater_dim"), this->TM.getTexture("card-repeater"), "repeater", 200);
			//Inv.addCard(this->TM.getTexture("card-wallnut_dim"), this->TM.getTexture("card-wallnut"), "wallnut", 50);
			cout << "Level was full garden\n";
			levels[0] = new BeginnersGarden{ background, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score };
			levels[levelIndex] = new FullGarden{ background, &PF, &ZF, &Inv, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score, 1 };
		}
		else if (levels[levelIndex] == nullptr && levelIndex == 2) {
			// Inv.addCard(this->TM.getTexture("card-sunflower_dim"), this->TM.getTexture("card-sunflower"), "sunflower", 50);
			// Inv.addCard(this->TM.getTexture("card-peashooter_dim"), this->TM.getTexture("card-peashooter"), "peashooter", 100);
			// Inv.addCard(this->TM.getTexture("card-repeater_dim"), this->TM.getTexture("card-repeater"), "repeater", 200);
			// Inv.addCard(this->TM.getTexture("card-wallnut_dim"), this->TM.getTexture("card-wallnut"), "wallnut", 50);
			// Inv.addCard(this->TM.getTexture("card-snowpea_dim"), this->TM.getTexture("card-snowpea"), "snowpea", 175);
			// Inv.addCard(this->TM.getTexture("card-cherrybomb_dim"), this->TM.getTexture("card-cherrybomb"), "cherrybomb", 150);
			// Inv.addCard(this->TM.getTexture("shovel"), this->TM.getTexture("shovel"), "shovel", 0);
			levels[0] = new BeginnersGarden{ background, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score };
			levels[1] = new FullGarden{ background, &PF, &ZF, &Inv, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score , 1 };
			levels[levelIndex] = new NightGarden{ background, &PF, &ZF, &Inv, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score, 1 };
		}
		else if (levels[levelIndex] == nullptr && levelIndex == 3) {
			// Inv.addCard(this->TM.getTexture("card-sunflower_dim"), this->TM.getTexture("card-sunflower"), "sunflower", 50);
			// Inv.addCard(this->TM.getTexture("card-peashooter_dim"), this->TM.getTexture("card-peashooter"), "peashooter", 100);
			// Inv.addCard(this->TM.getTexture("card-repeater_dim"), this->TM.getTexture("card-repeater"), "repeater", 200);
			// Inv.addCard(this->TM.getTexture("card-wallnut_dim"), this->TM.getTexture("card-wallnut"), "wallnut", 50);
			// Inv.addCard(this->TM.getTexture("card-snowpea_dim"), this->TM.getTexture("card-snowpea"), "snowpea", 175);
			// Inv.addCard(this->TM.getTexture("card-cherrybomb_dim"), this->TM.getTexture("card-cherrybomb"), "cherrybomb", 150);
			// Inv.addCard(this->TM.getTexture("shovel"), this->TM.getTexture("shovel"), "shovel", 0);
			levels[0] = new BeginnersGarden{ background, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score };
			levels[1] = new FullGarden{ background, &PF, &ZF, &Inv, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score , 1 };
			levels[2] = new NightGarden{ background, &PF, &ZF, &Inv, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score , 1 };
			levels[levelIndex] = new LimitedGarden{ background, &PF, &ZF, &Inv, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score, 1 };
		}
		levels[levelIndex]->readEverything(file);


		file.close();
		cout << "Finished reading\n";

	}

	void restartGame() {
		this->restarted = false, this->showMenu = false, this->showHighScores = false; // maybe redundant work
		this->hasWon = false;

		this->menu.setMenuIndex(0);
		this->remainingTime = 120;
		this->runClock = new Clock;
		this->TimeText.setFillColor(Color::Black);
		this->sunCount = 100;
		this->PF.reset();
		this->ZF.reset();
		this->lives.reset();
		this->sun.reset();
		this->Inv.reset();

		this->playerName = "";
		this->score.resetScore();

		for (int i = 0; i < 5; i++) {
			this->lawnMowerPos[1] = i;
			this->lawnmowers[i] = new LawnMower(&TM, this->lawnMowerPos);
		}

		if (this->levels[0] != nullptr) delete this->levels[0];
		levels[0] = new BeginnersGarden{ background, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score };
		if (this->levels[1] != nullptr) delete this->levels[1];
		levels[1] = nullptr;
		if (this->levels[2] != nullptr) delete this->levels[2];
		levels[2] = nullptr;
		if (this->levels[3] != nullptr) delete this->levels[3];
		levels[3] = nullptr;
		this->levelIndex = 0;
	}

	void updateRound() {
		this->runClock->restart();
		this->levelIndex++;
		this->remainingTime = 120;
		//this->remainingTime = 5; //for testing
		this->TimeText.setFillColor(Color::Black);
		this->sun.reset();
		this->sunCount = 100;


		if (levels[levelIndex] == nullptr && levelIndex == 1) {
			levels[levelIndex] = new FullGarden{ background, &PF, &ZF, &Inv, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score };
		}
		else if (levels[levelIndex] == nullptr && levelIndex == 2) {
			levels[levelIndex] = new NightGarden{ background, &PF, &ZF, &Inv, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score };
		}
		else if (levels[levelIndex] == nullptr && levelIndex == 3) {
			levels[levelIndex] = new LimitedGarden{ background, &PF, &ZF, &Inv, &TM, &FM, &SM, runClock, &sunCountText,  sunCount, lawnmowers, lawnMowerPos, &score };
		}
	}

	void drawEverything() {
		if (this->hasWon || this->levelIndex > 3) return;
		levels[levelIndex]->drawEverything(this->window, this->background, &Inv, sunCount, &PF, &ZF, lawnmowers, lives, &sun, sunCountText);
		this->window.draw(this->TimeText);
		this->score.draw(this->window);
	}

	void updateEverything() {
		if (this->hasWon || this->levelIndex > 3) return;
		levels[levelIndex]->updateEverything(&PF, &ZF, lawnmowers, lives, sun);
		calculateTime();
		this->TimeText.setString("TIME: " + this->timeString);

		if (this->lives.livesGone()) {
			this->gameOver = true;
			this->SM.getSound("gameover")->play();
			this->SM.getMainMusic()->stop();
		}

		if (this->gameTime <= 0) {
			this->nextLevel = true;
			this->levelDelayClock.restart();

			this->updateRound();
		}

	}

	void sortScores() {
		bool swapped;
		for (int i = 0; i < 9; i++) {
			swapped = false;
			for (int j = 0; j < 10 - i - 1; j++) {
				if (this->highScores[j] < this->highScores[j + 1]) {
					swap(this->highScores[j], this->highScores[j + 1]);
					swap(this->names[j], this->names[j + 1]);
					swapped = true;
				}
			}

			if (swapped == false)
				break;
		}
	}

	void initHighScores() {

		this->menu.getHSSprite().setColor(Color(0, 0, 0, 255 * 0.4));
		ifstream scores("highscores.txt");
		if (!scores.is_open()) {
			cerr << "error" << endl;
			return;
		}
		ifstream playerNames("names.txt");
		if (!playerNames.is_open()) {
			cerr << "error" << endl;
			return;
		}
		for (int i = 0; i < 10; i++) {
			scores >> this->highScores[i];
			playerNames >> this->names[i];
		}

		scores.close();
		playerNames.close();

		sortScores();
		heading.setFont(FM[0]);
		heading.setCharacterSize(120);
		heading.setFillColor(Color::White);
		heading.setString("TOP 10 HIGHSCORES");
		heading.setPosition(30, -10);
		int pos = 110;
		for (int i = 0; i < 10; i++) {
			if (i == 0 || i == 1 || i == 2) {
				medals[i].setPosition(40, pos + i * 4);
				HighScores[i].setCharacterSize(48);
			}
			else {
				HighScores[i].setCharacterSize(40);
			}

			HighScores[i].setFont(FM[0]);
			if (i < 9) HighScores[i].setString(to_string(0) + to_string(i + 1) + ". " + this->names[i] + " ---------------- " + to_string(this->highScores[i]));
			else HighScores[i].setString(to_string(i + 1) + ". " + this->names[i] + " ---------------- " + to_string(this->highScores[i]));
			HighScores[i].setFillColor(Color{ 255,240, (Uint8)(230 - (Uint8)(20 * i)) });
			HighScores[i].setPosition(90, pos);
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

	void initInstructions() {



		this->instructionDecoration[0].setTexture(this->TM.getTexture("deco-w"));
		this->instructionDecoration[0].setRotation(10.0f);

		this->instructionDecoration[1].setTexture(this->TM.getTexture("deco-p"));
		this->instructionDecoration[1].setRotation(6.0f);

		this->instructionDecoration[2].setTexture(this->TM.getTexture("deco-r"));

		this->instructionDecoration[5].setTexture(this->TM.getTexture("deco-fz"));
		this->instructionDecoration[4].setRotation(5.0f);
		this->instructionDecoration[4].setTexture(this->TM.getTexture("deco-dz"));

		this->instructionDecoration[3].setTexture(this->TM.getTexture("deco-z"));
		this->instructionDecoration[3].setRotation(10.0f);


		this->menu.getHSSprite().setColor(Color(0, 0, 0, 255 * 0.6));
		this->instructionHeading.setFont(FM[1]);
		this->instructionHeading.setCharacterSize(110);
		this->instructionHeading.setFillColor(Color::Green);
		this->instructionHeading.setString("INSTRUCTIONS");
		this->instructionHeading.setPosition(30, -10);

		this->instructionHeadingShadow.setFont(FM[1]);
		this->instructionHeadingShadow.setCharacterSize(111);
		this->instructionHeadingShadow.setFillColor(Color(0, 0, 0, 150));
		this->instructionHeadingShadow.setString("INSTRUCTIONS");
		this->instructionHeadingShadow.setPosition(30, -5);

		this->pageNumber.setFont(FM[1]);
		this->pageNumber.setCharacterSize(80);
		this->pageNumber.setFillColor(Color::White);
		this->pageNumber.setString(to_string(this->pageNo));
		this->pageNumber.setPosition(1300, 500);

		for (int i = 0; i < 10; i++) {
			this->Instructions[i].setFont(FM[3]);
			this->Instructions[i].setCharacterSize(58);
			this->Instructions[i].setFillColor(Color::White);
		}

		this->Instructions[0].setPosition(30, 100);
		this->Instructions[0].setString("1. Place defensive plants strategically to \nfend off zombies.");
		this->instructionDecoration[0].setPosition(800, 20);

		this->Instructions[1].setPosition(30, 240);
		this->Instructions[1].setString("2. Utilize offensive plants like Peashooter\n to launch counterattacks\n against enemy forces.");
		this->instructionDecoration[1].setPosition(1000, 280);

		this->Instructions[2].setPosition(30, 435);
		this->Instructions[2].setString("3. Collect resources to unlock \nmore plants and abilities.");
		this->instructionDecoration[2].setPosition(950, 470);

		this->Instructions[3].setPosition(30, 100);
		this->Instructions[3].setString("4. Deploy support units to assist your main \nforces during battles.");
		this->instructionDecoration[3].setPosition(300, 50);

		this->Instructions[4].setPosition(30, 240);
		this->Instructions[4].setString("5. Use special abilities wisely to turn \nthe tide of difficult encounters.");
		this->instructionDecoration[4].setPosition(850, 180);

		this->Instructions[5].setPosition(30, 380);
		this->Instructions[5].setString("6. Defend your base or territory from \nincoming enemy waves.");
		this->instructionDecoration[5].setPosition(960, 450);

		/*Instructions[6].setString();
		Instructions[7].setString("Complete missions and challenges to earn rewards and progress in the game.");
		Instructions[8].setString("Upgrade your structures and defenses to withstand stronger enemy assaults.");
		Instructions[9].setString("Manage your resources efficiently to maintain a strong and balanced army.");
		Instructions[10].setString("Strategize your moves carefully to outsmart and defeat your opponents.");*/


	}

	void updateInstructions(int positive = 1) {
		if (positive == -1) {
			this->pageNo -= 1;
			if (this->pageNo < 1) {
				this->pageNo = 1;
				return;
			}
			this->instructionStartIndex -= 3;


			this->instructionEndIndex -= 3;

		}
		else if (positive) {
			this->pageNo += 1;
			if (this->pageNo > 2) {
				this->pageNo = 2;
				return;
			}
			this->instructionStartIndex += 3;
			this->instructionEndIndex += 3;
		}
		this->pageNumber.setString(to_string(this->pageNo));

	}

public:
	void run() {


		while (this->window.isOpen()) {
			Event event;
			while (this->window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					this->window.close();
				}
				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Escape) {
						this->SM.playSound("enter");
						if (this->showHighScores) {
							this->showHighScores = false;
						}
						else if (this->showInstructions) {
							this->showInstructions = false;
						}
						else {
							if (!this->showMenu && !this->nextLevel) {
								this->showMenu = true;
								if (this->runClock) {
									this->remainingTime = this->remainingTime - this->runClock->getElapsedTime().asSeconds();
								}
								if (this->runClock) delete this->runClock;
								this->runClock = nullptr;
							}
						}
					}

					else if (event.key.code == Keyboard::Return) {
						if (this->showMenu) {
							this->menu.handleEnter(this->saveGame, this->loadGame, this->showInstructions, this->showMenu, this->showHighScores, this->quit, this->hasStarted, restarted, &ZF, &sun);
							if (!this->showMenu && !this->restarted) { // resume or start mode
								this->runClock = new Clock();
							}
							else if (this->restarted) {
								restartGame();
							}
							else if (this->showHighScores) {
								initHighScores();
							}
							else if (this->showInstructions) {
								initInstructions();
							}
							else if (this->saveGame) {
								this->saveEverything();
								saveGame = false;
							}
							else if (this->loadGame) {
								this->readEverything();
								loadGame = false;
							}
							else if (this->quit) {
								this->window.close();
							}
						}
						else if (this->gameOver || this->hasWon) {
							if (this->gameOver) this->gameOver = false;
							else if (this->hasWon) this->hasWon = false;
							this->SM.getMainMusic()->play();
							this->SM.getMainMusic()->setLoop(true);
							this->SM.getMainMusic()->setVolume(40);
							// highscores updating
							this->highScores[9] = this->score.getScore();
							this->names[9] = this->playerName;
							sortScores();
							ofstream scores("highscores.txt");
							ofstream playerNames("names.txt");
							if (!scores.is_open()) {
								cerr << "Error" << endl;
								return;
							}
							if (!playerNames.is_open()) {
								cerr << "Error" << endl;
								return;
							}

							for (int i = 0; i < 10; i++) {
								scores << this->highScores[i] << endl;
								playerNames << this->names[i] << endl;
							}
							scores.close();
							playerNames.close();

							restartGame();
							this->showMenu = true;
							this->menu.reset();
						}
					}
					else if (event.key.code == Keyboard::Up) {
						if (this->showMenu && !this->showHighScores && !this->showInstructions) {
							this->menu.handleUp();
						}
					}
					else if (event.key.code == Keyboard::Down) {
						if (this->showMenu && !this->showHighScores && !this->showInstructions) {
							this->menu.handleDown();
						}
					}
					else if (event.key.code == Keyboard::Right) {
						this->SM.playSound("enter");
						if (this->showInstructions) {
							updateInstructions();
						}
					}
					else if (event.key.code == Keyboard::Left) {
						this->SM.playSound("enter");
						if (this->showInstructions) {
							updateInstructions(-1);
						}
					}
				}
				else if (event.type == Event::TextEntered) {
					if (this->gameOver || this->hasWon) {
						if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 27 && this->playerName.length() < 15) { // shouldn't be backspace
							this->playerName += static_cast<char>(event.text.unicode);
							this->nameText.setString(this->playerName);
						}
						else if (event.text.unicode == 8) { // backspace pressed
							if (this->playerName.length() > 0) {
								string temp = this->playerName;
								this->playerName = "";
								for (int i = 0; i < temp.length() - 1; i++) {
									this->playerName += temp[i];
								}
								this->nameText.setString(this->playerName);
							}
						}
					}
				}
				else if (event.type == Event::MouseButtonPressed) {
					if (!this->showMenu && !this->showHighScores) {
						if (event.mouseButton.button == Mouse::Left) {
							int mouseX = event.mouseButton.x;
							int mouseY = event.mouseButton.y;

							if (gardenCords.valid(mouseX, mouseY)) {
								cout << "Position on Grid: " << (mouseY - gardenCords.topY) / 96 << ", " << (mouseX - gardenCords.leftX) / 80 << endl;

								// Handle placing of plants
								int gy = (mouseY - gardenCords.topY) / 96;
								int gx = (mouseX - gardenCords.leftX) / 80;
								this->PF.handleSunClick(gx, gy, this->sunCountText, this->sunCount);
								this->PF.handlePlacing(&this->Inv, gx, gy, this->sunCount, this->levelIndex + 1);
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


			if (this->showMenu && !this->gameOver && !this->hasWon && !this->nextLevel && !this->saveGame && !this->loadGame) {
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
				else if (this->showInstructions) {
					this->window.draw(this->menu.getHSSprite());
					this->window.draw(this->instructionHeadingShadow);
					this->window.draw(this->instructionHeading);

					for (int i = this->instructionStartIndex; i < this->instructionEndIndex; i++) {
						this->window.draw(this->instructionDecoration[i]);
						this->window.draw(this->Instructions[i]);
					}

					this->window.draw(this->pageNumber);

				}
				this->window.display();
			}
			else if ((this->gameOver || this->hasWon) && (!this->saveGame && !this->loadGame)) {
				this->window.clear();
				if (this->gameOver) {
					this->gameover.draw(this->window);
				}
				else if (this->hasWon) {
					this->window.draw(this->winSprite);
				}
				this->window.draw(this->nameText);
				this->window.draw(this->enterNameS);
				this->window.draw(this->pressEnterS);

				this->window.draw(this->enterName);
				this->window.draw(this->pressEnter);

				this->window.display();
			}
			else if (this->nextLevel) {
				if (this->levelIndex > 3) {
					this->nextLevel = false;
				}
				else {
					if (this->levelDelayClock.getElapsedTime().asSeconds() < this->levelDelay) {
						this->window.clear();
						this->NL.drawLevel(this->window, this->levelIndex);
						this->window.display();
						this->PF.reset();
						this->ZF.reset();
						this->sun.reset();
						this->runClock->restart();
					}
					else {
						this->nextLevel = false;
					}
				}
			}
			else {
				this->window.clear();
				if (this->levelIndex > 3) {
					this->hasWon = true;
				}
				if (!this->nextLevel) {
					this->updateEverything();
					this->drawEverything();
				}
				this->window.display();
			}

		}

	}
private:
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