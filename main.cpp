#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
<<<<<<< HEAD

=======
>>>>>>> cd60cfd5cf58bf24daf7b5b5c57c0af5f8c6809e
    // Mus Branch with blue color circle
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Blue);
<<<<<<< HEAD

=======
>>>>>>> cd60cfd5cf58bf24daf7b5b5c57c0af5f8c6809e

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