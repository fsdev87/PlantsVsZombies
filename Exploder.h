#pragma once
#include "Plant.h"

class Exploder : public Plant {
protected:
	Animation anim;

public:
	Exploder() {}
	virtual void explode() {}
};