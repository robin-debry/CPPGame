// Windows initial size
#define WIDTH 800
#define HEIGHT 600

void windowInit(sf::RenderWindow &window) {
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Game");
    window.setFramerateLimit(60);
}

// Background
void drawBackground(sf::RenderWindow &window, sf::Sprite &background); {
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile(BACKGROUND_SPRITE_PATH);
    background.setTexture(backgroundTexture);
    window.draw(background);
}

