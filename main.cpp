#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
// cout << "hellow";
int main()
{
    // Mus Branch
    // change
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    RectangleShape shape({ 100.0f,100.0f });
    shape.setFillColor(Color::Blue);
    // abd -> main
    // abd -> pull main with you
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
