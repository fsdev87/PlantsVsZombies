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
#include "Plant.h"
#include "Bullet.h"
#include "Peashooter.h"
#include "Zombie.h"
#include "NormalZombie.h"
#include "Sunflower.h"
#include "Wallnut.h"
#include "Cherrybomb.h"
#include "DancingZombie.h"

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


	int sunCount = 300;
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


	const int maxPlantsForLevelOne = 45;
	Plant** plants = new Plant * [maxPlantsForLevelOne] { nullptr };
	int plantsArrayIndex = 0;


	const int maxZombieCount = 20;
	Zombie** zombies = new Zombie * [maxZombieCount];
	int zombiesArrayIndex = 10;
	for (int i = 0; i < zombiesArrayIndex; i++) {
		float pos[2];
		pos[0] = 8 + i % 4, pos[1] = i % 5;
		zombies[i] = new NormalZombie(TM["spritesheet-nZombWalk"], 22, pos, &TM);
	}

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
				else if (event.key.code == Keyboard::L) {
					Inv.showPlantIndex(plants, plantsArrayIndex);
					cout << "Zombie alive or dead: \n";
					for (int i = 0; i < zombiesArrayIndex; i++) {
						cout << i << " = " << zombies[i]->getExist() << endl;
					}
				}
				else if (event.key.code == Keyboard::R) {
					for (int i = 0; i < plantsArrayIndex; i++) {
						int plantRow = 0;
						for (int j = 0; j < zombiesArrayIndex; j++) {
							if (plants[i] != nullptr && zombies[j]->getExist() && (zombies[j]->getPosition()[1] == plants[i]->getPosition()[1]) && (zombies[j]->getPosition()[0] <= 9)) {
								plantRow++;
							}
						}
						cout << i << " = " << plantRow << endl;
					}
				}
				else if (event.key.code == Keyboard::H) {
					for (int i = 0; i < plantsArrayIndex; i++) {
						cout << "Plant: " << i << " : " << plants[i]->getPosition()[0] << " " << plants[i]->getPosition()[1] << endl;
					}
					for (int i = 0; i < zombiesArrayIndex; i++) {
						cout << "Zombie: " << i << " : " << zombies[i]->getPosition()[0] << " " << zombies[i]->getPosition()[1] << endl;
					}
				}
				else if (event.key.code == Keyboard::P) {
					pause = !pause;
				}
				else if (event.key.code == Keyboard::C) {
					system("cls");
				}
				else if (event.key.code == Keyboard::D) {
					plants[0]->setExist(false);
				}

			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {

					int mouseX = event.mouseButton.x;
					int mouseY = event.mouseButton.y;
					cout << "Mouse X: " << mouseX << " Mouse Y: " << mouseY << endl;
					if (gardenCords.valid(mouseX, mouseY)) {
						cout << mouseX << " " << mouseY << endl;
						cout << "Position on Grid: " << (mouseY - gardenCords.topY) / 96 << ", " << (mouseX - gardenCords.leftX) / 80 << endl;


						// Handle placing of plants
						int gy = (mouseY - gardenCords.topY) / 96;
						int gx = (mouseX - gardenCords.leftX) / 80;

						if (Inv.hasSelectedSomething()) {
							Inv.handlePlacing(gx, gy, plants, plantsArrayIndex, sunCount);
						}

						for (int i = 0; i < plantsArrayIndex; i++) {
							if (plants[i]->getExist() && plants[i]->getPosition()[0] == gx && plants[i]->getPosition()[1] == gy) {
								plants[i]->clickSun(sunCount);
								sunCountText.setString(to_string(sunCount));
							}
						}

					}

					// Handle selection of any card in inventory
					if (Inv.validMouseClick(mouseX, mouseY)) {
						cout << "Valid Mouse Click on Inventory\n";
					}


				}
			}
		}

		window.clear();
		// Update everything here
		// check for collisions, animation, shooting, everything
		for (int i = 0; i < plantsArrayIndex && !pause; i++) {
			plants[i]->animate();
			plants[i]->generateSun();

			/*int plantRow = 0;
			for (int j = 0; j < zombiesArrayIndex; j++) {
				if (plants[i] != nullptr && zombies[j]->getExist() && (zombies[j]->getPosition()[1] == plants[i]->getPosition()[1]) && (zombies[j]->getPosition()[0] <= 9)) {
					plantRow++;
				}
			}
			if (plantRow > 0) {
				plants[i]->shoot(zombies, zombiesArrayIndex);
			}*/
			plants[i]->shoot(zombies, zombiesArrayIndex);
			plants[i]->explode();
		}
		for (int i = 0; i < zombiesArrayIndex && !pause; i++) {
			zombies[i]->animate();
			zombies[i]->move(plants, plantsArrayIndex);
		}


		// Draw everything here...
		window.draw(background.getSprite());

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				window.draw(garden[i][j]);
			}
		}

		Inv.drawInventory(window, sunCount);
		level.move_draw(window);

		for (int i = 0; i < plantsArrayIndex; i++) {
			plants[i]->draw(window);
		}
		for (int i = 0; i < zombiesArrayIndex; i++) {
			zombies[i]->draw(window);
		}

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