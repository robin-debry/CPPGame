#include "../include/background.hpp"
#include "../include/coin.hpp"
#include "../include/game.hpp"
#include "../include/laser.hpp"
#include "../include/player.hpp"
#include "../include/policeman.hpp"
#include "SFML/Audio.hpp"


// Main function: creates game instance and runs it
int main() {
    
    Game background;
    return background.run();

    Game coin;
    return coin.run();

    Game game;
    return game.run();

    Game laser;
    return laser.run();

    Game player;
    return player.run();

    Game policeman;
    return policeman.run();
}
