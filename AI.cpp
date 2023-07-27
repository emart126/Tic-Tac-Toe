#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "board.h"
#include "AI.h"

// Class constructor -----------------------------------------------------------

AI::AI(std::string n, std::string s) {
    setName(n);
    setSign(s);
}

// Manipulation functions -------------------------------------------------------

// allow the ai to choose a cell on the board
void AI::choose(Board* b) {
    int random;
    char alphR = ((*b).cells[0])[0];
    char alphL = ((*b).cells[(*b).cells.size()-1])[0];
    char numR = ((*b).cells[0])[1];
    char numL = ((*b).cells[(*b).cells.size()-1])[1];

    bool validInput = false;
    bool continueLoop = true;
    std::string botCell;

    while (continueLoop) {
        std::cout << getName() << ", " << getSign() << ": Enter a cell ["<< alphR <<"-"<< alphL <<"]["<< numR <<"-"<< numL <<"]: ";
        random = rand() % ((*b).cells.size()) + 1; // random num from 1 to board size
        botCell = (*b).cells[random];

        for (int i = 0; i < (*b).cells.size(); i++) {
            if ((*b).isEmpty(botCell)) {
                validInput = true;
                break;
            }
        }
        if (validInput) {
            continueLoop = false;
        }
    }
    (*b).set(botCell, getSign());
}