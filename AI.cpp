#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "AI.h"

// Class constructor -----------------------------------------------------------

AI::AI(std::string n, std::string s) {
    
}

// Manipulation functions -------------------------------------------------------

// allow the ai to choose a cell on the board
void AI::choose(Board* b) {
    char alphR = ((*b).cells[0])[0];
    char alphL = ((*b).cells[(*b).cells.size()-1])[0];
    char numR = ((*b).cells[0])[1];
    char numL = ((*b).cells[(*b).cells.size()-1])[1];

    bool validInput = false;
    bool continueLoop = true;
    std::string userCell;

    while (continueLoop) {
        std::cout << name << ", " << sign << ": Enter a cell ["<< alphR <<"-"<< alphL <<"]["<< numR <<"-"<< numL <<"]: ";
        std::cin >> userCell;
        userCell[0] = toupper(userCell[0]);

        for (int i = 0; i < (*b).cells.size(); i++) {
            if (userCell == (*b).cells[i]) {
                if ((*b).isEmpty(userCell)) {
                    validInput = true;
                    break;
                }
            }
        }
        if (validInput) {
            continueLoop = false;
        }
        else {
            std::cout << userCell << " is not a valid space, choose again." << std::endl;
        }
    }
    (*b).set(userCell, sign);
}