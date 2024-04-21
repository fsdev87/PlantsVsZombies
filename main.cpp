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


    // kisi tarha ise bhi chupa
    // main bilkul khali hona chaie
    Texture cherryBomb_s;
    if (!cherryBomb_s.loadFromFile("assets/images/i_cherry.png")) cout << "Failed to load i_cherry.png" << endl;
    Texture chomper_s;
    if (!chomper_s.loadFromFile("assets/images/i_chomper.png")) cout << "Failed to load i_chomper.png" << endl;
    Texture freezer_s;
    if (!freezer_s.loadFromFile("assets/images/i_freeze.png")) cout << "Failed to load i_freezer.png" << endl;
    Texture mine_s;
    if (!mine_s.loadFromFile("assets/images/i_mine.png")) cout << "Failed to load i_mine.png" << endl;
    Texture pea_s;
    if (!pea_s.loadFromFile("assets/images/i_pea.png")) cout << "Failed to load i_pea.png" << endl;
    Texture sunflower_s;
    if (!sunflower_s.loadFromFile("assets/images/i_sunflower.png")) cout << "Failed to load i_sunflower.png" << endl;
    Texture walnut_s;
    if (!walnut_s.loadFromFile("assets/images/i_walnut.png")) cout << "Failed to load i_walnut.png" << endl;
    Texture sun;
    if (!sun.loadFromFile("assets/images/sun.png")) cout << "Failed to load i_sun.png" << endl;

    TextureManager TM;
    TM.addTexture(cherryBomb_s, "cherrybomb");
    TM.addTexture(chomper_s, "chomper");
    TM.addTexture(freezer_s, "freezer");
    TM.addTexture(mine_s, "mine");
    TM.addTexture(sunflower_s, "sunflower");
    TM.addTexture(walnut_s, "walnut");
    TM.addTexture(sun, "sun");


    Inventory Inv;
    Inv.addCard(TM.getTexture("cherrybomb"));
    Inv.addCard(TM.getTexture("walnut"));
    Inv.addCard(TM.getTexture("sunflower"));
    
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