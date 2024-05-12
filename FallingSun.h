#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
using namespace sf;

class FallingSun {
private:
	Sprite sprite;
	Texture texture;
	Clock sunClock;
	Clock moveClock;
	float sunDelay = 5 + rand() % 3;
	float position[2];
	bool exists;
	float speed = 0.03125;
	float xFactor = 260;
	float yFactor = 90;

public:
	FallingSun() {
		srand(time(0));
		this->texture.loadFromFile("assets/Static/sun.png");
		this->sprite = Sprite(this->texture);
		this->position[0] = rand() % 9; // randomly in the grid
		this->position[1] = 0;
		this->sunClock.restart(), this->moveClock.restart();
		this->exists = false;

		this->yFactor = 20;
	}

	void saveEverything(ofstream& file) {
		file.write(reinterpret_cast<char*>(&position[0]), sizeof(float));
		file.write(reinterpret_cast<char*>(&position[1]), sizeof(float));
		file.write(reinterpret_cast<char*>(&exists), sizeof(bool));
		file.write(reinterpret_cast<char*>(&sunDelay), sizeof(float));
	}
	void readEverything(ifstream& file) {
		file.read(reinterpret_cast<char*>(&position[0]), sizeof(float));
		file.read(reinterpret_cast<char*>(&position[1]), sizeof(float));
		this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);

		file.read(reinterpret_cast<char*>(&exists), sizeof(bool));
		file.read(reinterpret_cast<char*>(&sunDelay), sizeof(float));
	}

	float* getPosition() {
		return this->position;
	}

	void restartGenerateClock() { this->sunClock.restart(); }

	void generate() {
		if (this->exists) {
			this->sunClock.restart();
			return;
		}
		if (this->sunClock.getElapsedTime().asSeconds() > this->sunDelay) {
			this->sunClock.restart();
			this->sunDelay = 5 + rand() % 3;
			this->exists = true;
			this->position[0] = rand() % 9, this->position[1] = 0;
		}
	}

	void moveSun() {
		if (!this->exists) return;
		if (this->moveClock.getElapsedTime().asMilliseconds() < 50) return;
		this->moveClock.restart();

		if (this->position[1] < 5.25) {
			this->position[1] += this->speed;
		}
		else {
			this->exists = false;
		}
		this->sprite.setPosition(this->xFactor + this->position[0] * 80, this->yFactor + this->position[1] * 96);
	}

	void setExist(bool val) { this->exists = val; }
	bool getExist() { return this->exists; }

	void draw(RenderWindow& window) {
		if (this->exists) {
			window.draw(this->sprite);
		}
	}

	void reset() {
		this->position[0] = rand() % 9; // randomly in the grid
		this->position[1] = 0;
		this->sunClock.restart(), this->moveClock.restart();
		this->exists = false;
	}
};