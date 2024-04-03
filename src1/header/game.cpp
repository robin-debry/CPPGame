#include "game.hpp"
#include <cmath>

// Constructor: initialize game window and load resources
Game::Game() : window(sf::VideoMode(800, 600), "Jetpack Joyride", sf::Style::Fullscreen),
               backgroundSpeed(600.0f), gravity(75.0f), isSpacePressed(false), score(0), Coins(0), currentRunFrame(0), currentLaserFrame(0), pause(false)
{
    initialYPosition = window.getSize().y * 0.68f;
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
    if (!backgroundTexture1.loadFromFile("img/background.jpg") || !backgroundTexture2.loadFromFile("img/background.jpg") || !frontgroundTexture1.loadFromFile("img/frontground.png") || !frontgroundTexture2.loadFromFile("img/frontground.png"))
    {
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

    for (int i = 0; i < 15; ++i)
    {
        sf::Texture texture;
        std::string filename = "../Images/The Black Thief Slim Version/Animations/Run/run_";
        filename += (i < 10) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename))
        {
            std::cerr << "Failed to load player texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        playerRunTextures.push_back(texture);
    }

    for (int i = 0; i < 3; i++)
    {
        sf::Texture texture;
        std::string filename = "../Images/laser/laserTest_";
        filename += (i < 3) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename))
        {
            std::cerr << "Failed to load laser texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        laserTextures.push_back(texture);
    }
    if (!playerJumpTextures.loadFromFile("../Images/The Black Thief Slim Version/Animations/Jump Start/jump_start_009.png"))
    {
        std::cerr << "Failed to load player jump texture." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!playerFallTextures.loadFromFile("../Images/The Black Thief Slim Version/Animations/Jump Fall/jump_fall_000.png"))
    {
        std::cerr << "Failed to load player fall texture." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 7; ++i)
    {
        sf::Texture texture;
        std::string filename = "../Images/Policeman/1/walk_reverse/1_police_Walk_";
        filename += (i < 7) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename))
        {
            std::cerr << "Failed to load player texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        reversePolicemanTextures.push_back(texture);
    }
    for (int i = 0; i < 7; ++i)
    {
        sf::Texture texture;
        std::string filename = "../Images/Policeman/1/walk/1_police_Walk_";
        filename += (i < 7) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename))
        {
            std::cerr << "Failed to load player texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        policemanTextures.push_back(texture);
    }

    if (!coinTexture.loadFromFile("../Images/money/money.png"))
    {
        std::cerr << "Failed to load coin texture." << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Setup initial scene elements
void Game::setupScene()
{
    if (!font.loadFromFile("font/arial.ttf"))
    {
        std::cerr << "Failed to load font." << std::endl;
        exit(EXIT_FAILURE);
    }

    background1.setTexture(backgroundTexture1);
    background2.setTexture(backgroundTexture2);

    player.setTexture(playerRunTextures[0]);
    for (sf::Sprite &coin : coins)
    {
        coin.setTexture(coinTexture);
    }

    reversePoliceman.setTexture(reversePolicemanTextures[0]);
    player.setTexture(playerTextures[0]);
    policeman.setTexture(policemanTextures[0]);
    laser.setTexture(laserTextures[0]);

    float scaleX = static_cast<float>(window.getSize().x) / background1.getTexture()->getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / background1.getTexture()->getSize().y;
    float scaleFactor = std::max(scaleX, scaleY);

    background1.setScale(scaleFactor, scaleFactor);
    background2.setScale(scaleFactor, scaleFactor);
    background1.setPosition(0.f, 0.f);
    background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0.f);

    player.setPosition(200.f, initialYPosition);
    player.setScale(0.14, 0.14);
    policeman.setPosition(800.f, 800.f + blueRectangle.getSize().y - 50);
    policeman.setScale(0.12, 0.12);
    reversePoliceman.setPosition(800.f, initialYPosition + 85); // Align policeman below player
    reversePoliceman.setScale(0.12, 0.12);

    laser.setPosition(0.f, 400.f);

    frontground1.setTexture(frontgroundTexture1);
    frontground2.setTexture(frontgroundTexture2);
    frontground1.setScale(scaleFactor, scaleFactor);
    frontground2.setScale(scaleFactor, scaleFactor);
    frontground1.setPosition(0.f, 0.f);
    frontground2.setPosition(frontground1.getPosition().x + frontground1.getGlobalBounds().width, 0.f);

    // Initialize coins
    for (int i = 0; i < 20; ++i)
    { // Create 20 coins
        sf::Sprite coinSprite;
        coinSprite.setTexture(coinTexture);            // Set coin texture
        coinSprite.setPosition(400.f + i * 50, 400.f); // Adjust the initial position as needed
        coinSprite.setScale(0.1f, 0.1f);               // Adjust scale as needed
        coins.push_back(coinSprite);                   // Add coin to vector
    }
}

