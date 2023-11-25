#include "SuperPower.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

// Implementation of MoneyHeistSuperPower class
// Constructor for MoneyHeistSuperPower class
MoneyHeistSuperPower::MoneyHeistSuperPower(const std::string& power) : power(power) {}

// Function to use the superpower
void MoneyHeistSuperPower::usePower() const {
    std::cout << power << "!" << std::endl;
}

// Implementation of MoneyHeistSuperPowerFactory class
// Constructor for MoneyHeistSuperPowerFactory class
MoneyHeistSuperPowerFactory::MoneyHeistSuperPowerFactory(const std::string& power) : power(power) {}

// Function to create a new instance of MoneyHeistSuperPower
SuperPower* MoneyHeistSuperPowerFactory::createSuperPower() const {
    return new MoneyHeistSuperPower(power);
}