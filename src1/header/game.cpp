#include "game.hpp"
#include <cmath>

// Constructor: initialize game window and load resources
Game::Game() : window(sf::VideoMode(800, 600), "Jetpack Joyride", sf::Style::Fullscreen),
               backgroundSpeed(600.0f), gravity(75.0f), initialYPosition(720.f), isSpacePressed(false), score(0), currentRunFrame(0) {
    initialize();
}

// Initialize game components
void Game::initialize() {
    loadTextures();
    setupScene();
}

// Load textures from files
void Game::loadTextures() {
    if (!backgroundTexture1.loadFromFile("img/background.jpg") || !backgroundTexture2.loadFromFile("img/background.jpg") || !frontgroundTexture1.loadFromFile("img/frontground.png") || !frontgroundTexture2.loadFromFile("img/frontground.png")){
        std::cerr << "Failed to load background textures." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Scale the textures based on the window's dimensions
    sf::Vector2u windowSizeU = window.getSize();
    sf::Vector2f windowSize(static_cast<float>(windowSizeU.x), static_cast<float>(windowSizeU.y));
    backgroundTexture1.setSmooth(true);
    backgroundTexture2.setSmooth(true);
    frontgroundTexture1.setSmooth(true);
    frontgroundTexture2.setSmooth(true);
    background1.setScale(windowSize.x / backgroundTexture1.getSize().x, windowSize.y / backgroundTexture1.getSize().y);
    background2.setScale(windowSize.x / backgroundTexture2.getSize().x, windowSize.y / backgroundTexture2.getSize().y);
    frontground1.setScale(windowSize.x / frontgroundTexture1.getSize().x, windowSize.y / frontgroundTexture1.getSize().y);
    frontground2.setScale(windowSize.x / frontgroundTexture2.getSize().x, windowSize.y / frontgroundTexture2.getSize().y);

    for (int i = 0; i < 15; ++i) {
        sf::Texture texture;
        std::string filename = "../Images/The Black Thief Slim Version/Animations/Run/run_";
        filename += (i < 10) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename)) {
            std::cerr << "Failed to load player texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        playerRunTextures.push_back(texture);
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
    player.setTexture(playerRunTextures[0]);

    float scaleX = static_cast<float>(window.getSize().x) / background1.getTexture()->getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / background1.getTexture()->getSize().y;
    float scaleFactor = std::max(scaleX, scaleY);
    

    background1.setScale(scaleFactor, scaleFactor);
    background2.setScale(scaleFactor, scaleFactor);
    background1.setPosition(0.f, 0.f);
    background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0.f);

    player.setPosition(200.f, initialYPosition);
    player.setScale(0.14, 0.14);

    frontground1.setTexture(frontgroundTexture1);
    frontground2.setTexture(frontgroundTexture2);
    frontground1.setScale(scaleFactor, scaleFactor);
    frontground2.setScale(scaleFactor, scaleFactor);
    frontground1.setPosition(0.f, 0.f);
    frontground2.setPosition(frontground1.getPosition().x + frontground1.getGlobalBounds().width, 0.f);
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
    if (isSpacePressed){
    timeElapsed += dtSeconds;
    if (timeElapsed >= 0.1f) {
        currentJumpFrame = (currentJumpFrame + 1) % 9;
        player.setTexture(playerJumpTextures[currentJumpFrame]);
        timeElapsed = 0.0f;
    }
        player.move(0.f, -backgroundSpeed * dtSeconds);
    }
    else{
        player.move(0.f, backgroundSpeed * dtSeconds + gravity * dtSeconds);
    }

    // Update background
    background1.move(-backgroundSpeed * dtSeconds, 0.f);
    background2.move(-backgroundSpeed * dtSeconds, 0.f);

    frontground1.move(-backgroundSpeed * dtSeconds, 0.f);
    frontground2.move(-backgroundSpeed * dtSeconds, 0.f);

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

    if (frontground1.getPosition().x + frontground1.getGlobalBounds().width < 0) {
        frontground1.setPosition(frontground2.getPosition().x + frontground2.getGlobalBounds().width, 0.f);
    }

    if (frontground2.getPosition().x + frontground2.getGlobalBounds().width < 0) {
        frontground2.setPosition(frontground1.getPosition().x + frontground1.getGlobalBounds().width, 0.f);
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
        currentRunFrame = (currentRunFrame + 1) % 15;
        player.setTexture(playerRunTextures[currentRunFrame]);
        timeElapsed = 0.0f;
    }
}

// Render all game objects
void Game::render() {
    window.clear();
    window.draw(background1);
    window.draw(background2);
    window.draw(player);
    window.draw(frontground1);
    window.draw(frontground2);

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
