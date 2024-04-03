#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Game
{
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
    std::vector<sf::Texture> reversePolicemanTextures;
    std::vector<sf::Texture> laserTextures;
    sf::Texture backgroundTexture1;
    sf::Texture backgroundTexture2;
    sf::Texture frontgroundTexture1;
    sf::Texture frontgroundTexture2;
    sf::Texture coinTexture;
    sf::Sprite background1;
    sf::Sprite background2;
    sf::Sprite frontground1;
    sf::Sprite frontground2;
    sf::Sprite policeman;
    sf::Sprite reversePoliceman;
    sf::Sprite player;
    std::vector<sf::Sprite> coins; // Vector to store coins
    sf::Sprite laser;
    sf::RectangleShape blueRectangle;
    sf::RectangleShape redRectangle;
    sf::Font font;
    float animationSpeed = 0.1f;
    int policemanCurrentFrame;
    float policemanTimeElapsed;
    int reversePolicemanCurrentFrame;
    float reversePolicemanTimeElapsed;
    float backgroundSpeed;
    float gravity;
    float initialYPosition;
    bool isSpacePressed;
    sf::Clock clock;
    sf::Clock scoreClock;
    int score;
    int Coins;
    int currentRunFrame;
    int currentLaserFrame;
    float laserTimeElapsed = 0.0f;
    bool isJumping;
    float timeElapsed = 0.0f;
    bool pause = false;

    void initialize();
    void loadTextures();
    void setupScene();
    void gameLoop();
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
};
