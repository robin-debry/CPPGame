#ifndef COIN_HPP
#define COIN_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "player.hpp"

namespace sf {
    class RenderWindow;
}

class Coin {
public:

    Player player;

    Coin(sf::RenderWindow& window);
    void update(sf::Time deltaTime, Player& player);
    void drawCoin();
    void loadTextures();
    void setupScene();
    void drawCoinScore();

private:

    sf::RenderWindow& window;
    sf::Texture coinTexture;
    
    sf::Font font;
    sf::Clock clock;

    std::vector<sf::Sprite> coins;
    int Coins;

    
    float coinSpeed;

};

#endif