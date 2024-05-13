#pragma once

#include "Level.h"
#include "Garden.h"
#include "LawnMower.h"


class BeginnersGarden : public Level {
	RectangleShape garden[5][9];

public:
	BeginnersGarden(Background& background, TextureManager* TM, FontManager* FM, SoundManager* SM, Clock* runClock, Text* sunCountText, int& sunCount, LawnMower** lawnmowers, float* lawnMowerPos, Scoreboard* scoreboard);

	void drawEverything(RenderWindow& window, Background& background, Inventory* Inv, int& sunCount, PlantFactory* PF, ZombieFactory* ZF, LawnMower** lawnmowers, Life& lives, FallingSun* sun, Text& sunCountText);
};
