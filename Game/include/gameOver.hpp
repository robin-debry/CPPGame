
#ifndef GAME_OVER_HPP
#define GAME_OVER_HPP

#include <SFML/Graphics.hpp>

class GameOver {
public:
    GameOver(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    int handleInput(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text gameOverText;
    sf::Text retryText;
    sf::Text quitText;
    int selectedItemIndex;
};

#endif