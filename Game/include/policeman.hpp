#ifndef POLICEMAN_HPP
#define POLICEMAN_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

namespace sf {
    class RenderWindow;
}

class Policeman {
public:

    Policeman(sf::RenderWindow& window);
    void update(sf::Time deltaTime);
    void drawPoliceman();
    void loadTextures();
    void setupScene();
    void drawScore();

    float initialYPosition;
    sf::Clock clock;
    sf::RenderWindow& window;
    std::vector<sf::Texture> policemanTextures;
    std::vector<sf::Texture> reversePolicemanTextures;
    std::vector<sf::Texture> runPolicemanTextures;   
    sf::Sprite policeman;
    sf::Sprite reversePoliceman;
    sf::Sprite runPoliceman;
    int policemanCurrentFrame;
    float policemanTimeElapsed;
    int reversePolicemanCurrentFrame;
    float reversePolicemanTimeElapsed;
    int runPolicemanCurrentFrame;
    float runPolicemanTimeElapsed;
    int currentRunFrame;
    float animationSpeed = 0.1f;
    float gravity;
    bool isJumping;
    float timeElapsed;
    float playerSpeed;
    int score;

};    

#endif