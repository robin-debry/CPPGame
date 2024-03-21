# Technical Specification

## Language

The game is written in C++.

## Libraries

### SFML

SFML is a simple and fast multimedia library. It is written in C++ and it is used to create games and multimedia applications. It provides a simple interface to the various components of your PC, to ease the development of games and multimedia applications. It is composed of five modules: the `system`, `window`, `graphics`, `audio` and `network` modules.

## Classes

### Class 1 : Human

- speed
- life
- size
- physics(gravity)
- sprite

### Subclass 1 : Player

- name
- jump
- direction
- maxHeight
- minHeight
- sprite
- initialWidth

### Subclass 2 : PoliceMan

- randomDirection
- speed
- differentStates

## Class 2 : Items 

- placement 
- sprite
- size 

### SubClass 1 : Coin (reward)

- value
- sprite

### SubClass 2 : Missiles

- speed
- sprite
- direction

## Music

For the music we will use the following songs:

- [On soundCloud](https://on.soundcloud.com/MMTPRLJ4Lrom9nrFA)

## How implement the music in C++

```cpp
#include <SFML/Audio.hpp>

int main() {
    sf::Music music;
    if (!music.openFromFile("music.ogg")) {
        return -1; // error
    }
    music.play();
}
```

## How to loop the music in C++

```cpp
music.setLoop(true);
```

## How to create a class in C++

```cpp

class <ClassName> {
    public:
        <VariableType> <VariableName>;
        <VariableType> <VariableName>;
        <VariableType> <VariableName>;
        <VariableType> <VariableName>;
        <VariableType> <VariableName>;
};
```

## How to create a subclass in C++

```cpp
class <SubClassName> : public <ClassName> {
    public:
       <VariableType> <VariableName>;
        <VariableType> <VariableName>;
        <VariableType> <VariableName>;
        <VariableType> <VariableName>;
        <VariableType> <VariableName>;
        <VariableType> <VariableName>;
};
```

## How to create a method in C++

```cpp
<ReturnType> <ClassName>::<MethodName>(<ParameterType> <ParameterName>) {
}
```
