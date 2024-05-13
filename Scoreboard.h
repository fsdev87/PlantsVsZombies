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
		this->scoreText.setPosition(670, 2);
		this->scoreText.setString("Score: " + to_string(this->score));
		this->scoreText.setFillColor(Color::White);

		this->scoreTextS.setFont(FM->get(3));
		this->scoreTextS.setCharacterSize(49);
		this->scoreTextS.setPosition(670, 6);
		this->scoreTextS.setString("Score: " + to_string(this->score));
		this->scoreTextS.setFillColor(Color(89, 46, 12));


	}

	void saveEverything(ofstream& file) {

		file.write(reinterpret_cast<char*>(&score), sizeof(int));


	}

	void readEverything(ifstream& file) {

		file.read(reinterpret_cast<char*>(&score), sizeof(int));
		this->scoreText.setString("Score: " + to_string(this->score));
		this->scoreTextS.setString("Score: " + to_string(this->score));

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

	void resetScore() { this->score = 0; this->scoreText.setString("Score: " + to_string(this->score)); }
};