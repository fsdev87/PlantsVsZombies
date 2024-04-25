#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#include "FontManager.h"
#include "TextureManager.h"
#include "Background.h"
#include "Inventory.h"

struct {
	const int leftX = 255;
	const int rightX = 975;
	const int topY = 80;
	const int bottomY = 560;

	bool valid(int x, int y) const {
		if (x >= leftX && x <= rightX && y >= topY && y <= bottomY) {
			return true;
		}
		return false;
	}
} gardenCords;


int main()
{
	RenderWindow window(VideoMode(1400, 600), "game");
	Background background;

	TextureManager TM;
	Inventory Inv;

	RectangleShape garden[5][9];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			garden[i][j].setSize(Vector2f(80, 96));
			garden[i][j].setFillColor(((i + j) % 2) == 0 ? Color(255, 255, 255, 50) : Color(255, 255, 255, 100));
			garden[i][j].setPosition(gardenCords.leftX + j * 80, gardenCords.topY + i * 96);
		}
	}

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
						cout << mouseX << " " << mouseY << endl;
						cout << "Position on Grid: " << (mouseY - gardenCords.topY) / 96 << ", " << (mouseX - gardenCords.leftX) / 80 << endl;
					}
				}
			}
		}
		/*Vector2i localPosition = sf::Mouse::getPosition(window);
		cout << "Mouse X: " << localPosition.x << " Mouse Y: " << localPosition.y << endl;*/

		window.clear(Color::Red);

		window.draw(background.getSprite());
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				window.draw(garden[i][j]);
			}
		}
		//Inv.drawInventory(window);
		window.display();
	}

	return 0;
}

// Top Left of Garden : 255, 80
// Bottom Right of Garden : 975, 560