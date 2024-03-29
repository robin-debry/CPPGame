#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Game {
public:
    Game();
    int run();

private:
    sf::RenderWindow window;
    std::vector<sf::Texture> playerRunTextures;
    sf::Texture playerJumpTextures;
    sf::Texture playerFallTextures;
    std::vector<sf::Texture> playerTextures;
    std::vector<sf::Texture> policemanTextures;
    sf::Texture backgroundTexture1;
    sf::Texture backgroundTexture2;
    sf::Texture frontgroundTexture1;
    sf::Texture frontgroundTexture2;
    sf::Sprite background1;
    sf::Sprite background2;
    sf::Sprite frontground1;
    sf::Sprite frontground2;
    sf::Sprite policeman;
    sf::Sprite player;
    sf::RectangleShape blueRectangle;
    sf::RectangleShape redRectangle;
    sf::Font font;
    float animationSpeed = 0.1f;
    int policemanCurrentFrame;
    float policemanTimeElapsed;
    float backgroundSpeed;
    float gravity;
    float initialYPosition;
    bool isSpacePressed;
    sf::Clock clock;
    sf::Clock scoreClock;
    int score;
    int currentFrame;
    bool isJumping;
    float timeElapsed = 0.0f;

    void initialize();
    void loadTextures();
    void setupScene();
    void gameLoop();
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
};
