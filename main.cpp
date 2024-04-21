#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#include "FontManager.h"
#include "TextureManager.h"
#include "Background.h"
#include "Inventory.h"

int main()
{
    RenderWindow window(VideoMode(1400, 600), "game");
    Background background;

    TextureManager TM;
    TM.addTexture("assets/images/i_cherry.png", "cherrybomb");
    TM.addTexture("assets/images/i_chomper.png", "chomper");
    TM.addTexture("assets/images/i_freeze.png", "freezer");
    TM.addTexture("assets/images/i_mine.png", "mine");
    TM.addTexture("assets/images/i_sunflower.png", "sunflower");
    TM.addTexture("assets/images/i_walnut.png", "walnut");
    TM.addTexture("assets/images/sun.png", "sun");
    TM.addTexture("assets/images/i_pea.png", "peashooter");


    Inventory Inv;
    Inv.addCard(TM.getTexture("cherrybomb"));
    Inv.addCard(TM.getTexture("walnut"));
    Inv.addCard(TM.getTexture("sunflower"));
    Inv.addCard(TM.getTexture("mine"));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::E) {
                    window.close();
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
					cout << "Mouse X: " << event.mouseButton.x << " Mouse Y: " << event.mouseButton.y << endl;
				}
			}
        }

        window.clear(Color::Red);

        window.draw(background.getSprite());
        Inv.drawInventory(window);
        window.display();
    }

    return 0;
}