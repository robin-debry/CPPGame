#include "game.hpp"
#include <cmath>

// Constructor: initialize game window and load resources
Game::Game() : window(sf::VideoMode(800, 600), "Jetpack Joyride", sf::Style::Fullscreen),
               backgroundSpeed(600.0f), gravity(75.0f), isSpacePressed(false), score(0), currentFrame(0) {
    initialYPosition = window.getSize().y * 0.68f;
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
    if (!playerJumpTextures.loadFromFile("../Images/The Black Thief Slim Version/Animations/Jump Start/jump_start_009.png")) {
        std::cerr << "Failed to load player jump texture." << std::endl;
        exit(EXIT_FAILURE);
    }

    if(!playerFallTextures.loadFromFile("../Images/The Black Thief Slim Version/Animations/Jump Fall/jump_fall_000.png")){
        std::cerr << "Failed to load player fall texture." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 7; ++i) {
        sf::Texture texture;
        std::string filename = "../Images/Policeman/1/walk/1_police_Walk_";
        filename += (i < 7) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename)) {
            std::cerr << "Failed to load player texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        policemanTextures.push_back(texture);
    }
}

// Setup initial scene elements
void Game::setupScene() {
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        exit(EXIT_FAILURE);
    }

    background1.setTexture(backgroundTexture1);
    background2.setTexture(backgroundTexture2);

    player.setTexture(playerRunTextures[0]);

    player.setTexture(playerTextures[0]);
    policeman.setTexture(policemanTextures[0]);


    float scaleX = static_cast<float>(window.getSize().x) / background1.getTexture()->getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / background1.getTexture()->getSize().y;
    float scaleFactor = std::max(scaleX, scaleY);

    background1.setScale(scaleFactor, scaleFactor);
    background2.setScale(scaleFactor, scaleFactor);
    background1.setPosition(0.f, 0.f);
    background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0.f);

    player.setPosition(200.f, initialYPosition);
    player.setScale(0.14, 0.14);
    policeman.setPosition(800.f, 800.f + blueRectangle.getSize().y - 50); // Align policeman below player
    policeman.setScale(0.12, 0.12);

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
    policemanTimeElapsed += dtSeconds;
    if (policemanTimeElapsed >= animationSpeed) {
        policemanCurrentFrame = (policemanCurrentFrame + 1) % 7; // Assuming there are 7 frames
        policeman.setTexture(policemanTextures[policemanCurrentFrame]);
        policemanTimeElapsed = 0.0f;
    }

    if (isSpacePressed){
        player.move(0.f, -backgroundSpeed * dtSeconds);
        isJumping = true;
        timeElapsed = 0.0f;
    }
    else if (!isSpacePressed && isJumping){
        player.setTexture(playerFallTextures);
        player.move(0.f, backgroundSpeed * dtSeconds + gravity * dtSeconds);
        timeElapsed = 0.0f;
        if (player.getPosition().y >= initialYPosition){
            player.setPosition(player.getPosition().x, initialYPosition);
            isJumping = false;
        }
    }
    else
        player.move(0.f, backgroundSpeed * dtSeconds + gravity * dtSeconds);
        

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

    timeElapsed += dtSeconds;
    if (timeElapsed >= 0.1f) {
        currentFrame = (currentFrame + 1) % 15;
        player.setTexture(playerRunTextures[currentFrame]);
        timeElapsed = 0.0f;
    }
}

// Render all game objects
void Game::render() {
    window.clear();
    window.draw(background1);
    window.draw(background2);
    window.draw(player);
    window.draw(policeman);
    window.draw(frontground1);
    window.draw(frontground2);

    // Draw score
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    scoreText.setString(std::to_string(score) + "m");

    window.draw(scoreText);
    window.display();
}
