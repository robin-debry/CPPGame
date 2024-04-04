#include "../include/player.hpp"
#include "../include/gameOver.hpp"

Player::Player(sf::RenderWindow& window) : initialYPosition(), gravity(75.0f), 
                isJumping(false), isSpacePressed(false), isDead(false), score(0),
                timeElapsed(0.0f), window(window), currentRunFrame(0), currentDieFrame(0), playerSpeed(600.0f),gameOverActive(false){
    loadTextures();

}

void Player::loadTextures() {
    // Load running textures
    for (int i = 0; i < 15; ++i)
    {
        sf::Texture texture;
        std::string filename = "assets/images/sprites/The Black Thief Slim Version/Animations/Run/run_";
        filename += (i < 10) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename))
        {
            std::cerr << "Failed to load player texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        playerRunTextures.push_back(texture);
    }
    
    if (!playerJumpTextures.loadFromFile("assets/images/sprites/The Black Thief Slim Version/Animations/Jump Start/jump_start_009.png"))
    {
        std::cerr << "Failed to load player jump texture." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!playerFallTextures.loadFromFile("assets/images/sprites/The Black Thief Slim Version/Animations/Jump Fall/jump_fall_000.png"))
    {
        std::cerr << "Failed to load player fall texture." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 14; ++i)
    {
        sf::Texture texture;
        std::string filename = "assets/images/sprites/The Black Thief Slim Version/Animations/Death/death_";
        filename += (i < 10) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename))
        {
            std::cerr << "Failed to load player texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        playerDieTextures.push_back(texture);
    }


    if (!font.loadFromFile("assets/fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Player::setupScene() 
{
    // Load player textures
    player.setTexture(playerRunTextures[0]);
    player.setTexture(playerTextures[0]);

    // Set player position and scale
    player.setPosition(200.f, initialYPosition);
    player.setScale(0.14, 0.14);
}

void Player::update(sf::Time deltaTime) {
    sf::Time DeltaTime = clock.restart();
    float dtSeconds = deltaTime.asSeconds();
    gameOverActive = false;

    if (isDead && !gameOverActive)
    {
        gameOverScreen(window);
        gameOverActive = true;
    }

    if (isDead)
    {
        //Die animation and stay on the last frame in the initialYPosition
        if (currentDieFrame < 14)
        {
            player.setTexture(playerDieTextures[currentDieFrame]);
            currentDieFrame++;
        }
        player.setPosition(player.getPosition().x, initialYPosition);
        return;
    }

    if (isSpacePressed)
    {
        player.setTexture(playerJumpTextures);
        player.move(0.f, -playerSpeed * dtSeconds);
        isJumping = true;
        timeElapsed = 0.0f;
    }
    else if (!isSpacePressed && isJumping)
    {
        player.setTexture(playerFallTextures);
        player.move(0.f, playerSpeed * dtSeconds + gravity * dtSeconds);
        timeElapsed = 0.0f;
        if (player.getPosition().y >= initialYPosition)
        {
            player.setPosition(player.getPosition().x, initialYPosition);
            isJumping = false;
        }
    }
    else
        player.move(0.f, playerSpeed * dtSeconds + gravity * dtSeconds);

    if (player.getPosition().y > initialYPosition)
    {
        player.setPosition(player.getPosition().x, initialYPosition);
    }

    if (player.getPosition().y < 0)
    {
        player.setPosition(player.getPosition().x, 0);
    }

    timeElapsed += dtSeconds;
    if (timeElapsed >= 0.1f)
    {
        currentRunFrame = (currentRunFrame + 1) % 15;
        player.setTexture(playerRunTextures[currentRunFrame]);
        timeElapsed = 0.0f;
    }

    sf::Time scoreElapsedTime = scoreClock.getElapsedTime();
    if (scoreElapsedTime.asSeconds() >= 1.0f)
    {
        score += 10;
        scoreClock.restart();
    }
}

void Player::drawPlayer() {
    window.draw(player);
}

void Player::drawScore() {
    // Draw score text
    sf::Text scoreText;
    sf::Text distanceText;
    scoreText.setFont(font);
    distanceText.setFont(font);
    scoreText.setCharacterSize(60);
    distanceText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::Yellow);
    distanceText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(800, 50);
    distanceText.setPosition(780, 20);
    scoreText.setString(std::to_string(score) + "m");
    distanceText.setString("Distance ");
    window.draw(scoreText);
    window.draw(distanceText);
}

void Player::gameOverScreen(sf::RenderWindow& window) {
    // Create an instance of GameOver class
    GameOver gameOver(window);

    // Loop for handling input and drawing game over screen
    while (true) {
        // Handle input for game over screen
        int selection = gameOver.handleInput(window);
        if (selection == 0) {
            reset();
            gameOverActive = false;
            break;
        } else if (selection == 1) {
            // Quit option selected
            window.close(); // Close the window
            break;
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the game over screen
        gameOver.draw(window);

        window.display();
    }
}

void Player::reset() {
    isDead = false;
    isJumping = false;
    isSpacePressed = false;
    score = 0;
    timeElapsed = 0.0f;
    currentRunFrame = 0;
    currentDieFrame = 0;
    player.setPosition(200.f, initialYPosition);
}