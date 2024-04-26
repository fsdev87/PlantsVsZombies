#include <SFML/Graphics.hpp>
#include <iostream>
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




int main()
{
	RenderWindow window(VideoMode(1400, 600), "game");
	TextureManager TM;
	loadTextures(&TM);
	FontManager FM;

	Level level(&FM);


	Background background(&TM);

	Inventory Inv(&TM);
	Inv.addCard(TM["card-sunflower"], "sunflower");
	Inv.addCard(TM["card-peashooter"], "peashooter");
	Inv.addCard(TM["card-repeater"], "repeater");
	Inv.addCard(TM["card-wallnut"], "wallnut");
	Inv.addCard(TM["card-snowpea"], "snowpea");
	Inv.addCard(TM["card-cherrybomb"], "cherrybomb");
	Inv.addCard(TM["card-chomper"], "chomper");


	RectangleShape garden[5][9];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			garden[i][j].setSize(Vector2f(80, 96));
			garden[i][j].setFillColor(((i + j) % 2) == 0 ? Color(255, 255, 255, 50) : Color(255, 255, 255, 100));
			garden[i][j].setPosition(gardenCords.leftX + j * 80, gardenCords.topY + i * 96);
		}
	}



	Plant** plants = new Plant * [2];
	float pos[2] = { 1, 1 };
	plants[0] = new Peashooter(TM["spritesheet-peashooter"], 13, pos);
	plants[1] = nullptr;





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
				/*else if (event.key.code == Keyboard::R) {
					level.reset();
					level.increaseLevel();
				}*/
			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {

					int mouseX = event.mouseButton.x;
					int mouseY = event.mouseButton.y;
					cout << "Mouse X: " << mouseX << " Mouse Y: " << mouseY << endl;
					if (gardenCords.valid(mouseX, mouseY)) {
						cout << mouseX << " " << mouseY << endl;
						cout << "Position on Grid: " << (mouseY - gardenCords.topY) / 96 << ", " << (mouseX - gardenCords.leftX) / 80 << endl;

						if (Inv.hasSelectedSomething()) {
							int gx = (mouseX - gardenCords.leftX) / 80;
							int gy = (mouseY - gardenCords.topY) / 96;
							Inv.handlePlacing(gx, gy, plants);
						}
					}

					if (Inv.validMouseClick(mouseX, mouseY)) {
						cout << "Valid Mouse Click on Inventory\n";
					}


				}
			}
		}

		window.clear();

		for (int i = 0; i < 2; i++) {
			if (plants[i] != nullptr) {
				plants[i]->shoot();
				plants[i]->animate();
			}
		}

		// Draw everything here...
		window.draw(background.getSprite());
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				window.draw(garden[i][j]);
			}
		}
		Inv.drawInventory(window);
		//level.move_draw(window);

		for (int i = 0; i < 2; i++) {
			if (plants[i]) {
				plants[i]->draw(window);
			}
		}



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