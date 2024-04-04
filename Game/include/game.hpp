#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "background.hpp"
#include "player.hpp"
#include "coin.hpp"
#include "laser.hpp"
#include "menu.hpp"
#include "obstacle.hpp"
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
    Laser laser;
    Obstacle obstacle;
    sf::Font font;
    sf::Text scoreText;
    int score;
    sf::Clock clock;
    bool pause;
    Menu menu;
    bool menuActive = true;
    
    void initialize();
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void loadTextures();
    void setupScene();
};

#endif
