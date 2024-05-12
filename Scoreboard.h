#pragma once
#include "FontManager.h"

class Scoreboard {
private:
	int score;
	Text scoreText;
	RectangleShape rect;
public:
	Scoreboard(FontManager* FM) {
		this->score = 0;
		this->scoreText.setFont(FM->get(3));
		this->scoreText.setCharacterSize(48);
		this->scoreText.setPosition(10, 540);
		this->scoreText.setString("Score: " + to_string(this->score));
		this->scoreText.setFillColor(Color::White);

		rect.setSize(Vector2f(225, 60));
		rect.setFillColor(Color(191, 105, 44, 255));
		rect.setPosition(5, 540);
	}
	void addScore(int n) {
		this->score += n;
		this->scoreText.setString("Score: " + to_string(this->score));
	}

	int getScore() { return this->score; }

	void draw(RenderWindow& window) {
		window.draw(this->rect);
		window.draw(this->scoreText);
	}

	void resetScore() { this->score = 0; }
};