#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "player.h"


 // Class constructor -----------------------------------------------------------

Player::Player() {
    name = "Bob";
    sign = "+";
}

Player::Player(std::string n, std::string s) {
    // fill vars
    name = n;
    sign = s;
}

// Access functions -------------------------------------------------------------

// get instance of player's name
std::string Player::getName() {
    return(name);
}

// get instance of player's sign
std::string Player::getSign() {
    return(sign);
}

// Manipulation functions -------------------------------------------------------

// sets the player's name
void Player::setName(std::string n) {
    name = n;
}

// sets the player's sign
void Player::setSign(std::string s) {
    sign = s;
}

// allow player to choose and set a cell on board b
void Player::choose(Board* b) {
    char alphL = ((*b).cells[0])[0];
    char alphR = ((*b).cells[(*b).cells.size()-1])[0];
    char numL = ((*b).cells[0])[1];
    char numR = ((*b).cells[(*b).cells.size()-1])[1];

    bool validInput = false;
    bool continueLoop = true;
    std::string userCell;

    while (continueLoop) {
        std::cout << name << ", " << sign << ": Enter a cell ["<< alphL <<"-"<< alphR <<"]["<< numL <<"-"<< numR <<"]: ";
        std::cin >> userCell;
        userCell[0] = toupper(userCell[0]);

        // for (int i = 0; i < (*b).cells.size(); i++) {
        //     if (userCell == (*b).cells[i]) {
                if ((*b).isEmpty(userCell)) {
                    validInput = true;
        //            break;
                }
        //     }
        // }
        if (validInput) {
            continueLoop = false;
        }
        else {
            std::cout << userCell << " is not a valid space, choose again." << std::endl;
        }
    }
    (*b).set(userCell, sign);
}