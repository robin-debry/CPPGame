#include "../include/laser.hpp"

Laser::Laser(sf::RenderWindow& window) : player(window), window(window), laserSpeed(600.0f) {
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
        laserTexture.push_back(texture);
    }
}

void Laser::setupScene() {
    laser.setTexture(laserTexture[0]);
    laser.setPosition(0.f, 500.f);
}

void Laser::update(sf::Time deltaTime) {
    sf::Time DeltaTime = clock.restart();
    float dtSeconds = deltaTime.asSeconds();

     laser.setPosition(0.f, 400.f);


}

void Laser::drawLaser() {
    window.draw(laser);
}