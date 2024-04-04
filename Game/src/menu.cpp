#include "../include/menu.hpp"

Menu::Menu(sf::RenderWindow& window) {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        // Handle font loading failure
    }

    titleText.setFont(font);
    titleText.setString("Jumping Joyride");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(sf::Vector2f(window.getSize().x / 2 - 150, 100));

    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(60);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(sf::Vector2f(window.getSize().x / 2 - 50, 300));

    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(60);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(sf::Vector2f(window.getSize().x / 2 - 50, 450));

    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black); // Clear the window

    // Draw the title
    window.draw(titleText);

    // Draw the menu items
    window.draw(playText);
    window.draw(quitText);

        // Set the color for the selected item
    if (selectedItemIndex == 0) {
        playText.setFillColor(sf::Color::Red);
        quitText.setFillColor(sf::Color::White); // Reset other item's color
    } else if (selectedItemIndex == 1) {
        playText.setFillColor(sf::Color::White); // Reset other item's color
        quitText.setFillColor(sf::Color::Red);
    }
}


int Menu::handleInput(sf::RenderWindow& window) {
    sf::Event event;
   while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selectedItemIndex > 0)
                            selectedItemIndex--;
                        break;
                    case sf::Keyboard::Down:
                        if (selectedItemIndex < 1)
                            selectedItemIndex++;
                        break;
                    case sf::Keyboard::Return:
                        return selectedItemIndex;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }

    return -1;

}