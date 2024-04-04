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

class Rectangle {
public:
    int x, y, width, height;

    Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    bool contains(int pointX, int pointY) {
        return pointX >= x && pointX <= x + width && pointY >= y && pointY <= y + height;
    }

    int minCollisionDistance(int pointX, int pointY) {
        int dx = std::max({x - pointX, 0, pointX - (x + width)});
        int dy = std::max({y - pointY, 0, pointY - (y + height)});
        return std::sqrt(dx * dx + dy * dy);
    }
};

class Obstacle {
public:

    Player player;

    Obstacle(sf::RenderWindow& window);
    void update(sf::Time deltaTime, Player& player);
    void drawObstacle();
    void loadTextures();
    void setupScene();

    int x, y, width, height;

    Rectangle toRectangle() {
        return Rectangle(x, y, width, height);
    }

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

    

};

#endif