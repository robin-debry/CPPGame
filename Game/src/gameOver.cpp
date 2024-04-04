#include "../include/gameOver.hpp"

GameOver::GameOver(sf::RenderWindow& window) {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        // Handle font loading failure
    }

    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(sf::Vector2f(window.getSize().x / 2 - 100, 100));

    retryText.setFont(font);
    retryText.setString("Retry");
    retryText.setCharacterSize(40);
    retryText.setFillColor(sf::Color::White);
    retryText.setPosition(sf::Vector2f(window.getSize().x / 2 - 50, 200));

    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(40);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(sf::Vector2f(window.getSize().x / 2 - 50, 300));
    

    selectedItemIndex = 0;
}

void GameOver::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black); // Clear the window

    // Draw the game over text
    window.draw(gameOverText);

    // Draw the menu items
    window.draw(retryText);
    window.draw(quitText);

    // Set the color for the selected item
    if (selectedItemIndex == 0) {
        retryText.setFillColor(sf::Color::Red);
        quitText.setFillColor(sf::Color::White); // Reset other item's color
    } else if (selectedItemIndex == 1) {
        retryText.setFillColor(sf::Color::White); // Reset other item's color
        quitText.setFillColor(sf::Color::Red);
    }
}

int GameOver::handleInput(sf::RenderWindow& window) {
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
