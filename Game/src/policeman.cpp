#include "../include/policeman.hpp"


Policeman::Policeman(sf::RenderWindow& window) : initialYPosition(), gravity(75.0f), 
                isJumping(false), timeElapsed(0.0f), window(window), currentRunFrame(0), playerSpeed(600.0f){
    loadTextures();
}


void Policeman::loadTextures() {

    for (int i = 0; i < 7; ++i)
    {
        sf::Texture texture;
        std::string filename = "assets/images/sprites/Policeman/1/walk_reverse/1_police_Walk_";
        filename += (i < 7) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename))
        {
            std::cerr << "Failed to load player texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        reversePolicemanTextures.push_back(texture);
    }

    for (int i = 0; i < 7; ++i)
    {
        sf::Texture texture;
        std::string filename = "assets/images/sprites/policeman/1/walk/1_police_Walk_";
        filename += (i < 7) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename))
        {
            std::cerr << "Failed to load player texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        policemanTextures.push_back(texture);
    }    

    for (int i = 0; i < 5; ++i)
    {
        sf::Texture texture;
        std::string filename = "assets/images/sprites/policeman/1/run/1_police_Run_";
        filename += (i < 7) ? "00" + std::to_string(i) : "0" + std::to_string(i);
        filename += ".png";

        if (!texture.loadFromFile(filename))
        {
            std::cerr << "Failed to load player texture: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        runPolicemanTextures.push_back(texture);
    }
}

void Policeman::setupScene() {

    reversePoliceman.setTexture(reversePolicemanTextures[0]);
    runPoliceman.setTexture(runPolicemanTextures[0]);
    policeman.setTexture(policemanTextures[0]);


    policeman.setPosition(800.f, initialYPosition + 85);
    policeman.setScale(0.10, 0.10);
    reversePoliceman.setPosition(800.f, initialYPosition + 85  ); // Align policeman below player
    reversePoliceman.setScale(0.12, 0.12);
    runPoliceman.setPosition(800.f, initialYPosition + 85 );
    runPoliceman.setScale(0.11, 0.11);
}


void Policeman::update(sf::Time deltaTime) {


    sf::Time DeltaTime = clock.restart();
    float dtSeconds = deltaTime.asSeconds();

    policemanTimeElapsed += dtSeconds;
    if (policemanTimeElapsed >= animationSpeed)
    {
        policemanCurrentFrame = (policemanCurrentFrame + 1) % 7; // Assuming there are 7 frames
        policeman.setTexture(policemanTextures[policemanCurrentFrame]);
        policemanTimeElapsed = 0.0f;
    }

    reversePolicemanTimeElapsed += dtSeconds;
    if (reversePolicemanTimeElapsed >= animationSpeed)
    {
        reversePolicemanCurrentFrame = (reversePolicemanCurrentFrame + 1) % 7; // Assuming there are 7 frames
        reversePoliceman.setTexture(reversePolicemanTextures[reversePolicemanCurrentFrame]);
        reversePolicemanTimeElapsed = 0.0f;
    }

    runPolicemanTimeElapsed += dtSeconds;
    if (runPolicemanTimeElapsed >= animationSpeed)
    {
        runPolicemanCurrentFrame = (runPolicemanCurrentFrame + 1) % 5; // Assuming there are 5 frames
        runPoliceman.setTexture(runPolicemanTextures[runPolicemanCurrentFrame]);
        runPolicemanTimeElapsed = 0.0f;
    }   

// Update policeman position and animation
    policemanTimeElapsed += dtSeconds;
    if (policemanTimeElapsed >= animationSpeed)
    {
        policemanCurrentFrame = (policemanCurrentFrame + 1) % 7; // Assuming there are 7 frames
        policeman.setTexture(policemanTextures[policemanCurrentFrame]);
        policemanTimeElapsed = 0.0f;
    }

    reversePolicemanTimeElapsed += dtSeconds;
    if (reversePolicemanTimeElapsed >= animationSpeed) {
        reversePolicemanCurrentFrame = (reversePolicemanCurrentFrame + 1) % 7; // Assuming there are 7 frames
        reversePoliceman.setTexture(reversePolicemanTextures[reversePolicemanCurrentFrame]);
        reversePolicemanTimeElapsed = 0.0f;
    }

    runPolicemanTimeElapsed += dtSeconds;
    if (runPolicemanTimeElapsed >= animationSpeed)
    {
        runPolicemanCurrentFrame = (runPolicemanCurrentFrame + 1) % 5; // Assuming there are 7 frames
        runPoliceman.setTexture(runPolicemanTextures[runPolicemanCurrentFrame]);
        runPolicemanTimeElapsed = 0.0f;
    }


    // Move policeman from right to left
    float policemanSpeed = 700.0f;          // Adjust speed as needed
    float dx = -policemanSpeed * dtSeconds; // Calculate horizontal movement
    policeman.move(dx, 0);                  // Move the policeman horizontally

    // Check if policeman has moved out of the window
    if (policeman.getPosition().x + policeman.getLocalBounds().width < 0)
    {
        // Reset policeman position to the right side of the window
        policeman.setPosition(window.getSize().x, initialYPosition - 30);
    }

   
    float reversePolicemanSpeed = -200.0f; // Adjust speed as needed
    float ax = reversePolicemanSpeed * dtSeconds; // Calculate horizontal movement
    reversePoliceman.move(ax, 0); // Move the policeman horizontally

    // Check if policeman has moved out of the window
    if (reversePoliceman.getPosition().x + reversePoliceman.getLocalBounds().width < 0) {
        // Reset policeman position to the right side of the window
        reversePoliceman.setPosition(window.getSize().x, initialYPosition + 75);
    }

    // Move policeman from right to left
    float runPolicemanSpeed = 500.0f;          // Adjust speed as needed
    float ex = runPolicemanSpeed * dtSeconds; // Calculate horizontal movement
    runPoliceman.move(ex, 0);                  // Move the policeman horizontally

    // Check if policeman has moved out of the window
    if (runPoliceman.getPosition().x > window.getSize().x)
    {
        // Reset policeman position to the right side of the window
        runPoliceman.setPosition(-runPoliceman.getLocalBounds().width, initialYPosition + 50);
    }

} 

void Policeman::drawPoliceman() {
    window.draw(policeman);
    window.draw(reversePoliceman);
    window.draw(runPoliceman);
}