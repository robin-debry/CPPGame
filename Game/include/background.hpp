#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>

namespace sf {
    class RenderWindow;
}

class Background {
public:

    Background(sf::RenderWindow& window);   
    void loadTextures();
    void drawBackground();
    void drawFrontground();
    void setupScene();
    void update(sf::Time deltaTime);

    sf::Clock clock;

    float backgroundSpeed;

private:

    sf::RenderWindow& window;
    sf::Texture backgroundTexture1;
    sf::Texture backgroundTexture2;
    sf::Texture frontgroundTexture1;
    sf::Texture frontgroundTexture2;
    sf::Sprite background1;
    sf::Sprite background2;
    sf::Sprite frontground1;
    sf::Sprite frontground2;

};

#endif
