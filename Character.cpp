#include <iostream>
#include "Character.h"

// Constructor for MoneyHeistCharacter class
MoneyHeistCharacter::MoneyHeistCharacter(const std::string& name, double winProb) : name(name), winProb(winProb){}

// Implementation of the displayInfo function
void MoneyHeistCharacter::displayInfo() const {
    std::cout << name << std::endl;
}

// Implementation of the fight function
void MoneyHeistCharacter::fight(int& characterLives, int& guardLives) const {
    std::cout << name << " is fighting the guards!" << std::endl;

    // The fight logic based on win probability
    double randomProb = static_cast<double>(rand()) / RAND_MAX; // Random number between 0 and 1

    if (randomProb <= winProb) {
        std::cout << name << " defeated a guard!" << std::endl;
        --guardLives;
    } else {
        std::cout << "Guard defeated " << name << "! " << name << " failed to defeat the guard." << std::endl;
        --characterLives;
    }

    std::cout << name << " defeated a guard!" << std::endl;
    --guardLives;
}

// Implementation of the getName function
std::string MoneyHeistCharacter::getName() const {
    return name;
}

// Implementation of the getWinProb function
double MoneyHeistCharacter::getWinProb() const {
    return winProb;
}

// Constructor for MoneyHeistCharacterFactory class
MoneyHeistCharacterFactory::MoneyHeistCharacterFactory(const std::string& characterName, double winProb) : characterName(characterName), winProb(winProb) {}

// Implementation of the createCharacter function
Character* MoneyHeistCharacterFactory::createCharacter() const {
    return new MoneyHeistCharacter(characterName, winProb);
}