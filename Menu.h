#pragma once
#include "TextureManager.h"

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
	int index = 0;

	bool inmenu = true;
public:
	Menu(TextureManager* TM, FontManager* FM) :TMptr(TM), FMptr(FM) {

		backgroundSprite.setTexture(this->TMptr->getTexture("mainmenu"));
		backgroundSprite.setScale(0.73, 0.73);
		backgroundSprite.setPosition(0, 0);
		menu[0].setString("Play");
		menu[1].setString("Resume");
		menu[2].setString("HighScores");
		menu[3].setString("Exit");

		shadow[0].setString("Play");
		shadow[1].setString("Resume");
		shadow[2].setString("HighScores");
		shadow[3].setString("Exit");

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

	bool inMenu() { return this->inmenu; }
	void setInMenu(bool val) { this->inmenu = val; }

	void handleUp() {
		menu[index].setFillColor(restColor);
		index -= 1;
		if (index < 0) index = 3;
	}

	void handleDown() {
		menu[index].setFillColor(restColor);
		index += 1;
		if (index > 3) index = 0;
	}

	void handleEnter(bool& hasStarted, bool& play, bool& showHighScores, bool& resume, bool& quit, int j = -1) {
		if (j != -1) {
			play = 0;
			showHighScores = 0;
			resume = 0;
			quit = 0;
			return;
		}

		play = (this->index == 0) && (hasStarted == false);
		if (play) {
			hasStarted = true;
			menu[0].setString("Restart");
			shadow[0].setString("Restart");
			menu[0].setPosition(555, 200 + 0 * 85);
			shadow[0].setPosition(555, 200 + 0 * 85 + 6);
		}
		resume = this->index == 1;
		showHighScores = this->index == 2;
		quit = this->index == 3;

		cout << endl << "Play: " << play << endl;
		cout << "showHighScores: " << showHighScores << endl;
		cout << "resume: " << resume << endl;
		cout << "quit: " << quit << endl;
	}

	Sprite& getHSSprite() {
		return this->highScoreSprite;
	}
	void display(RenderWindow& window) {

		window.draw(backgroundSprite);

		for (int i = 0; i < 4; i++) {
			if (this->index == i) {
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