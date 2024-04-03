#include "../include/game.hpp"
#include "../include/background.hpp"
#include "../include/player.hpp"
#include "../include/coin.hpp"
//#include "../include/obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

// Constructor: initialize game window and load resources
Game::Game() : window(sf::VideoMode(800, 600), "Jetpack Joyride", sf::Style::Fullscreen), background(window), player(window), coin(window),  laser(window)
{
    player.initialYPosition = window.getSize().y * 0.69f;
    initialize();
}

// Initialize game components
void Game::initialize() 
{
    loadTextures();
    setupScene();
}

// Load textures from files
void Game::loadTextures()
{
    background.loadTextures();
    player.loadTextures();
    coin.loadTextures();
    laser.loadTextures();
}

// Setup initial scene elements
void Game::setupScene() {
    background.setupScene();
    player.setupScene();
    coin.setupScene();
    laser.setupScene();
}


// Process all events
void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            player.isSpacePressed = true;
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            player.isSpacePressed = false;
    }
}

// Update game state
void Game::update(sf::Time deltaTime) {
    background.update(deltaTime);
    player.update(deltaTime);
    coin.update(deltaTime);
    laser.update(deltaTime);
}

// Render all game objects
void Game::render() {
    window.clear();

    // Render background
    background.drawBackground();

    // Render player
    player.drawPlayer();

    // Render coin
    coin.drawCoin();

    // Render laser
    laser.drawLaser();

    player.drawScore();
    coin.drawCoinScore();

    // Render frontground
    background.drawFrontground();

    window.display();
}

// Main game loop
int Game::run() {
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
    return 0;
}
