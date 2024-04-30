#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace sf;

#include "FontManager.h"
#include "TextureManager.h"
#include "Background.h"
#include "Inventory.h"
#include "Level.h"
#include "Garden.h"
#include "Animation.h"
#include "Bullet.h"
#include "Peashooter.h"
#include "NormalZombie.h"
#include "Sunflower.h"
#include "Wallnut.h"
#include "Cherrybomb.h"
#include "DancingZombie.h"

#include "PlantFactory.h"
#include "ZombieFactory.h"


void loadTextures(TextureManager* TM) {
	cout << "Loading Textures\n";
	TM->addTexture("assets/Screens/ChooserBackground.png", "inventory"); // Inventory Background

	TM->addTexture("assets/Background/bgday.jpg", "bgday");
	TM->addTexture("assets/Background/bgnight.jpg", "bgnight");
	TM->addTexture("assets/Background/limitedbg.jpg", "limitedbg");
	TM->addTexture("assets/Background/waterday.jpg", "waterday");
	TM->addTexture("assets/Background/waternight.jpg", "waternight");

	//->All Inventory Cards
	TM->addTexture("assets/Screens/Cards/card_sunflower.png", "card-sunflower");
	TM->addTexture("assets/Screens/Cards/card_peashooter.png", "card-peashooter");
	TM->addTexture("assets/Screens/Cards/card_repeaterpea.png", "card-repeater");
	TM->addTexture("assets/Screens/Cards/card_wallnut.png", "card-wallnut");
	TM->addTexture("assets/Screens/Cards/card_snowpea.png", "card-snowpea");
	TM->addTexture("assets/Screens/Cards/card_cherrybomb.png", "card-cherrybomb");

	TM->addTexture("assets/Screens/Cards/card_sunflower_dim.png", "card-sunflower_dim");
	TM->addTexture("assets/Screens/Cards/card_peashooter_dim.png", "card-peashooter_dim");
	TM->addTexture("assets/Screens/Cards/card_repeater_dim.png", "card-repeater_dim");
	TM->addTexture("assets/Screens/Cards/card_wallnut_dim.png", "card-wallnut_dim");
	TM->addTexture("assets/Screens/Cards/card_snowpea_dim.png", "card-snowpea_dim");
	TM->addTexture("assets/Screens/Cards/card_cherrybomb_dim.png", "card-cherrybomb_dim");
	TM->addTexture("assets/Screens/Cards/card_chomper.png", "card-chomper");
	//->M.addTexture("assets/Spritesheets/shovel.png", "shovel");
	//->Spritesheets
	TM->addTexture("assets/Spritesheets/peashooter.png", "spritesheet-peashooter");
	TM->addTexture("assets/Spritesheets/wallnut.png", "spritesheet-wallnut");
	TM->addTexture("assets/Spritesheets/cherrybomb.png", "spritesheet-cherrybomb");
	TM->addTexture("assets/Spritesheets/v.png", "spritesheet-2cherrybomb");
	TM->addTexture("assets/Spritesheets/repeater.png", "spritesheet-repeater");
	TM->addTexture("assets/Spritesheets/snowpea.png", "spritesheet-snowpea");
	TM->addTexture("assets/Spritesheets/sunflower.png", "spritesheet-sunflower");
	TM->addTexture("assets/Static/sun.png", "icon-sun");
	TM->addTexture("assets/Spritesheets/nZombEat.png", "spritesheet-nZombEat");
	TM->addTexture("assets/Spritesheets/nZombWalk.png", "spritesheet-nZombWalk");
	TM->addTexture("assets/Spritesheets/nZombWalkDim.png", "spritesheet-nZombWalkDim");
	TM->addTexture("assets/Spritesheets/nZombEatDim.png", "spritesheet-nZombEatDim");
	TM->addTexture("assets/Spritesheets/bucHeadZombEat.png", "spritesheet-bucZEat");
	TM->addTexture("assets/Spritesheets/bucHeadZombWalk.png", "spritesheet-bucZWalk");
	TM->addTexture("assets/Spritesheets/zombdie.png", "spritesheet-zombieDeath");

	TM->addTexture("assets/Bullets/peabullet.png", "bullet");
	TM->addTexture("assets/Bullets/peabulletexplode.png", "bulletExplode");
	TM->addTexture("assets/Bullets/peaice.png", "bulletIce");

}



