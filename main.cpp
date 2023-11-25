#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Character.h"
#include "SuperPower.h"

// Function to simulate a fight between the character and guards
void fight(std::string chN, double winProb, int i1, int i2);

// Enumeration for different move options
enum Move { ATTACK = 1, DEFEND = 2, SPECIAL_MOVE = 3 };
const int MAX_MOVES = 3;
const int MAX_SPECIAL_MOVES = 1;


// Function to display characters
void displayCharacterOptions() {
    std::cout << "Choose your character:" << std::endl;
    std::cout << "a) Characters from the show 'Money Heist':" << std::endl;
    std::cout << "1. Tokyo" << std::endl;
    std::cout << "2. The Professor" << std::endl;
    std::cout << "3. Berlin" << std::endl;
    std::cout << "4. Nairobi" << std::endl;
    std::cout << "5. Denver" << std::endl;
    std::cout << "6. Rio" << std::endl;
    std::cout << "7. Helsinki" << std::endl;
    std::cout << "8. Oslo" << std::endl;
}

// Function to display superpowers
void displaySuperPowerOptions() {
    std::cout << "Choose a superpower:" << std::endl;
    std::cout << "1. Super Strength" << std::endl;
    std::cout << "2. Speed" << std::endl;
    std::cout << "3. Fly" << std::endl;
    std::cout << "4. Heat Vision" << std::endl;
    std::cout << "5. Invisibility" << std::endl;
    std::cout << "6. Sonic Scream" << std::endl;
    std::cout << "7. Water Manipulation" << std::endl;
    std::cout << "8. Fire Manipulation" << std::endl;
    std::cout << "9. Air Manipulation" << std::endl;
    std::cout << "10. Electricity" << std::endl;
}

// Function to display banks
void displayBankOptions() {
    std::cout << "Choose a bank to rob:" << std::endl;
    std::cout << "1. Royal Mint of Spain" << std::endl;
    std::cout << "2. Bank of Spain" << std::endl;
}

// Function to validate user input for menu choices
int getValidChoice(int lowerBound, int upperBound) {
    int choice;
    do {
        std::cout << "Enter your choice (" << lowerBound << "-" << upperBound << "): ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }
    } while (choice < lowerBound || choice > upperBound);

    return choice;
}

// Function to validate the bank choice
int getValidBankChoice() {
    int choice;
    do {
        choice = getValidChoice(1, 2);
        if (choice < 1 || choice > 2) {
            std::cout << "Invalid bank choice. Please choose 1 or 2." << std::endl;
        }
    } while (choice < 1 || choice > 2);

    return choice;
}

// Function to handle the bank robbery
void robBank(CharacterFactory* characterFactory, SuperPowerFactory* superPowerFactory) {
    // Create character, superpower, and bank based on user choice or random
    Character* selectedCharacter = characterFactory->createCharacter();
    SuperPower* selectedSuperPower = superPowerFactory->createSuperPower();

    // Display selected character, superpower, and bank
    selectedCharacter->displayInfo();
    selectedSuperPower->usePower();

    std::cout << "Robbing the bank. Choose:\n1. Royal Mint of Spain\n2. Bank of Spain\n";
    int bankChoice = getValidBankChoice();
    if (bankChoice == 1) {
        std::cout << "Royal Mint of Spain!" << std::endl;
    } else if (bankChoice == 2) {
        std::cout << "Bank of Spain!" << std::endl;
    }

    // Simulate the fight
    int characterLives = 3;
    int guardLives = 3;
    selectedCharacter->displayInfo();
    selectedCharacter->getName();
    //simulateFight(selectedCharacter, characterLives, guardLives);

    fight(selectedCharacter->getName(), selectedCharacter->getWinProb(),characterLives, guardLives);


    delete selectedCharacter;
    delete selectedSuperPower;
}

void fight(std::string characterName,double winProb, int characterLives, int guardLives) {
    std::string moves[] = {"Attack", "Defend", "Special Move"};
    bool canUseSpecialMove = true;
    int userMove;
    while (characterLives > 0 && guardLives > 0) {
        std::cout << "Choose your move:\n";
        if (!canUseSpecialMove) {
            for (int i = 0; i < MAX_MOVES-1; ++i) {
                std::cout << i + 1 << ". " << moves[i] << std::endl;
            }
        }else {
            for (int i = 0; i < MAX_MOVES; ++i) {
                std::cout << i + 1 << ". " << moves[i] << std::endl;
            }
        }

        std::cin >> userMove;
        // Validate user input
        if (userMove < 1 || userMove > MAX_MOVES) {
            std::cout << "Invalid move. Please select a valid move." << std::endl;
            continue;
        }

        // Check if special move is not available
        if (userMove == SPECIAL_MOVE && !canUseSpecialMove) {
            std::cout << "You ran out of energy and cannot use more special moves. Please select only 1 and 2 options." << std::endl;
            continue;
        }

        // Update special move availability
        if (userMove == SPECIAL_MOVE) {
            canUseSpecialMove = false;
        }

        // The fight logic based on win probability
        // Loss PROB is a random number between 0 and 1
        double lossProb = static_cast<double>(rand()) / RAND_MAX; // Random number between 0 and 1

        // if attacking more chances of losing since you are letting your guard down
        if (userMove == 1) {
            lossProb+=0.05;
        // if you are defending, you have more chances of winning
        }else if (userMove == 2) {
            lossProb-=0.09;
        //special move increases your winning probability greatly. But can only use it 1 time.
        }else  if (userMove == 3) {
            lossProb-=0.20;
        }

        std::cout << "Win PROB is " << winProb<< std::endl;
        std::cout << "Loss PROB is " << lossProb << std::endl;

        if (lossProb <= winProb) {
            std::cout << characterName<< " defeated a guard!" << std::endl;
            --guardLives;
        } else {
            std::cout << "Guard defeated " << characterName << "! " << characterName << " failed to defeat the guard." << std::endl;
            --characterLives;
        }
    }


    if (characterLives > 0) {
        std::cout << "Congratulations! The character " + characterName +  " successfully robbed the bank!" << std::endl;
    } else if(guardLives > characterLives) {
        std::cout << "Guard defeated " + characterName + "!!. Oh no.";
    }
    else {
        std::cout << "The guards successfully defended the bank. The " + characterName + " was defeated." << std::endl;
    }

}

