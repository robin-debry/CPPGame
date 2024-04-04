#include "../include/obstacle.hpp"
#include "../include/gameOver.hpp"


Obstacle::Obstacle(sf::RenderWindow& window) : player(window), window(window), obstacleSpeed(600.0f),gameOverActive(false){
    loadTextures();
}

void Obstacle::loadTextures() {
    if (!obstacleHorizontalTexture.loadFromFile("assets/images/sprites/obstacle/obstacleHorizontal.png"))
    {
        std::cerr << "Failed to load obstacle texture." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!obstacleVerticalTexture.loadFromFile("assets/images/sprites/obstacle/obstacleVertical.png"))
    {
        std::cerr << "Failed to load obstacle texture." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Obstacle::setupScene() 
{
    // Initialize obstacles
    for (int i = 0; i < 1; ++i)
    { 
        // Create horizontal obstacle
        obstacleSpriteHorizontal.setTexture(obstacleHorizontalTexture);            // Set obstacle texture
        obstacleSpriteHorizontal.setPosition(200.f, 300.f); // Adjust the initial position as needed
        obstacleSpriteHorizontal.setScale(0.40f, 0.40f);               // Adjust scale as needed
        obstaclesHorizontal.push_back(obstacleSpriteHorizontal);                   // Add obstacle to vector
        
        // Create vertical obstacle
        obstacleSpriteVertical.setTexture(obstacleVerticalTexture);            // Set obstacle texture
        obstacleSpriteVertical.setPosition(700.f, 800.f); // Adjust the initial position as needed
        obstacleSpriteVertical.setScale(0.40f, 0.40f);               // Adjust scale as needed
        obstaclesVertical.push_back(obstacleSpriteVertical);                   // Add obstacle to vector
    
    }
}

void Obstacle::update(sf::Time deltaTime, Player& player) {
    sf::Time DeltaTime = clock.restart();
    float dtSeconds = deltaTime.asSeconds();
    gameOverActive = false;
    
    for (sf::Sprite &obstacle : obstaclesHorizontal)
    {
        // Update obstacle position
        obstacle.move(-obstacleSpeed * deltaTime.asSeconds(), 0.f);

        // Reset obstacle position if it goes out of screen
        if (obstacle.getPosition().x + obstacle.getGlobalBounds().width < 0 || obstacle.getPosition().y > window.getSize().y * 0.25f)
        {
            obstacle.setPosition(window.getSize().x, std::max(0.f, window.getSize().y * 0.25f - static_cast<float>(rand() % 300)));
        }

    // Check for collision between player and obstacle if they are close enough
        sf::Vector2f playerCenter = player.getPosition() + sf::Vector2f(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
        sf::Vector2f obstacleCenter = obstacle.getPosition() + sf::Vector2f(obstacle.getGlobalBounds().width / 2, obstacle.getGlobalBounds().height / 2);
        float distanceX = std::sqrt(std::pow(playerCenter.x - obstacleCenter.x, 2));
        float distanceY = std::sqrt(std::pow(playerCenter.y - obstacleCenter.y, 2));
        float minCollisionDistanceX = 200.0f; // Increased distance
        float minCollisionDistanceY = 75.0f; // Increased distance

        if (distanceX < minCollisionDistanceX && distanceY < minCollisionDistanceY)
        {                                                                                                                                                                                                                  // Increase obstacles count
            if (!gameOverActive)
            {
               player.gameOverScreen(window);
               gameOverActive = true;
            }
        }
    }

    for (sf::Sprite &obstacle : obstaclesVertical)
    {
        // Update obstacle position
        obstacle.move(-obstacleSpeed * deltaTime.asSeconds(), 0.f);

        // Reset obstacle position if it goes out of screen
        if (obstacle.getPosition().x + obstacle.getGlobalBounds().width < 0 || obstacle.getPosition().y > window.getSize().y * 0.45f)
        {
            obstacle.setPosition(window.getSize().x, std::max(0.f, window.getSize().y * 0.45f - static_cast<float>(rand() % 300)));
        }

    // Check for collision between player and obstacle if they are close enough
        sf::Vector2f playerCenter = player.getPosition() + sf::Vector2f(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
        sf::Vector2f obstacleCenter = obstacle.getPosition() + sf::Vector2f(obstacle.getGlobalBounds().width / 2, obstacle.getGlobalBounds().height / 2);
        float distanceX = std::sqrt(std::pow(playerCenter.x - obstacleCenter.x, 2));
        float distanceY = std::sqrt(std::pow(playerCenter.y - obstacleCenter.y, 2));
        float minCollisionDistanceY = 200.0f; // Increased distance
        float minCollisionDistanceX = 75.0f; // Increased distance

        if (distanceX < minCollisionDistanceX && distanceY < minCollisionDistanceY)
        {                                                                                                        // Increase score                                                                                                           // Increase obstacles count
          if (!gameOverActive)
          {
            player.gameOverScreen(window);
            gameOverActive = true;
          }  
        }
    }
}

void Obstacle::drawObstacle() {
    for (const sf::Sprite &obstacle : obstaclesVertical)
    {
        window.draw(obstacle);
    }
    
    for (const sf::Sprite &obstacle : obstaclesHorizontal)
    {
        window.draw(obstacle);
    }

    for (const sf::Sprite &obstacle : obstaclesHorizontal)
    {
        window.draw(obstacle);
    }
}

        