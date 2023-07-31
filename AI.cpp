#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "board.h"
#include "AI.h"

// Helper Functions ------------------------------------------------------------

// fill row vectors with data from the board b
std::vector<std::vector<std::string>> fillRows(std::vector<std::string> b, int size) {
    int brdI = 0, vecI = 0, innerVecI = 0;
    std::vector<std::vector<std::string>> rows(size, std::vector<std::string> (size, " "));
    
    while(vecI < size) {
        rows[vecI][innerVecI] = b[brdI];
        brdI++;

        innerVecI++;
        if (innerVecI == size) {
            innerVecI = 0;
            vecI++;
        }
    }
    return(rows);
}

// fill column vectors with data from the board b
std::vector<std::vector<std::string>> fillCols(std::vector<std::string> b, int size) {
    int brdI = 0, vecI = 0, innerVecI = 0;
    std::vector<std::vector<std::string>> cols(size, std::vector<std::string> (size, " ")); 

    while(vecI < size) {
        cols[vecI][innerVecI] = b[brdI];
        brdI+=size;

        innerVecI++;
        if (innerVecI == size) {
            innerVecI = 0;
            vecI++;
            brdI = vecI;
        }
    }
    return(cols);
}

// fill diagonal vectors with data from the board b
std::vector<std::vector<std::string>> fillDiagonals(std::vector<std::string> b, int size) {
    int brdI = 0, vecI = 0, innerVecI = 0;
    std::vector<std::vector<std::string>> diagonals(2, std::vector<std::string> (size, " "));

    while(vecI < 1) {
        diagonals[vecI][innerVecI] = b[brdI];
        brdI+=size+1;

        innerVecI++;
        if (innerVecI == size) {
            innerVecI = 0;
            vecI++;
        }
    }
    brdI = size-1;
    innerVecI = 0;
    while(vecI < 2) {
        diagonals[vecI][innerVecI] = b[brdI];
        brdI+=size-1;

        innerVecI++;
        if (innerVecI == size) {
            innerVecI = 0;
            vecI++;
        }
    }
    return(diagonals);
}


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
        random = rand() % ((*b).cells.size()); // random num from 0 to board size - 1
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
    std::cout << getName() << ", " << getSign() << ": Enter a cell ["<< alphR <<"-"<< alphL <<"]["<< numR <<"-"<< numL <<"]: " << botCell << std::endl;
    (*b).set(botCell, getSign());
}