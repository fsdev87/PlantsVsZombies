#pragma once

#include "PlantFactory.h"
#include "SoundManager.h"
#include "ZombieFactory.h"

#include "FontManager.h"
#include "TextureManager.h"
#include "Background.h"
#include "Inventory.h"
#include "Life.h"
#include "Level.h"
#include "Garden.h"



class Game {
	TextureManager TM;
	SoundManager SM;
	FontManager FM;
	Level level;
	Background background;
	Inventory Inv;

	int sunCount = 10000;
	Text sunCountText;

	RectangleShape garden[5][9];

	PlantFactory PF;
	ZombieFactory ZF;

	LawnMower* lawnmowers[5]{ nullptr };
	float lawnMowerPos[2] = { -1, 0 };

	Life lives;

	int round;
private:
	void loadTextures() {
		cout << "Loading Textures\n";
		TM.addTexture("assets/Screens/ChooserBackground.png", "inventory"); // Inventory Background

		TM.addTexture("assets/Background/bgday.jpg", "bgday");
		TM.addTexture("assets/Background/bgnight.jpg", "bgnight");
		TM.addTexture("assets/Background/limitedbg.jpg", "limitedbg");
		TM.addTexture("assets/Background/waterday.jpg", "waterday");
		TM.addTexture("assets/Background/waternight.jpg", "waternight");

		//.All Inventory Cards
		TM.addTexture("assets/Screens/Cards/card_sunflower.png", "card-sunflower");
		TM.addTexture("assets/Screens/Cards/card_peashooter.png", "card-peashooter");
		TM.addTexture("assets/Screens/Cards/card_repeaterpea.png", "card-repeater");
		TM.addTexture("assets/Screens/Cards/card_wallnut.png", "card-wallnut");
		TM.addTexture("assets/Screens/Cards/card_snowpea.png", "card-snowpea");
		TM.addTexture("assets/Screens/Cards/card_cherrybomb.png", "card-cherrybomb");

		TM.addTexture("assets/Screens/Cards/card_sunflower_dim.png", "card-sunflower_dim");
		TM.addTexture("assets/Screens/Cards/card_peashooter_dim.png", "card-peashooter_dim");
		TM.addTexture("assets/Screens/Cards/card_repeater_dim.png", "card-repeater_dim");
		TM.addTexture("assets/Screens/Cards/card_wallnut_dim.png", "card-wallnut_dim");
		TM.addTexture("assets/Screens/Cards/card_snowpea_dim.png", "card-snowpea_dim");
		TM.addTexture("assets/Screens/Cards/card_cherrybomb_dim.png", "card-cherrybomb_dim");
		//.M.addTexture("assets/Spritesheets/shovel.png", "shovel");
		TM.addTexture("assets/Static/sun.png", "icon-sun");
		//.Spritesheets
		TM.addTexture("assets/Spritesheets/peashooter.png", "spritesheet-peashooter");
		TM.addTexture("assets/Spritesheets/wallnut.png", "spritesheet-wallnut");
		TM.addTexture("assets/Spritesheets/v.png", "spritesheet-cherrybomb");
		TM.addTexture("assets/Spritesheets/repeater.png", "spritesheet-repeater");
		TM.addTexture("assets/Spritesheets/snowpea.png", "spritesheet-snowpea");
		TM.addTexture("assets/Spritesheets/sunflower.png", "spritesheet-sunflower");
		TM.addTexture("assets/Spritesheets/threepeater.png", "spritesheet-threepeater");
		TM.addTexture("assets/Spritesheets/lawnmower.png", "spritesheet-lawnmower");
		TM.addTexture("assets/Spritesheets/lawnmowerIdle.png", "image-lawnmowerIdle");
		// All are for normal zombie
		TM.addTexture("assets/Spritesheets/nZombEat.png", "spritesheet-nZombEat");
		TM.addTexture("assets/Spritesheets/nZombWalk.png", "spritesheet-nZombWalk");
		TM.addTexture("assets/Spritesheets/headlesswalk.png", "spritesheet-headLessWalk");
		TM.addTexture("assets/Spritesheets/headlesseat.png", "spritesheet-headLessEat");
		TM.addTexture("assets/Spritesheets/normalzombiedie.png", "spritesheet-headLessDeath");
		TM.addTexture("assets/Spritesheets/head.png", "spritesheet-head");
		TM.addTexture("assets/Spritesheets/zombdie.png", "spritesheet-zombieDeath");

		TM.addTexture("assets/Spritesheets/bucHeadZombEat.png", "spritesheet-bucZEat");
		TM.addTexture("assets/Spritesheets/bucHeadZombWalk.png", "spritesheet-bucZWalk");

		TM.addTexture("assets/Spritesheets/wallnutrolling.png", "spritesheet-wallnut-rolling");
		// For all explosion
		TM.addTexture("assets/Spritesheets/zombash.png", "spritesheet-zombieAshes");

		// Bullets
		TM.addTexture("assets/Bullets/peabullet.png", "bullet");
		TM.addTexture("assets/Bullets/peabulletexplode.png", "bulletExplode");
		TM.addTexture("assets/Bullets/peaice.png", "bulletIce");

		// football left textures
		TM.addTexture("assets/Spritesheets/football-walk.png", "football-walk");
		TM.addTexture("assets/Spritesheets/football-walk-2.png", "football-walk-2");
		TM.addTexture("assets/Spritesheets/football-walk-3.png", "football-walk-3");
		TM.addTexture("assets/Spritesheets/football-eat.png", "football-eat");
		TM.addTexture("assets/Spritesheets/football-eat-2.png", "football-eat-2");
		TM.addTexture("assets/Spritesheets/football-eat-3.png", "football-eat-3");
		TM.addTexture("assets/Spritesheets/football-die.png", "football-die");

		// football right textures
		TM.addTexture("assets/Spritesheets/football-walk-right.png", "football-walk-right");
		TM.addTexture("assets/Spritesheets/football-walk-right-2.png", "football-walk-right-2");
		TM.addTexture("assets/Spritesheets/football-walk-right-3.png", "football-walk-right-3");
		TM.addTexture("assets/Spritesheets/football-eat-right.png", "football-eat-right");
		TM.addTexture("assets/Spritesheets/football-eat-right-2.png", "football-eat-right-2");
		TM.addTexture("assets/Spritesheets/football-eat-right-3.png", "football-eat-right-3");

		// dancing textures
		TM.addTexture("assets/Spritesheets/dancingwalk1.png", "dancing-walk-1");
		TM.addTexture("assets/Spritesheets/dancingeat1.png", "dancing-eat-1");
		TM.addTexture("assets/Spritesheets/dancinghead.png", "dancing-head");
		TM.addTexture("assets/Spritesheets/dancingdie.png", "dancing-die");
		TM.addTexture("assets/Spritesheets/dancingwalk2.png", "dancing-walk-2");
		TM.addTexture("assets/Spritesheets/dancingeat2.png", "dancing-eat-2");

		TM.addTexture("assets/Spritesheets/shovel.png", "shovel");


	}

