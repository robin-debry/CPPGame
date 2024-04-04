#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>



namespace sf {
    class RenderWindow;
}

class Player {
public:

    Player(sf::RenderWindow& window);
    void update(sf::Time deltaTime);
    void drawPlayer();
    void loadTextures();
    void setupScene();
    void drawScore();
    void gameOverScreen(sf::RenderWindow& window);
    void reset();

    bool isSpacePressed;
    bool isDead;
    float initialYPosition;

    sf::Vector2f getPosition() const {
        return player.getPosition();
    }

    sf::FloatRect getGlobalBounds() const {
        return player.getGlobalBounds();
    }

    int score;

private:

    sf::Sprite player;
    sf::RenderWindow& window;
    std::vector<sf::Texture> playerRunTextures;
    sf::Texture playerJumpTextures;
    sf::Texture playerFallTextures;
    std::vector<sf::Texture> playerDieTextures;
    sf::Font font;
    std::vector<sf::Texture> playerTextures;
    sf::Clock clock;
    sf::Clock scoreClock;

    int currentRunFrame;
    int currentDieFrame;
    float gravity;
    bool isJumping;
    float timeElapsed;
    float playerSpeed;
    bool gameOverActive = false;
    

};

#endif
