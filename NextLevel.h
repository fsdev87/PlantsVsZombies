#pragma once
#include "TextureManager.h"

class NextLevel {
private:
	Font textFont;
	Texture texture;
	Text texts[4];
	Sprite plantSprites[4];
	Sprite zombieSprites[3];

	Sprite backGroundSprite;


public:
	NextLevel(TextureManager* TMptr) {
		this->textFont.loadFromFile("assets/fonts/roman.otf");
		this->texts[0] = Text("LEVEL CLEARED", this->textFont, 180); this->texts[0].setFillColor(Color::White);

		this->texts[1] = Text("UNLOCKED: ", this->textFont, 85); this->texts[1].setFillColor(Color::Green);
		this->texts[2] = Text("BEWARE OF: ", this->textFont, 85); this->texts[2].setFillColor(Color::Red);

		this->plantSprites[0] = Sprite(TMptr->getTexture("spritesheet-wallnut"));
		this->plantSprites[0].setTextureRect(IntRect(0, 0, 71, 71));
		this->plantSprites[1] = Sprite(TMptr->getTexture("spritesheet-repeater"));
		this->plantSprites[1].setTextureRect(IntRect(0, 0, 71, 71));
		this->plantSprites[2] = Sprite(TMptr->getTexture("spritesheet-snowpea"));
		this->plantSprites[2].setTextureRect(IntRect(0, 0, 71, 71));
		this->plantSprites[3] = Sprite(TMptr->getTexture("spritesheet-cherrybomb"));
		this->plantSprites[3].setTextureRect(IntRect(426, 0, 71, 71));

		this->zombieSprites[0] = Sprite(TMptr->getTexture("football-walk"));
		this->zombieSprites[0].setTextureRect(IntRect(0, 0, 166, 144));
		this->zombieSprites[1] = Sprite(TMptr->getTexture("dancing-walk-1"));
		this->zombieSprites[1].setTextureRect(IntRect(0, 0, 166, 144));
		this->zombieSprites[2] = Sprite(TMptr->getTexture("flying-zombie"));
		this->zombieSprites[2].setTextureRect(IntRect(0, 0, 88, 140));

		this->backGroundSprite = Sprite(TMptr->getTexture("levelbg"));
		this->backGroundSprite.setPosition(0, 0);
		this->backGroundSprite.setColor(Color(255, 255, 255, 180));

		this->texts[0].setPosition(190, 20);

		this->texts[1].setPosition(385, 228);
		this->plantSprites[0].setPosition(800, 235);
		this->plantSprites[1].setPosition(900, 235);
		this->plantSprites[2].setPosition(800, 235);
		this->plantSprites[3].setPosition(900, 235);

		this->texts[2].setPosition(375, 340);
		this->zombieSprites[0].setPosition(770, 320);
		this->zombieSprites[1].setPosition(780, 300);
		this->zombieSprites[2].setPosition(800, 305);

	}

	void level2(RenderWindow& window) {
		window.draw(this->backGroundSprite);
		window.draw(this->texts[0]);
		window.draw(this->texts[1]); window.draw(this->plantSprites[0]); window.draw(this->plantSprites[1]);
		window.draw(this->texts[2]); window.draw(this->zombieSprites[0]);
		window.draw(this->texts[3]);
	}

	void level3(RenderWindow& window) {
		window.draw(this->backGroundSprite);
		window.draw(this->texts[0]);
		window.draw(this->texts[1]); window.draw(this->plantSprites[2]); window.draw(this->plantSprites[3]);
		window.draw(this->texts[2]); window.draw(this->zombieSprites[1]);
		window.draw(this->texts[3]);
	}

	void level4(RenderWindow& window) {
		window.draw(this->backGroundSprite);
		this->texts[2].setPosition(460, 280);
		this->zombieSprites[2].setPosition(800, 245);

		window.draw(this->texts[0]);

		window.draw(this->texts[2]); window.draw(this->zombieSprites[2]);
	}

	void drawLevel(RenderWindow& window, int levelIndex) {
		if (levelIndex == 1) level2(window);
		else if (levelIndex == 2) level3(window);
		else if (levelIndex == 3) level4(window);
	}

	void reset() {
		this->texts[0].setPosition(650, 150);

		this->texts[1].setPosition(500, 250);
		this->plantSprites[0].setPosition(700, 250);
		this->plantSprites[1].setPosition(900, 250);
		this->plantSprites[2].setPosition(700, 250);
		this->plantSprites[3].setPosition(900, 250);

		this->texts[2].setPosition(500, 350);
		this->zombieSprites[0].setPosition(700, 300);
		this->zombieSprites[1].setPosition(700, 300);
		this->zombieSprites[2].setPosition(700, 300);

	}
};