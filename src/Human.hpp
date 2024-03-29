#include <iostream>
#include <string>

class Human {
    public: 
        int speed; 
        bool life; 
        int size; 
        int gravity; 
        void sprite(); 

};

class Player : public Human {
    public:
        std::string Name; 
        int jump; 
        int direction;
        int maxHeight;
        int minHeight;
        void sprite();
        int initialWidth;
};

class PoliceMan : public Human {
    public:
        int randomDirection;
        int speed;
        bool diffrentState; 
};

void Human::sprite() {
    std::cout << "Human sprite" << std::endl;
}

void Player::sprite() {
    std::cout << "Player sprite" << std::endl;
}