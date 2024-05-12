#pragma once
#include "TextureManager.h"
#include "ZombieFactory.h"

class Menu {
	// play
	// resume
	// highscores
	// exit
	Color selectedColor{ 134, 252, 58 };
	Color restColor{ 34, 48, 25 };

	Text menu[7];
	Text shadow[7];
	Sprite backgroundSprite;
	TextureManager* TMptr;
	FontManager* FMptr;
	SoundManager* SMptr;
	Sprite highScoreSprite;
	int menuIndex = 0;


public:
	Menu(TextureManager* TM, FontManager* FM, SoundManager* SM) :TMptr(TM), FMptr(FM), SMptr(SM) {

		backgroundSprite.setTexture(this->TMptr->getTexture("mainmenu"));
		backgroundSprite.setScale(0.73, 0.73);
		backgroundSprite.setPosition(0, 0);
		menu[0].setString("PLAY");
		menu[1].setString("RESTART");
		menu[2].setString("HIGHSCORES");
		menu[3].setString("INSTRUCTIONS");
		menu[4].setString("SAVE");
		menu[5].setString("LOAD");
		menu[6].setString("EXIT");

		shadow[0].setString("PLAY");
		shadow[1].setString("RESTART");
		shadow[2].setString("HIGHSCORES");
		shadow[3].setString("INSTRUCTIONS");
		shadow[4].setString("SAVE");
		shadow[5].setString("LOAD");
		shadow[6].setString("EXIT");

		this->highScoreSprite.setTexture(this->TMptr->getTexture("highscorebg"));
		this->highScoreSprite.setScale(0.73, 0.73);
		this->highScoreSprite.setPosition(0, 0);
		this->highScoreSprite.setColor(Color(0, 0, 0, 255 * 0.4));

		for (int i = 0; i < 7; i++) {
			float xFactor = 580;
			float yFactor = i;
			//menu[i].setFillColor(Color::Black);
			menu[i].setFont(this->FMptr->get(3));
			menu[i].setCharacterSize(70);

			if (i == 1) {
				xFactor -= 25;
			}
			else if (i == 2) {
				xFactor -= 315;
			}
			else if (i == 3) {
				yFactor -= 1;
				xFactor += 130;
			}
			else if (i == 4) {
				xFactor -= 100;
				yFactor -= 1;
			}
			else if (i == 5) {
				yFactor -= 2;
				xFactor += 100;
			}
			else if (i == 6) {
				yFactor -= 2;
			}

			menu[i].setPosition(xFactor, 200 + yFactor * 75);

			xFactor = 580;
			yFactor = i;
			float shadowYOffset = 6;
			shadow[i].setFillColor(Color(41, 39, 39));
			shadow[i].setFont(this->FMptr->get(3));
			shadow[i].setCharacterSize(70);
			if (i == 1) {
				xFactor -= 25;
			}
			else if (i == 2) {
				xFactor -= 315;
			}
			else if (i == 3) {
				yFactor -= 1;
				xFactor += 130;
			}
			else if (i == 4) {
				xFactor -= 100;
				yFactor -= 1;
			}
			else if (i == 5) {
				yFactor -= 2;
				xFactor += 100;
			}
			else if (i == 6) {
				yFactor -= 2;
			}
			shadow[i].setPosition(xFactor, 200 + yFactor * 75 + shadowYOffset);


		}

	};

	void setMenuIndex(int val) {
		this->menuIndex = val;
	}

	void handleUp() {
		this->SMptr->playSound("change");
		this->menu[this->menuIndex].setFillColor(this->restColor);
		this->menuIndex--;
		if (this->menuIndex < 0) this->menuIndex = 6;
	}

	void handleDown() {
		this->SMptr->playSound("change");
		this->menu[this->menuIndex].setFillColor(this->restColor);
		this->menuIndex++;
		if (this->menuIndex > 6) this->menuIndex = 0;
	}

	void handleEnter(bool& saveGame, bool& loadGame, bool& showInstructions, bool& showMenu, bool& showHighScores, bool& quit, bool& hasStarted, bool& restarted, ZombieFactory* ZF, FallingSun* sun) {
		this->SMptr->playSound("enter");
		switch (this->menuIndex) {
		case 0:
			showMenu = false;
			if (!hasStarted) {
				hasStarted = true;
				this->menu[0].setString("RESUME");
				this->shadow[0].setString("RESUME");
			}
			ZF->restartSpawnClock();
			sun->restartGenerateClock();
			return;
		case 1:
			if (hasStarted) {
				showMenu = false;
				restarted = true;
			}
			return;
		case 2:
			showHighScores = true;
			return;
		case 3:
			showInstructions = true;
			return;
		case 4:
			saveGame = true;
			return;
		case 5:
			loadGame = true;
			return;
		case 6:
			quit = true;
			return;
		}

	}

	Sprite& getHSSprite() {
		return this->highScoreSprite;
	}
	void display(RenderWindow& window) {

		window.draw(backgroundSprite);

		for (int i = 0; i < 7; i++) {
			if (this->menuIndex == i) {
				this->menu[i].setFillColor(selectedColor);
			}
			else {
				this->menu[i].setFillColor(restColor);
			}
			window.draw(this->shadow[i]);
			window.draw(this->menu[i]);
		}


	}


	void reset() {
		this->menu[0].setString("PLAY");
		this->shadow[0].setString("PLAY");
	}

};