#include "../include/obstacle.hpp"


Obstacle::Obstacle(sf::RenderWindow& window) : player(window), window(window), obstacleSpeed(600.0f){
    loadTextures();
}

void Obstacle::loadTextures() {
    if (!obstacleTexture.loadFromFile("assets/images/sprites/obstacle/obstacle.png"))
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
        // Generate a random number between 0 and 1
        int randomNum = rand() % 2;

        if (randomNum == 0) {
            // Create horizontal obstacle
            sf::Sprite obstacleSpriteHorizontal;
            obstacleSpriteHorizontal.setTexture(obstacleTexture);            // Set obstacle texture
            obstacleSpriteHorizontal.setPosition(400.f + i * 50, 400.f); // Adjust the initial position as needed
            obstacleSpriteHorizontal.setScale(0.6f, 0.6f);               // Adjust scale as needed
            obstaclesHorizontal.push_back(obstacleSpriteHorizontal);                   // Add obstacle to vector
        } else {
            // Create vertical obstacle
            sf::Sprite obstacleSpriteVertical;
            obstacleSpriteVertical.setTexture(obstacleTexture);            // Set obstacle texture
            obstacleSpriteVertical.setPosition(400.f + i * 50, 400.f); // Adjust the initial position as needed
            obstacleSpriteVertical.setScale(0.6f, 0.6f);               // Adjust scale as needed
            obstacleSpriteVertical.setRotation(90); 
            obstaclesVertical.push_back(obstacleSpriteVertical);                   // Add obstacle to vector
        }
    }
}

void Obstacle::update(sf::Time deltaTime, Player& player) {
    sf::Time DeltaTime = clock.restart();
    float dtSeconds = deltaTime.asSeconds();

    // Update positions of horizontal obstacles
    for (sf::Sprite &obstacle : obstaclesHorizontal) {
        sf::Vector2f pos = obstacle.getPosition();
        pos.x += dtSeconds * obstacleSpeed;  // Adjust speed as needed
        obstacle.setPosition(pos);
    }

    // Update positions of vertical obstacles
    for (sf::Sprite &obstacle : obstaclesVertical) {
        sf::Vector2f pos = obstacle.getPosition();
        pos.y += dtSeconds * obstacleSpeed;  // Adjust speed as needed
        obstacle.setPosition(pos);
    }

    // Check for collision between player and obstacle if they are close enough
    for (const sf::Sprite &obstacle : obstaclesHorizontal) {
        sf::Vector2f playerCenter = player.getPosition() + sf::Vector2f(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
        sf::Vector2f obstacleCenter = obstacle.getPosition() + sf::Vector2f(obstacle.getGlobalBounds().width / 2, obstacle.getGlobalBounds().height / 2);
        float distance = std::sqrt(std::pow(playerCenter.x - obstacleCenter.x, 2) + std::pow(playerCenter.y - obstacleCenter.y, 2));
        float minCollisionDistance = 75.0f; // Increased distance

        if (distance < minCollisionDistance)
        {                                                                                                 // Increase obstacles count
            //window.close();
        }
    
    }

    for (const sf::Sprite &obstacle : obstaclesVertical) {
        sf::Vector2f playerCenter = player.getPosition() + sf::Vector2f(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
        sf::Vector2f obstacleCenter = obstacle.getPosition() + sf::Vector2f(obstacle.getGlobalBounds().width / 2, obstacle.getGlobalBounds().height / 2);
        float distance = std::sqrt(std::pow(playerCenter.x - obstacleCenter.x, 2) + std::pow(playerCenter.y - obstacleCenter.y, 2));
        float minCollisionDistance = 75.0f; // Increased distance

        if (distance < minCollisionDistance)
        {                                                                                                 // Increase obstacles count
            //window.close();
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
}

        