#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "background.hpp"
#include "player.hpp"
#include "coin.hpp"
#include "laser.hpp"
#include "menu.hpp"
#include "obstacle.hpp"
#include "policeman.hpp"
#include <iostream>
#include <SFML/Audio.hpp>
#include <vector>

class Game {
public:
    Game();
    int run();

private:
    sf::RenderWindow window;
    sf::Music music;
    Background background;
    Player player;
    Policeman policeman;
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
