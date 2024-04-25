#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Animation.h"
using namespace sf;

class Plant : public Animation {
protected:
	float position[2];
	int health;
	int cost;

public:
	virtual void shoot() = 0;
	virtual void repeatShoot() = 0;
	virtual void explode() = 0;
	virtual void makeSun() = 0;
};
