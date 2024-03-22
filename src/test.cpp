#include <SFML/Graphics.hpp>

// make a game with a sprite of robber inside human.hpp
#include "human.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    Human human;
    human.load("robber.png");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(human);
        window.display();
    }

    return 0;
}