int main()
{
	srand((unsigned)time(0));

	RenderWindow window(VideoMode(1400, 600), "game");
	TextureManager TM;

	loadTextures(&TM);

	FontManager FM;
	Level level(&FM);

	Background background(&TM);

	Inventory Inv(&TM);
	Inv.addCard(TM["card-sunflower_dim"], TM["card-sunflower"], "sunflower", 50);
	Inv.addCard(TM["card-peashooter_dim"], TM["card-peashooter"], "peashooter", 100);
	Inv.addCard(TM["card-repeater_dim"], TM["card-repeater"], "repeater", 200);
	Inv.addCard(TM["card-wallnut_dim"], TM["card-wallnut"], "wallnut", 50);
	Inv.addCard(TM["card-snowpea_dim"], TM["card-snowpea"], "snowpea", 175);
	Inv.addCard(TM["card-cherrybomb_dim"], TM["card-cherrybomb"], "cherrybomb", 150);
	//Inv.addCard(TM["card-chomper"], "chomper");


	int sunCount = 500;
	Text sunCountText;
	sunCountText.setFont(FM[0]);
	sunCountText.setString(to_string(sunCount));
	sunCountText.setCharacterSize(24);
	sunCountText.setPosition(86, 62);
	sunCountText.setFillColor(Color::Black);


	RectangleShape garden[5][9];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			garden[i][j].setSize(Vector2f(80, 96));
			garden[i][j].setFillColor(((i + j) % 2) == 0 ? Color(255, 255, 255, 50) : Color(255, 255, 255, 100));
			garden[i][j].setPosition(gardenCords.leftX + j * 80, gardenCords.topY + i * 96);
		}
	}
	PlantFactory PF;
	cout << "plant factory created\n";
	ZombieFactory ZF(&TM);
	cout << "zombie factory created\n";


	bool pause = false;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape) {
					window.close();
				}
			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {

					int mouseX = event.mouseButton.x;
					int mouseY = event.mouseButton.y;
					cout << "Mouse X: " << mouseX << " Mouse Y: " << mouseY << endl;
					if (gardenCords.valid(mouseX, mouseY)) {
						cout << "Position on Grid: " << (mouseY - gardenCords.topY) / 96 << ", " << (mouseX - gardenCords.leftX) / 80 << endl;


						// Handle placing of plants
						int gy = (mouseY - gardenCords.topY) / 96;
						int gx = (mouseX - gardenCords.leftX) / 80;

						PF.handlePlacing(&Inv, gx, gy, sunCount);

						PF.handleSunClick(gx, gy, sunCountText, sunCount);

					}

					// no need to call in if statement
					Inv.validMouseClick(mouseX, mouseY, sunCount);



				}
			}
		}

		window.clear();
		// Update everything here
		// check for collisions, animation, shooting, everything
		PF.updateEverything(ZF.getZombies(), ZF.getZombiesArrayIndex());

		ZF.updateEverything(PF.getPlants(), PF.getPlantsArrayIndex());

		// spawning of zombies


		// Draw everything here...
		window.draw(background.getSprite());

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				window.draw(garden[i][j]);
			}
		}

		Inv.drawInventory(window, sunCount);
		level.move_draw(window);

		PF.draw(window);
		ZF.draw(window);

		window.draw(sunCountText);
		window.display();
	}
	return 0;
}

// Top Left of Garden : 255, 80
// Bottom Right of Garden : 975, 560


/*
	if image size is 80x80
	 then xfactor = 255 and yfactor = ~100
	if image size is 166x144
	then xfactor = 185 and yfactor = 32
*/