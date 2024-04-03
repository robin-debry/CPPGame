#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "background.hpp"
#include "player.hpp"
#include "coin.hpp"
#include "laser.hpp"
#include <iostream>
#include <vector>

class Game {
public:
    Game();
    int run();

private:
    sf::RenderWindow window;
    Background background;
    Player player;
    Coin coin;
    sf::Font font;
    sf::Text scoreText;
    int score;
    sf::Clock clock;
    
    void initialize();
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void loadTextures();
    void setupScene();
};

#endif
