#include "../include/background.hpp"

Background::Background(sf::RenderWindow& window) : window(window), backgroundSpeed(600.0f){
    loadTextures();
    background1.setTexture(backgroundTexture1);
    background2.setTexture(backgroundTexture2); 
    frontground1.setTexture(frontgroundTexture1);
    frontground2.setTexture(frontgroundTexture2);
    background1.setPosition(0, 0);
    background2.setPosition(background1.getGlobalBounds().width, 0);
    frontground1.setPosition(0, 0);
    frontground2.setPosition(frontground1.getGlobalBounds().width, 0);
}


void Background::loadTextures() {
    if (!backgroundTexture1.loadFromFile("assets/images/background.jpg") || !backgroundTexture2.loadFromFile("assets/images/background.jpg")) {
        std::cerr << "Failed to load background textures." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!frontgroundTexture1.loadFromFile("assets/images/frontground.png") || !frontgroundTexture2.loadFromFile("assets/images/frontground.png")) {
        std::cerr << "Failed to load frontground textures." << std::endl;
        exit(EXIT_FAILURE);
    }

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
}

void Background::setupScene()
{
    // Background
    background1.setTexture(backgroundTexture1);
    background2.setTexture(backgroundTexture2);

    float scaleX = static_cast<float>(window.getSize().x) / background1.getTexture()->getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / background1.getTexture()->getSize().y;
    float scaleFactor = std::max(scaleX, scaleY);

    background1.setScale(scaleFactor, scaleFactor);
    background2.setScale(scaleFactor, scaleFactor);
    background1.setPosition(0.f, 0.f);
    background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0.f);

    // Frontground
    frontground1.setTexture(frontgroundTexture1);
    frontground2.setTexture(frontgroundTexture2);

    frontground1.setScale(scaleFactor, scaleFactor);
    frontground2.setScale(scaleFactor, scaleFactor);
    frontground1.setPosition(0.f, 0.f);
    frontground2.setPosition(frontground1.getPosition().x + frontground1.getGlobalBounds().width, 0.f);
}

void Background::update(sf::Time deltaTime) {
    // Scroll backgrounds
    float dtSeconds = deltaTime.asSeconds();
    sf::Time DeltaTime = clock.restart();
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

    if (frontground1.getPosition().x + frontground1.getGlobalBounds().width < 0)
    {
        frontground1.setPosition(frontground2.getPosition().x + frontground2.getGlobalBounds().width, 0.f);
    }

    if (frontground2.getPosition().x + frontground2.getGlobalBounds().width < 0)
    {
        frontground2.setPosition(frontground1.getPosition().x + frontground1.getGlobalBounds().width, 0.f);
    }
}

void Background::drawBackground() {
    window.draw(background1);
    window.draw(background2);

}

void Background::drawFrontground() {
    window.draw(frontground1);
    window.draw(frontground2);
}
