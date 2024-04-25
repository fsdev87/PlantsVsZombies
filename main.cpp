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


int main()
{
	RenderWindow window(VideoMode(1400, 600), "game");

	Background background;
	FontManager FM;
	TextureManager TM;
	TM.addTexture("assets/Inventory-GameScreen/ChooserBackground.png", "inventory");
	TM.addTexture("assets/Inventory-GameScreen/Cards/card_sunflower.png", "card_sunflower");
	TM.addTexture("assets/Inventory-GameScreen/Cards/card_peashooter.png", "card_peashooter");
	TM.addTexture("assets/Inventory-GameScreen/Cards/card_repeaterpea.png", "card_repeater");
	TM.addTexture("assets/Inventory-GameScreen/Cards/card_wallnut.png", "card_wallnut");
	TM.addTexture("assets/Inventory-GameScreen/Cards/card_snowpea.png", "card_snowpea");
	TM.addTexture("assets/Inventory-GameScreen/Cards/card_cherrybomb.png", "card_cherrybomb");
	TM.addTexture("assets/Inventory-GameScreen/Cards/card_chomper.png", "card_chomper");

	Inventory Inv(TM["inventory"]);
	Inv.addCard(TM["card_sunflower"]);
	Inv.addCard(TM["card_peashooter"]);
	Inv.addCard(TM["card_repeater"]);
	Inv.addCard(TM["card_wallnut"]);
	Inv.addCard(TM["card_snowpea"]);
	Inv.addCard(TM["card_cherrybomb"]);
	Inv.addCard(TM["card_chomper"]);
	Inv.addCard(TM["card_sunflower"]);
	Inv.addCard(TM["card_peashooter"]);


	RectangleShape garden[5][9];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			garden[i][j].setSize(Vector2f(80, 96));
			garden[i][j].setFillColor(((i + j) % 2) == 0 ? Color(255, 255, 255, 50) : Color(255, 255, 255, 100));
			garden[i][j].setPosition(gardenCords.leftX + j * 80, gardenCords.topY + i * 96);
		}
	}


	Level level;

	Peashooter pea("assets/Spritesheets/peashooter71px.png", 71, 71, 13, 1, 2, 100, 100);
	pea.setFactor(255, 90);
	Animation zomb("assets/Spritesheets/bucHeadZombWalk.png", 166, 144, 15, 8, 4);
	Animation zomb2("assets/Spritesheets/nZombWalk.png", 166, 144, 22, 0, 4);
	Bullet bullet(0, 3);

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
				else if (event.key.code == Keyboard::R) {
					level.reset();
					level.increaseLevel();
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
					}
				}
			}
		}

		window.clear(Color::Red);

		// Do all updating and animation here...
		pea.animate();
		pea.shoot();

		zomb.animate();
		zomb2.animate();

		// Draw everything here...
		window.draw(background.getSprite());
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				window.draw(garden[i][j]);
			}
		}
		Inv.drawInventory(window);
		level.move_draw(window);



		bullet.move();
		bullet.draw(window);



		zomb.draw(window);
		zomb2.draw(window);

		pea.draw(window);


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