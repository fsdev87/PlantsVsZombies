#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Life {
private:
	Sprite sprites[3];
	Texture texture;
	int lifeIndex = 3;
	Font lifeFont;
	Text lifeText;

public:
	Life() {
		this->texture.loadFromFile("assets/Static/life.png");
		float posX = 12.75;
		for (int i = 0; i < 3; i++) {
			this->sprites[i].setTexture(this->texture);
			this->sprites[i].setPosition(posX * 80 + 140, 8);
			posX += 0.5;
		}
		this->lifeFont.loadFromFile("assets/fonts/lives.ttf");
		this->lifeText = Text("LIVES: ", this->lifeFont, 50);
		this->lifeText.setPosition(1000, 0);
		this->lifeText.setFillColor(Color::Black);
	}

	void saveEverything(ofstream& file) {
		file.write(reinterpret_cast<char*>(&lifeIndex), sizeof(int));
	}

	void readEverything(ifstream& file) {
		file.read(reinterpret_cast<char*>(&lifeIndex), sizeof(int));
	}

	void decrementLives() {
		if (this->lifeIndex == 0) return;
		this->lifeIndex--;
		if (this->lifeIndex == 1) {
			this->lifeText.setFillColor(Color::Red);
		}
	}

	void drawLives(RenderWindow& window) {
		window.draw(this->lifeText);
		for (int i = 0; i < this->lifeIndex; i++) {
			window.draw(this->sprites[i]);
		}
	}

	void reset() {
		this->lifeIndex = 3;
		this->lifeText.setFillColor(Color::Black);
	}

	bool livesGone() {
		return (this->lifeIndex <= 0);
	}
};