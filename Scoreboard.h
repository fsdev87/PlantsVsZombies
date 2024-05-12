#pragma once
#include "FontManager.h"

class Scoreboard {
private:
	int score;
	Text scoreText;
	Text scoreTextS;
public:
	Scoreboard(FontManager* FM) {
		this->score = 0;
		this->scoreText.setFont(FM->get(3));
		this->scoreText.setCharacterSize(48);
		this->scoreText.setPosition(10, 540);
		this->scoreText.setString("Score: " + to_string(this->score));
		this->scoreText.setFillColor(Color(245, 245, 245));

		this->scoreTextS.setFont(FM->get(3));
		this->scoreTextS.setCharacterSize(49);
		this->scoreTextS.setPosition(10, 541);
		scoreTextS.setString("Score: " + to_string(this->score));
		this->scoreTextS.setFillColor(Color(181, 96, 40));
	}
	void addScore(int n) {
		this->score += n;
		this->scoreText.setString("Score: " + to_string(this->score));
		this->scoreTextS.setString("Score: " + to_string(this->score));
	}

	int getScore() { return this->score; }

	void draw(RenderWindow& window) {
		window.draw(this->scoreTextS);
		window.draw(this->scoreText);
	}
};