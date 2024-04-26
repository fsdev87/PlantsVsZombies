#pragma once
#include "Plant.h"

class NonShooter : public Plant {
protected:
	Animation anim;

public:
	NonShooter() {}
	virtual void generateSun() {}
};