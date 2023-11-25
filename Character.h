#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>

// Abstract base class for characters
class Character {
public:
    // Pure virtual function to display information about the character
    virtual void displayInfo() const = 0;

    // Pure virtual function to simulate a fight between the character and a guard
    virtual void fight(int& characterLives, int& guardLives) const = 0;

    // Virtual destructor for proper polymorphic behavior
    virtual ~Character() = default;

    // Pure virtual function to get the name of the character
    virtual std::string getName() const = 0;

    // Pure virtual function to get the winning probability of the character
    virtual double getWinProb() const = 0;
};

// Derived class representing characters from the show Money Heist
class MoneyHeistCharacter : public Character {
public:
    // Constructor for MoneyHeistCharacter class
    MoneyHeistCharacter(const std::string& name, double winProb);

    // Implementation of the displayInfo function
    void displayInfo() const override;

    // Implementation of the fight function
    void fight(int& characterLives, int& guardLives) const override;

    // Implementation of the getName function
    std::string getName() const override;

    // Implementation of the getWinProb function
    double getWinProb() const override;

private:
    std::string name;
    double winProb;
};


class CharacterFactory {
public:
    virtual Character* createCharacter() const = 0;
    virtual ~CharacterFactory() = default;
};


class MoneyHeistCharacterFactory : public CharacterFactory {
public:

    MoneyHeistCharacterFactory(const std::string &characterName, double winProb);

    Character* createCharacter() const override;

private:
    std::string characterName;

    // Member variable to store the winning probability of the character
    double winProb;
};

#endif