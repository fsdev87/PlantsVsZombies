#pragma once
#include "Plant.h"
#include "Zombie.h"

class Shooter : public Plant {
protected:
	Clock bulletDelayClock;
	Clock startClock;

public:
	Shooter() {}
	virtual void shoot(Zombie** zombies, int zombiesArrayIndex) {}
};