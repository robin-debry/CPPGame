#include "../include/game.hpp"
#include "../include/background.hpp"
#include "../include/player.hpp"
#include "../include/coin.hpp"
#include "../include/obstacle.hpp"
#include "../include/menu.hpp"

#include "../include/policeman.hpp"
//#include "../include/obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Jetpack Joyride", sf::Style::Fullscreen), background(window), player(window), coin(window),  laser(window), pause(false), obstacle(window), menu(window),menuActive(true),policeman(window)


{
    if (!music.openFromFile("assets/music/music.mp3"))
    {
        std::cerr << "Failed to load music file" << std::endl;
        exit(EXIT_FAILURE);
    }
    music.setLoop(true);
    music.play();
    player.initialYPosition = window.getSize().y * 0.69f;
    policeman.initialYPosition = window.getSize().y * 0.69f;
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
    policeman.loadTextures();
    coin.loadTextures();
    laser.loadTextures();
    obstacle.loadTextures();
}

// Setup initial scene elements
void Game::setupScene() {
    background.setupScene();
    player.setupScene();
    policeman.setupScene();
    coin.setupScene();
    laser.setupScene();
    obstacle.setupScene();
}


// Process all events
void Game::processEvents() {
    if (!menuActive) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                player.isSpacePressed = true;
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
                player.isSpacePressed = false;
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            pause = !pause;
            std::cout << "Pause state: " << (pause ? "Paused" : "Not paused") << std::endl;
}

        }
    } else {
        int selection = menu.handleInput(window);
        if (selection == 0) {
            menuActive = false;
        } else if (selection == 1) {
            window.close();
        }
    }
}

// Update game state
void Game::update(sf::Time deltaTime) {
    if (pause) {
        return;
    }
    background.update(deltaTime);
    player.update(deltaTime);
    policeman.update(deltaTime);
    coin.update(deltaTime, player);
    laser.update(deltaTime, player);
    obstacle.update(deltaTime, player);

}

// Render all game objects
void Game::render() {
     window.clear();

    if (menuActive) {
        menu.draw(window);
        window.display();
        pause = true;
        return;
    }
    pause = false;
    // Render background
    background.drawBackground();

    // Render player
    player.drawPlayer();

    // Render coin
    coin.drawCoin();

    // Render obstacle
    obstacle.drawObstacle();

    // Render laser
    laser.drawLaser();

    policeman.drawPoliceman();
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