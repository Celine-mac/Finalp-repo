#ifndef SUPERPOWER_H
#define SUPERPOWER_H

#include <iostream>
#include <string>

// Abstract base class for superpowers
class SuperPower {
public:
    // Pure virtual function to use the superpower
    virtual void usePower() const = 0;

    // Virtual destructor for proper polymorphic behavior
    virtual ~SuperPower() = default;
};

// Derived class representing a superpower for the Money Heist characters
class MoneyHeistSuperPower : public SuperPower {
public:
    // Constructor for MoneyHeistSuperPower class
    MoneyHeistSuperPower(const std::string& power);

    // Implementation of the usePower function
    void usePower() const override;

private:
    // Member variable to store the specific superpower
    std::string power;
};

// Abstract base class for superpower factories
class SuperPowerFactory {
public:
    // Pure virtual function to create a new instance of SuperPower
    virtual SuperPower* createSuperPower() const = 0;

    // Virtual destructor for proper polymorphic behavior
    virtual ~SuperPowerFactory() = default;
};

// Derived class representing a superpower factory for the Money Heist characters
class MoneyHeistSuperPowerFactory : public SuperPowerFactory {
public:
    // Constructor for MoneyHeistSuperPowerFactory class
    MoneyHeistSuperPowerFactory(const std::string& power);

    // Implementation of the createSuperPower function
    SuperPower* createSuperPower() const override;

private:
    // Member variable to store the specific superpower
    std::string power;
};

#endif