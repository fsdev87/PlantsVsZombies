#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Animation {
	int columns;
	int boxSize;
	int frame;
	Texture tex;
	Sprite sprite;
	Clock animClock;
	int xCord, yCord;

public:
	Animation(string source, int boxsize, int col, int x, int y) : xCord(x), yCord(y), boxSize(boxsize), columns(col), frame(0) {
		if (!tex.loadFromFile(source)) {
			cout << "Error loading texture" << endl;
		}
		sprite.setTexture(tex);
		sprite.setTextureRect(IntRect(0, 0, boxSize, boxSize));
		sprite.setPosition(255 + yCord * 80, 80 + xCord * 96);
		animClock.restart();
	}

	void animate() {
		float time = animClock.getElapsedTime().asSeconds();
		if (time > 0.05) {
			sprite.setTextureRect(IntRect(frame * boxSize, 0, boxSize, boxSize));
			frame += 1;
			animClock.restart();
		}
		if (frame >= columns) frame = 0;
	}

	void draw(RenderWindow& window) const {
		window.draw(sprite);
	}
};
