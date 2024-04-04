g++ -std=c++11 src/main.cpp src/game.cpp src/background.cpp src/player.cpp src/coin.cpp src/laser.cpp src/obstacle.cpp -o game -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./game
