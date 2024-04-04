#include "../include/laser.hpp"

Laser::Laser(sf::RenderWindow& window) : player(window), window(window), laserSpeed(600.0f), currentLaserFrame(0), laserTimeElapsed(0.0f), laserTime(0.0f), laserTimeDuration(7.0f) {
    loadTextures();
}

void Laser::loadTextures() {
    for (int i = 0; i < 3; i++)
    {
        sf::Texture texture;
        std::string filename = "assets/images/sprites/laser/laserTest_";
        filename += (i < 3) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename))
        {
            std::cerr << "Failed to load laser texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        laserTextures.push_back(texture);
    }
}

void Laser::setupScene() {
    laser.setTexture(laserTextures[0]);
     sf::Vector2u windowSize = window.getSize();
     unsigned int windowHeight = windowSize.y;
     float yPosition = static_cast<float>(rand() % static_cast<int>(windowHeight - laser.getGlobalBounds().height));
     laser.setPosition(0.0f, yPosition);

}

void Laser::update(sf::Time deltaTime, Player& player) {

    sf::Time DeltaTime = clock.restart();
    float dtSeconds = deltaTime.asSeconds();

    laserTimeElapsed += dtSeconds;
    laserTime += dtSeconds;

    if (laserTime >= laserTimeDuration)
    {
      
    if (laserTimeElapsed >= 1.6f)
    {
        currentLaserFrame = (currentLaserFrame + 1) % 3;
        laser.setTexture(laserTextures[currentLaserFrame]);
        laserTimeElapsed = 0.0f;
    }

    else if (laserTime >= 11.0f)
    {
        laserTime = 0.0f;
        laser.setPosition(0.0f, static_cast<float>(rand() % static_cast<int>(window.getSize().y - laser.getGlobalBounds().height)));
    }


}
}

void Laser::drawLaser() {
    if (laserTime >= laserTimeDuration)
    {
        window.draw(laser);
    }
}