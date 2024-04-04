#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "player.hpp"

namespace sf {
    class RenderWindow;
}

class Obstacle {
public:

    Player player;

    Obstacle(sf::RenderWindow& window);
    void update(sf::Time deltaTime, Player& player);
    void drawObstacle();
    void loadTextures();
    void setupScene();

private:

    sf::RenderWindow& window;
    sf::Texture obstacleTexture;
    
    sf::Font font;
    sf::Clock clock;

    std::vector<sf::Sprite> obstaclesHorizontal;
    std::vector<sf::Sprite> obstaclesVertical;
    
    float obstacleSpeed;

};

#endif