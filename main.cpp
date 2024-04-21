#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
    // Mus Branch with blue color circle
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Blue);
    // just checking to see if git status works
    // git branch --set-upstream-to origin/main

    // this is abd branch shouldn't be in main

    // added to abd branch main.cpp from github.com

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