	void loadSounds() {
		SM.loadSound("assets/sounds/menu/mainmusic.mp3", "mainmusic");
		SM.loadSound("assets/sounds/plant/cherrybomb.ogg", "cherrybomb-explosion");
		SM.loadSound("assets/sounds/zombie/zombiefall.ogg", "zombie-fall");
		SM.loadSound("assets/sounds/menu/sunclick.mp3", "sunclick");
		SM.loadSound("assets/sounds/menu/misclick.mp3", "misclick");
		SM.loadSound("assets/sounds/zombie/lowgroan.ogg", "groan1");
		SM.loadSound("assets/sounds/zombie/lowgroan2.ogg", "groan2");
		SM.loadSound("assets/sounds/zombie/eating.mp3", "eating");
		SM.loadSound("assets/sounds/menu/round1.mp3", "round1");
		SM.loadSound("assets/sounds/zombie/mczombie.mp3", "mczombie");
		SM.loadSound("assets/sounds/menu/place1.mp3", "place1");
		SM.loadSound("assets/sounds/menu/place2.mp3", "place2");
		SM.loadSound("assets/sounds/zombie/zombieattack.mp3", "zombieattack");
		SM.loadSound("assets/sounds/zombie/zombieroar.mp3", "zombieroar");
		SM.loadSound("assets/sounds/zombie/hit.mp3", "hit");
		SM.getSound("hit").setVolume(70);
		SM.getSound("round1").setVolume(10.0f);
		SM.getSound("round1").setPlayingOffset(sf::Time(sf::seconds(1.05)));
	}

	void loadInventory() {
		Inv.addCard(TM["card-sunflower_dim"], TM["card-sunflower"], "sunflower", 50);
		Inv.addCard(TM["card-peashooter_dim"], TM["card-peashooter"], "peashooter", 100);
		Inv.addCard(TM["card-repeater_dim"], TM["card-repeater"], "repeater", 200);
		Inv.addCard(TM["card-wallnut_dim"], TM["card-wallnut"], "wallnut", 50);
		Inv.addCard(TM["card-snowpea_dim"], TM["card-snowpea"], "snowpea", 175);
		Inv.addCard(TM["card-cherrybomb_dim"], TM["card-cherrybomb"], "cherrybomb", 150);
		Inv.addCard(TM["shovel"], TM["shovel"], "shovel", 0);
	}

public:
	Game() :level(&FM, &SM), background(&TM), Inv(&TM, &SM), PF(&SM, &TM), ZF(&TM, &SM) {
		this->round = 1;

		loadTextures();
		loadSounds();
		loadInventory();

		sunCountText.setFont(FM[0]);
		sunCountText.setString(to_string(sunCount));
		sunCountText.setCharacterSize(24);
		sunCountText.setPosition(86, 62);
		sunCountText.setFillColor(Color::Black);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				garden[i][j].setSize(Vector2f(80, 96));
				garden[i][j].setFillColor(((i + j) % 2) == 0 ? Color(255, 255, 255, 50) : Color(255, 255, 255, 100));
				garden[i][j].setPosition(gardenCords.leftX + j * 80, gardenCords.topY + i * 96);
			}
		}

		for (int i = 0; i < 5; i++) {
			lawnMowerPos[1] = i;
			lawnmowers[i] = new LawnMower(&TM, lawnMowerPos);
		}
	}

	void
};