// Recursive function to allow the user to continue robbing banks
void robBanksRecursively(CharacterFactory* characterFactory, SuperPowerFactory* superPowerFactory) {
    robBank(characterFactory, superPowerFactory);

    // Ask if the user wants to rob another bank
    std::cout << "Do you want to rob another bank? (1 for Yes, 0 for No): ";
    int continueRobbing;
    std::cin >> continueRobbing;

    if (continueRobbing == 1) {
        robBanksRecursively(characterFactory, superPowerFactory);
    } else {
        std::cout << "Exiting the bank robbery sequence." << std::endl;
    }
}

int main() {
    // For randomization
    std::srand(std::time(0));

    // Display character, superpower, and bank options
    displayCharacterOptions();
    int characterChoice = getValidChoice(1, 8);

    displaySuperPowerOptions();
    int superPowerChoice = getValidChoice(1, 10);

    // Create character and superpower factories based on user choice or random
    CharacterFactory *characterFactory = nullptr;
    SuperPowerFactory *superPowerFactory = nullptr;

    // Assign factories based on character choice
    if (characterChoice == 1) {
        characterFactory = new MoneyHeistCharacterFactory("Tokyo",0.6);
    } else if (characterChoice == 2) {
        characterFactory = new MoneyHeistCharacterFactory("The Professor",0.4);
    } else if (characterChoice==3) {
        characterFactory = new MoneyHeistCharacterFactory("Berlin", 0.3);
    } else if (characterChoice==4) {
        characterFactory = new MoneyHeistCharacterFactory("Nairobi", 0.5);
        characterFactory = new MoneyHeistCharacterFactory("Nairobi", 0.5);
    } else if (characterChoice==5) {
        characterFactory = new MoneyHeistCharacterFactory("Denver", 0.1);
    } else if (characterChoice==6) {
        characterFactory = new MoneyHeistCharacterFactory("Rio", 0.7);
    } else if (characterChoice==7) {
        characterFactory = new MoneyHeistCharacterFactory("Helsinki", 0.2);
    } else if (characterChoice==8) {
        characterFactory = new MoneyHeistCharacterFactory("Oslo", 0.8);
    }else {
        std::cout<<"Invalid character choice. The character choice should be between 1 to 8."<<std::endl;
    }

    // Assign factories based on superpower choice
    if (superPowerChoice == 1) {
        superPowerFactory = new MoneyHeistSuperPowerFactory("Super Strength");
    } else if (superPowerChoice == 2) {
        superPowerFactory = new MoneyHeistSuperPowerFactory("Speed");
    } else if (superPowerChoice == 3) {
        superPowerFactory = new MoneyHeistSuperPowerFactory("Fly");
    } else if (superPowerChoice == 4) {
        superPowerFactory = new MoneyHeistSuperPowerFactory("Heat Vision");
    } else if (superPowerChoice == 5) {
        superPowerFactory = new MoneyHeistSuperPowerFactory("Invisibility");
    } else if (superPowerChoice == 6) {
        superPowerFactory = new MoneyHeistSuperPowerFactory("Sonic Scream");
    } else if (superPowerChoice == 7) {
        superPowerFactory = new MoneyHeistSuperPowerFactory("Water Manipulation");
    } else if (superPowerChoice == 8) {
        superPowerFactory = new MoneyHeistSuperPowerFactory("Fire Manipulation");
    } else if (superPowerChoice == 9) {
        superPowerFactory = new MoneyHeistSuperPowerFactory("Air Manipulation");
    } else if (superPowerChoice == 10) {
        superPowerFactory = new MoneyHeistSuperPowerFactory("Electricity");
    } else {
        std::cout<<"Invalid Super power choice. The character choice should be between 1 to 10."<<std::endl;
    }

    // Start the bank robbing sequence
    robBanksRecursively(characterFactory, superPowerFactory);

    delete characterFactory;
    delete superPowerFactory;

    return 0;
}