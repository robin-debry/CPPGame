#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

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
    sf::Texture obstacleHorizontalTexture;
    sf::Texture obstacleVerticalTexture;
    
    sf::Font font;
    sf::Clock clock;

    std::vector<sf::Sprite> obstaclesHorizontal;
    std::vector<sf::Sprite> obstaclesVertical;
    
    sf::Sprite obstacleSpriteHorizontal;
    sf::Sprite obstacleSpriteVertical;

    float obstacleSpeed;
    bool gameOverActive = false;
    

    

};

#endif