// Main game loop
int Game::run()
{
    while (window.isOpen())
    {

        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
    return 0;
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
            isSpacePressed = true;
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            isSpacePressed = false;
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            pause = !pause;
    }
}

// Update game state
void Game::update(sf::Time deltaTime)
{
    if (pause)
        return;

    sf::Time DeltaTime = clock.restart();
    float dtSeconds = deltaTime.asSeconds();

    policemanTimeElapsed += dtSeconds;
    if (policemanTimeElapsed >= animationSpeed)
    {
        policemanCurrentFrame = (policemanCurrentFrame + 1) % 7; // Assuming there are 7 frames
        policeman.setTexture(policemanTextures[policemanCurrentFrame]);
        policemanTimeElapsed = 0.0f;
    }

    reversePolicemanTimeElapsed += dtSeconds;
    if (reversePolicemanTimeElapsed >= animationSpeed)
    {
        reversePolicemanCurrentFrame = (reversePolicemanCurrentFrame + 1) % 7; // Assuming there are 7 frames
        reversePoliceman.setTexture(reversePolicemanTextures[reversePolicemanCurrentFrame]);
        reversePolicemanTimeElapsed = 0.0f;
    }

    if (isSpacePressed)
    {
        player.setTexture(playerJumpTextures);
        player.move(0.f, -backgroundSpeed * dtSeconds);
        isJumping = true;
        timeElapsed = 0.0f;
    }
    else if (!isSpacePressed && isJumping)
    {
        player.setTexture(playerFallTextures);
        player.move(0.f, backgroundSpeed * dtSeconds + gravity * dtSeconds);
        timeElapsed = 0.0f;
        if (player.getPosition().y >= initialYPosition)
        {
            player.setPosition(player.getPosition().x, initialYPosition);
            isJumping = false;
        }
    }
    else
        player.move(0.f, backgroundSpeed * dtSeconds + gravity * dtSeconds);

    // Update policeman position and animation
    policemanTimeElapsed += dtSeconds;
    if (policemanTimeElapsed >= animationSpeed)
    {
        policemanCurrentFrame = (policemanCurrentFrame + 1) % 7; // Assuming there are 7 frames
        policeman.setTexture(policemanTextures[policemanCurrentFrame]);
        policemanTimeElapsed = 0.0f;
    }

    reversePolicemanTimeElapsed += dtSeconds;
    if (reversePolicemanTimeElapsed >= animationSpeed)
    {
        reversePolicemanCurrentFrame = (reversePolicemanCurrentFrame + 1) % 7; // Assuming there are 7 frames
        reversePoliceman.setTexture(reversePolicemanTextures[reversePolicemanCurrentFrame]);
        reversePolicemanTimeElapsed = 0.0f;
    }

    // Move policeman from right to left
    float policemanSpeed = 700.0f;          // Adjust speed as needed
    float dx = -policemanSpeed * dtSeconds; // Calculate horizontal movement
    policeman.move(dx, 0);                  // Move the policeman horizontally

    // Check if policeman has moved out of the window
    if (policeman.getPosition().x + policeman.getLocalBounds().width < 0)
    {
        // Reset policeman position to the right side of the window
        policeman.setPosition(window.getSize().x, initialYPosition + blueRectangle.getSize().y - 50);
    }

    float reversePolicemanSpeed = -200.0f;        // Adjust speed as needed
    float ax = reversePolicemanSpeed * dtSeconds; // Calculate horizontal movement
    reversePoliceman.move(ax, 0);                 // Move the policeman horizontally

    // Check if policeman has moved out of the window
    if (reversePoliceman.getPosition().x + reversePoliceman.getLocalBounds().width < 0)
    {
        // Reset policeman position to the right side of the window
        reversePoliceman.setPosition(window.getSize().x, initialYPosition + 85);
    }

    // Update background
    background1.move(-backgroundSpeed * dtSeconds, 0.f);
    background2.move(-backgroundSpeed * dtSeconds, 0.f);

    frontground1.move(-backgroundSpeed * dtSeconds, 0.f);
    frontground2.move(-backgroundSpeed * dtSeconds, 0.f);

    if (background1.getPosition().x + background1.getGlobalBounds().width < 0)
    {
        background1.setPosition(background2.getPosition().x + background2.getGlobalBounds().width, 0.f);
    }

    if (background2.getPosition().x + background2.getGlobalBounds().width < 0)
    {
        background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0.f);
    }

    if (player.getPosition().y > initialYPosition)
    {
        player.setPosition(player.getPosition().x, initialYPosition);
    }

    if (player.getPosition().y < 0)
    {
        player.setPosition(player.getPosition().x, 0);
    }

    if (frontground1.getPosition().x + frontground1.getGlobalBounds().width < 0)
    {
        frontground1.setPosition(frontground2.getPosition().x + frontground2.getGlobalBounds().width, 0.f);
    }

    if (frontground2.getPosition().x + frontground2.getGlobalBounds().width < 0)
    {
        frontground2.setPosition(frontground1.getPosition().x + frontground1.getGlobalBounds().width, 0.f);
    }

    // Update score and player frame
    sf::Time scoreElapsedTime = scoreClock.getElapsedTime();
    if (scoreElapsedTime.asSeconds() >= 1.0f)
    {
        score += 10;
        scoreClock.restart();
    }

    timeElapsed += dtSeconds;
    if (timeElapsed >= 0.1f)
    {
        currentRunFrame = (currentRunFrame + 1) % 15;
        player.setTexture(playerRunTextures[currentRunFrame]);
        timeElapsed = 0.0f;
    }

    laserTimeElapsed += dtSeconds;
    if (laserTimeElapsed >= 1.6f)
    {
        currentLaserFrame = (currentLaserFrame + 1) % 3;
        laser.setTexture(laserTextures[currentLaserFrame]);
        laserTimeElapsed = 0.0f;
    }

    laser.move(0.f, 0.f);
    if (laser.getPosition().x + laser.getGlobalBounds().width < 0 || laser.getPosition().y > window.getSize().y * 0.68f)
    {
        laser.setPosition(window.getSize().x, std::max(0.f, window.getSize().y * 0.68f - static_cast<float>(rand() % 300))); // Adjust the random range as needed
    }

    for (sf::Sprite &coin : coins)
    {
        // Update coin position
        coin.move(-backgroundSpeed * deltaTime.asSeconds(), 0.f);

        // Reset coin position if it goes out of screen
        if (coin.getPosition().x + coin.getGlobalBounds().width < 0 || coin.getPosition().y > window.getSize().y * 0.68f)
        {
            coin.setPosition(window.getSize().x, std::max(0.f, window.getSize().y * 0.68f - static_cast<float>(rand() % 300)));
        }
    }

    if (player.getGlobalBounds().intersects(laser.getGlobalBounds()))
    {
        // Pause the game
        // window.close();
    }
}

// Render all game objects
void Game::render()
{
    window.clear();

    // Draw background
    window.draw(background1);
    window.draw(background2);

    // Draw policeman
    window.draw(policeman);
    window.draw(reversePoliceman);

    // Draw player
    window.draw(player);

    // Draw coins
    for (const sf::Sprite &coin : coins)
    {
        window.draw(coin);
    }

    // Draw laser
    window.draw(laser);

    // Draw frontground
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

    // Draw coins count
    sf::Text coinsText;
    coinsText.setFont(font);
    coinsText.setCharacterSize(24);
    coinsText.setFillColor(sf::Color::White);
    coinsText.setPosition(window.getSize().x - coinsText.getLocalBounds().width - 80, 10);
    coinsText.setString(std::to_string(Coins) + " $");
    window.draw(coinsText);

    window.display();
}
