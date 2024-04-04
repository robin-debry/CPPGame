#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window); 
    int handleInput(sf::RenderWindow& window); 

private:
    sf::Font font;
    sf::Text titleText;
    sf::Text playText;
    sf::Text quitText;
    int selectedItemIndex;
};

#endif 
