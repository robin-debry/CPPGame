#include "../include/coin.hpp"
#include <cmath>

Coin::Coin(sf::RenderWindow& window) : player(window), window(window), coinSpeed(600.0f), Coins(0){
    loadTextures();
}

void Coin::loadTextures() {
    if (!coinTexture.loadFromFile("assets/images/sprites/money/money.png"))
    {
        std::cerr << "Failed to load coin texture." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!font.loadFromFile("assets/fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Coin::setupScene() 
{
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

void Coin::update(sf::Time deltaTime, Player& player) {
    sf::Time DeltaTime = clock.restart();
    float dtSeconds = deltaTime.asSeconds();

    for (sf::Sprite &coin : coins)
    {
        // Update coin position
        coin.move(-coinSpeed * deltaTime.asSeconds(), 0.f);

        // Reset coin position if it goes out of screen
        if (coin.getPosition().x + coin.getGlobalBounds().width < 0 || coin.getPosition().y > window.getSize().y * 0.68f)
        {
            coin.setPosition(window.getSize().x, std::max(0.f, window.getSize().y * 0.68f - static_cast<float>(rand() % 300)));
        }

    // Check for collision between player and coin if they are close enough
        sf::Vector2f playerCenter = player.getPosition() + sf::Vector2f(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
        sf::Vector2f coinCenter = coin.getPosition() + sf::Vector2f(coin.getGlobalBounds().width / 2, coin.getGlobalBounds().height / 2);
        float distance = std::sqrt(std::pow(playerCenter.x - coinCenter.x, 2) + std::pow(playerCenter.y - coinCenter.y, 2));
        float minCollisionDistance = 75.0f; // Increased distance

        if (distance < minCollisionDistance)
        {                                                                                                        // Increase score
            Coins += 100;                                                                                                            // Increase coins count
            coin.setPosition(window.getSize().x, rand() % (window.getSize().y - static_cast<int>(coin.getGlobalBounds().height))); // Reset coin position
        }
        
    }
}

void Coin::drawCoin() {
    for (const sf::Sprite &coin : coins)
    {
        window.draw(coin);
    }
}

void Coin::drawCoinScore() {
     // Draw coins text
    sf::Text coinsText;
    coinsText.setFont(font);
    coinsText.setCharacterSize(24);
    coinsText.setFillColor(sf::Color::White);
    coinsText.setPosition(window.getSize().x - coinsText.getLocalBounds().width - 80, 10);
    coinsText.setString(std::to_string(Coins) + " $");
    window.draw(coinsText);
}