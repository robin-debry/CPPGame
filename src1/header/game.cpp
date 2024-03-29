#include "game.hpp"
#include <cmath>

// Constructor: initialize game window and load resources
Game::Game() : window(sf::VideoMode(800, 600), "Jetpack Joyride", sf::Style::Fullscreen),
               backgroundSpeed(600.0f), gravity(75.0f), initialYPosition(720.f), isSpacePressed(false), score(0), currentFrame(0) {
    initialize();
}

// Initialize game components
void Game::initialize() {
    loadTextures();
    setupScene();
}

// Load textures from files
void Game::loadTextures() {
    if (!backgroundTexture1.loadFromFile("img/background.jpg") || !backgroundTexture2.loadFromFile("img/background.jpg")) {
        std::cerr << "Failed to load background textures." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 15; ++i) {
        sf::Texture texture;
        std::string filename = "../Images/The Black Thief Slim Version/Animations/Run/run_";
        filename += (i < 10) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename)) {
            std::cerr << "Failed to load player texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        playerTextures.push_back(texture);
    }
}

// Setup initial scene elements
void Game::setupScene() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        exit(EXIT_FAILURE);
    }

    background1.setTexture(backgroundTexture1);
    background2.setTexture(backgroundTexture2);
    player.setTexture(playerTextures[0]);

    float scaleX = static_cast<float>(window.getSize().x) / background1.getTexture()->getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / background1.getTexture()->getSize().y;
    float scaleFactor = std::max(scaleX, scaleY);

    background1.setScale(scaleFactor, scaleFactor);
    background2.setScale(scaleFactor, scaleFactor);
    background1.setPosition(0.f, 0.f);
    background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0.f);

    player.setPosition(200.f, initialYPosition);
    player.setScale(0.14, 0.14);
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

// Process all events
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            isSpacePressed = true;
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            isSpacePressed = false;
    }
}

// Update game state
void Game::update(sf::Time deltaTime) {
    float dtSeconds = deltaTime.asSeconds();
    if (isSpacePressed)
        player.move(0.f, -backgroundSpeed * dtSeconds);
    else
        player.move(0.f, backgroundSpeed * dtSeconds + gravity * dtSeconds);

    // Update background
    background1.move(-backgroundSpeed * dtSeconds, 0.f);
    background2.move(-backgroundSpeed * dtSeconds, 0.f);

    if (background1.getPosition().x + background1.getGlobalBounds().width < 0) {
        background1.setPosition(background2.getPosition().x + background2.getGlobalBounds().width, 0.f);
    }

    if (background2.getPosition().x + background2.getGlobalBounds().width < 0) {
        background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0.f);
    }

    if (player.getPosition().y > initialYPosition) {
        player.setPosition(player.getPosition().x, initialYPosition);
    }

    if (player.getPosition().y < 0) {
        player.setPosition(player.getPosition().x, 0);
    }

    // Update score and player frame
    sf::Time scoreElapsedTime = scoreClock.getElapsedTime();
    if (scoreElapsedTime.asSeconds() >= 1.0f) {
        score += 10;
        scoreClock.restart();
    }

    static float timeElapsed = 0.0f;
    timeElapsed += dtSeconds;
    if (timeElapsed >= 0.1f) {
        currentFrame = (currentFrame + 1) % 15;
        player.setTexture(playerTextures[currentFrame]);
        timeElapsed = 0.0f;
    }
}

// Render all game objects
void Game::render() {
    window.clear();
    window.draw(background1);
    window.draw(background2);
    window.draw(player);

    // Draw score
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    scoreText.setString("Score: " + std::to_string(score));

    window.draw(scoreText);
    window.display();
}
