#pragma once
#include "Plant.h"
#include "Zombie.h"

class Shooter : public Plant {
protected:
	bool shooting;
	Animation anim;
	Clock bulletDelayClock;
	//Clock startClock;

public:
	Shooter() {}
	virtual void shoot(Zombie** zomb, int zombiesArrayIndex) {}
};