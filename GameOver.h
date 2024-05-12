#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class GameOver {
private:
	Sprite sprite;
	Texture texture;
	Clock clock;

public:
	GameOver() {
		this->texture.loadFromFile("assets/Screens/gameover.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setPosition(0, 0);
	}

	void draw(RenderWindow& window) {
		window.draw(this->sprite);
	}

	void restartClock() { this->clock.restart(); }

	Clock& getClock() { return this->clock; }
};