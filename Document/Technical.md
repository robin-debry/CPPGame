# Technical Specification

## Class 1 : Human

- speed
- life
- size
- sprite
- physics(gravity)

### Subclass 1 : Player

- name
- jump
- direction
- maxHeight
- minHeight
- initialWidth

### Subclass 2 : PoliceMan

- randomDirection
- speed
- differentStates

## Class 2 : Coin (reward)

- value
- size
- sprite
- placement

## Class 3 : Missiles

- speed
- size
- sprite
- placement
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
