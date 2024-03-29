#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jetpack Joyride", sf::Style::Fullscreen);

    sf::Texture backgroundTexture1;
    if (!backgroundTexture1.loadFromFile("imgs/background.jpg")) {
        return EXIT_FAILURE;
    }

    sf::Texture backgroundTexture2;
    if (!backgroundTexture2.loadFromFile("imgs/background.jpg")) {
        return EXIT_FAILURE;
    }

    std::vector<sf::Texture> playerTextures;
    for (int i = 0; i < 15; ++i) {
        sf::Texture texture;
        std::string filename = "../Images/The Black Thief Slim Version/Animations/Run/run_";
        if (i < 10)
            filename += "00" + std::to_string(i) + ".png";
        else
            filename += "0" + std::to_string(i) + ".png";

        if (!texture.loadFromFile(filename)) {
            std::cerr << "Failed to load texture: " << filename << std::endl;
            return EXIT_FAILURE;
        }
        playerTextures.push_back(texture);
    }


    sf::Sprite background1(backgroundTexture1);
    sf::Sprite background2(backgroundTexture2);
    sf::Sprite player;
    player.setTexture(playerTextures[0]);

    float scaleX = static_cast<float>(window.getSize().x) / background1.getTexture()->getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / background1.getTexture()->getSize().y;
    float scaleFactor = std::max(scaleX, scaleY);

    // Animation variables
    int currentFrame = 0;

    background1.setScale(scaleFactor, scaleFactor);
    background2.setScale(scaleFactor, scaleFactor);

    background1.setPosition(0.f, 0.f);
    background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0.f);

    float backgroundSpeed = 600.0f; // Increased background speed
    float gravity = 75.0f;

    float initialYPosition = 600.f; // Initial y position for both rectangles

    

    sf::RectangleShape blueRectangle(sf::Vector2f(50.f, 50.f));
    blueRectangle.setFillColor(sf::Color::Blue);
    blueRectangle.setPosition(400.f, initialYPosition);
    player.setPosition(200.f, initialYPosition);
    player.setScale(0.14, 0.14);

    sf::RectangleShape redRectangle(sf::Vector2f(50.f, 50.f));
    redRectangle.setFillColor(sf::Color::Red);
    redRectangle.setPosition(800.f, initialYPosition + blueRectangle.getSize().y -50); // Align red below blue

    bool isSpacePressed = false;

    sf::Clock clock;
    sf::Clock scoreClock; // Clock to track score increase

    int score = 0; // Initialize score

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float dtSeconds = deltaTime.asSeconds();

        sf::Time scoreElapsedTime = scoreClock.getElapsedTime();
        if (scoreElapsedTime.asSeconds() >= 1.0f) { // Increase score every second
            score += 10;
            scoreClock.restart();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                isSpacePressed = true;
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
                isSpacePressed = false;
        }

        if (isSpacePressed)
            // blueRectangle.move(0.f, -backgroundSpeed * dtSeconds); // Move the blue rectangle upwards
            player.move(0.f, -backgroundSpeed * dtSeconds); // Move the blue rectangle upwards
        else
            // blueRectangle.move(0.f, backgroundSpeed * dtSeconds + gravity * dtSeconds); // Move the blue rectangle downwards with gravity
            player.move(0.f, backgroundSpeed * dtSeconds + gravity * dtSeconds); // Move the blue rectangle downwards with gravity

        redRectangle.move(-backgroundSpeed * dtSeconds, 0.f); // Move the red rectangle towards the left

        background1.move(-backgroundSpeed * dtSeconds, 0.f);
        background2.move(-backgroundSpeed * dtSeconds, 0.f);

        if (background1.getPosition().x + background1.getGlobalBounds().width < 0) {
            background1.setPosition(background2.getPosition().x + background2.getGlobalBounds().width, 0.f);
        }

        if (background2.getPosition().x + background2.getGlobalBounds().width < 0) {
            background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0.f);
        }

        // if (blueRectangle.getPosition().y > initialYPosition) {
        //     blueRectangle.setPosition(blueRectangle.getPosition().x, initialYPosition);
        // }

        if (player.getPosition().y > initialYPosition) {
            player.setPosition(player.getPosition().x, initialYPosition);
        }

        if (player.getPosition().y < 0) {
            player.setPosition(player.getPosition().x, 0);
        }


        // Draw score
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            return EXIT_FAILURE;
        }

        sf:: Text GameOver;
        GameOver.setFont(font);
        GameOver.setCharacterSize(50);
        GameOver.setFillColor(sf::Color::Black);
        GameOver.setPosition(800, 800);
        GameOver.setString("Game Over");

        if (redRectangle.getPosition().x < 0) {
            window.draw(GameOver); // Reset the red rectangle position when it goes out of the window
        }

        static float timeElapsed = 0.0f;
        timeElapsed += dtSeconds;
        if (timeElapsed >= 0.1f) {
            currentFrame = (currentFrame + 1) % 15; // Loop through frames
            player.setTexture(playerTextures[currentFrame]);
            timeElapsed = 0.0f;
        }

        window.clear();
        window.draw(background1);
        window.draw(background2);
        window.draw(player);
        window.draw(redRectangle);


        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);
        scoreText.setString("Score: " + std::to_string(score));

        window.draw(scoreText);

        window.display();
    }

    return 0;
}
