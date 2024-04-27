#pragma once
#include "Plant.h"

class NonShooter : public Plant {
public:
	NonShooter() {}
	virtual void generateSun() {}
};