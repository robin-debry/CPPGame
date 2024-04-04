#ifndef LASER_HPP
#define LASER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <SFML/Audio.hpp>

#include "player.hpp"

namespace sf {
    class RenderWindow;
}

class Laser {
public:

    Player player;
    Laser(sf::RenderWindow& window);
    void update(sf::Time deltaTime, Player& player);
    void drawLaser();
    void loadTextures();
    void setupScene();

private:

    sf::RenderWindow& window;
    // sf::Music music;
    sf::Clock clock;
    std::vector<sf::Texture> laserTextures;
    sf::Sprite laser;
    sf::Sprite warning;
    sf::Texture warningTexture;

    float laserSpeed;
    float laserTimeElapsed = 0.0f;
    int currentLaserFrame;
    float laserTime = 0.0f;
    float laserTimeDuration = 7.0f;
    float warningTime = 0.0f;
    bool warningFlag = false;
    sf::SoundBuffer laserSoundBuffer;
    sf::Sound laserSound;
    bool laserSoundIsPlaying = false;

    void loadSound();


};
#endif

