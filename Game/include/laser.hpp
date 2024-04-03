#ifndef LASER_HPP
#define LASER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "player.hpp"

namespace sf {
    class RenderWindow;
}

class Laser {
public:

    Player player;
    Laser(sf::RenderWindow& window);
    void update(sf::Time deltaTime);
    void drawLaser();
    void loadTextures();
    void setupScene();

private:

    sf::RenderWindow& window;

    sf::Clock clock;
    sf::Texture laserTexture;
    sf::Sprite laser;

    float laserSpeed;
    float laserTimeElapsed = 0.0f;
    int currentLaserFrame;


};
#endif
