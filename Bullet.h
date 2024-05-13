#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "TextureManager.h"
#include "Animation.h"
#include "Zombie.h"
#include "Scoreboard.h"

using namespace sf;

class Bullet {
protected:
	Texture texture;
	Sprite sprite;
	float position[2];
	int damage;
	Clock bulletClock;
	bool exists;
	float speed;
	Sound hitSound;

public:
	Bullet(int x = 0, int y = 0);

	void setHitSound(Sound sound);

	void saveEverything(ofstream& file);

	void readEverything(ifstream& file);

	void changeSprite(Texture& tex);

	bool getExist();

	void setExist(bool val);

	void setPosition(float x, float y);

	void move(Zombie** zombies, int zombiesArrayIndex, bool isSnow = false, Scoreboard* scoreboard = nullptr);

	void draw(RenderWindow& window);
};
