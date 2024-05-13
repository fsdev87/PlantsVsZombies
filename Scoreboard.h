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

		rect.setSize(Vector2f(245, 60));
		rect.setFillColor(Color(191, 105, 44, 245));
		rect.setPosition(5, 540);
	}

	void saveEverything(ofstream& file) {

		file.write(reinterpret_cast<char*>(&score), sizeof(int));
		this->scoreText.setString("Score: " + to_string(this->score));

	}

	void readEverything(ifstream& file) {

		file.read(reinterpret_cast<char*>(&score), sizeof(int));

	}
	void addScore(int n) {
		this->score += n;
		this->scoreText.setString("Score: " + to_string(this->score));

		if (this->score > 100) {
			rect.setSize(Vector2f(260, 60));
		}
		else if (this->score > 1000) {
			rect.setSize(Vector2f(350, 60));
		}
		else if (this->score > 10000) {
			rect.setScale(Vector2f(380, 60));
		}
	}

	int getScore() { return this->score; }

	void draw(RenderWindow& window) {
		window.draw(this->rect);
		window.draw(this->scoreText);
	}

	void resetScore() { this->score = 0; this->scoreText.setString("Score: " + to_string(this->score)); }
};