#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
<<<<<<< HEAD
    // ABD BRANCH mus changed color to white
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Color(255, 255, 255));
=======
    // Mus Branch with blue color circle
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Blue);
    // just checking to see if git status works
    // git branch --set-upstream-to origin/main

    // this is abd branch shouldn't be in main

    // added to abd branch main.cpp from github.com
>>>>>>> 8fbb453d9a7e64302afdae72fbb6a1049dc048b9

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
