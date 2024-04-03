#include "../include/player.hpp"

Player::Player(sf::RenderWindow& window) : initialYPosition(), gravity(75.0f), 
                isJumping(false), isSpacePressed(false),
                timeElapsed(0.0f), window(window), currentRunFrame(0), playerSpeed(600.0f){
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
}

void Player::drawPlayer() {
    window.draw(player);
}

