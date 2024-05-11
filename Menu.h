#pragma once
#include "TextureManager.h"
#include "ZombieFactory.h"

class Menu {
	// play
	// resume
	// highscores
	// exit
	Color selectedColor{ 5, 227, 96 };
	Color restColor{ 0, 34, 23 };

	Text menu[4];
	Text shadow[4];
	Sprite backgroundSprite;
	TextureManager* TMptr;
	FontManager* FMptr;
	Sprite highScoreSprite;
	int menuIndex = 0;


public:
	Menu(TextureManager* TM, FontManager* FM) :TMptr(TM), FMptr(FM) {

		backgroundSprite.setTexture(this->TMptr->getTexture("mainmenu"));
		backgroundSprite.setScale(0.73, 0.73);
		backgroundSprite.setPosition(0, 0);
		menu[0].setString("PLAY");
		menu[1].setString("RESTART");
		menu[2].setString("HIGHSCORES");
		menu[3].setString("EXIT");

		shadow[0].setString("PLAY");
		shadow[1].setString("RESTART");
		shadow[2].setString("HIGHSCORES");
		shadow[3].setString("EXIT");

		this->highScoreSprite.setTexture(this->TMptr->getTexture("highscorebg"));
		this->highScoreSprite.setScale(0.73, 0.73);
		this->highScoreSprite.setPosition(0, 0);
		this->highScoreSprite.setColor(Color(0, 0, 0, 255 * 0.4));

		for (int i = 0; i < 4; i++) {
			float xFactor = 580;

			menu[i].setFillColor(Color::Black);
			menu[i].setFont(this->FMptr->get(3));
			menu[i].setCharacterSize(92);
			if (i == 1) {
				xFactor -= 20;
			}
			else if (i == 2) {
				xFactor -= 125;
			}

			menu[i].setPosition(xFactor, 200 + i * 85);

			xFactor = 580;
			float shadowYOffset = 6;
			shadow[i].setFillColor(Color::Black);
			shadow[i].setFont(this->FMptr->get(3));
			shadow[i].setCharacterSize(92);
			if (i == 1) {
				xFactor -= 20;
			}
			else if (i == 2) {
				xFactor -= 125;
			}

			shadow[i].setPosition(xFactor, 200 + i * 85 + shadowYOffset);
		}

	};


	void handleUp() {
		this->menu[this->menuIndex].setFillColor(this->restColor);
		this->menuIndex--;
		if (this->menuIndex < 0) this->menuIndex = 3;
	}

	void handleDown() {
		this->menu[this->menuIndex].setFillColor(this->restColor);
		this->menuIndex++;
		if (this->menuIndex > 3) this->menuIndex = 0;
	}

	void handleEnter(bool& showMenu, bool& showHighScores, bool& quit, bool& hasStarted, ZombieFactory* ZF, FallingSun* sun) {
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

			return;
		case 2:
			showHighScores = true;
			return;
		case 3:
			quit = true;
			return;
		}
		/*if (j != -1) {
			play = 0;
			showHighScores = 0;
			resume = 0;
			quit = 0;
			return;
		}

		play = (this->menuIndex == 0) && (hasStarted == false);
		if (play) {
			hasStarted = true;
			menu[0].setString("Restart");
			shadow[0].setString("Restart");
			menu[0].setPosition(555, 200);
			shadow[0].setPosition(555, 206);
		}
		resume = this->menuIndex == 1;
		if (resume || play) this->inmenu = false;
		showHighScores = this->menuIndex == 2;
		quit = this->menuIndex == 3;

		cout << endl << "Play: " << play << endl;
		cout << "showHighScores: " << showHighScores << endl;
		cout << "resume: " << resume << endl;
		cout << "quit: " << quit << endl;*/
	}

	Sprite& getHSSprite() {
		return this->highScoreSprite;
	}
	void display(RenderWindow& window) {

		window.draw(backgroundSprite);

		for (int i = 0; i < 4; i++) {
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




};