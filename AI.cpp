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

// finds if there exists a slot in a vector that is empty while all others are sign
bool findMissingOne(std::vector<std::vector<std::string>> vec, std::string sign) {
    int empty;
    for (int i = 0; i < vec.size(); i++) {
        empty = 0;
        for (int j = 0; j < vec[i].size(); j++) {
            if (vec[i][j] == " ") {
                empty+=1;
            }
            else if (vec[i][j] != sign) {
                empty = 0;
                break;
            }
        }
        if (empty == 1) {
            return(true);
        }
    }
    return(false);
}

// get the index of the vector with the first space string in it
std::vector<int> getIndex(std::vector<std::vector<std::string>> vec) {
    int emptyI, emptyJ;
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size() j++) {
            if (vec[i][j] == " ") {
                emptyI = i;
                emptyJ = j;
            }
        }
    }
    std::vector result = {emptyI, emptyJ};
    return(result);
}

// find if there exists a cell that wins the game in this bots favor
std::string winningCell(std::vector<std::string> b, std::vector<std::string> cells, std::string sign, int size) {
    std::vector<std::vector<std::string>> rows = fillRows(b, size);
    std::vector<std::vector<std::string>> columns = fillCols(b, size);  
    std::vector<std::vector<std::string>> diagonals = fillDiagonals(b, size);

    std::vector<int> indeces;
    int Idx, Jdx;
    int vecI, innerVecI, brdI;

    if (findMissingOne(rows, sign)) {
        vecI = 0, innerVecI = 0, brdI = 0;
        indeces = getIndex(rows);
        Idx = indeces[0];
        Jdx = indeces[1];

        while(vecI < size) {
            if (vecI == Idx && innerVecI == Jdx) {
                return(cells[brdI]);
            }

            brdI++;
            innerVecI++;
            if (innerVecI == size) {
                innerVecI = 0;
                vecI++;
            }
        }
    }
    if (findMissingOne(columns, sign)) {
        vecI = 0, innerVecI = 0, brdI = 0;
        indeces = getIndex(columns);
        Idx = indeces[0];
        Jdx = indeces[1];

        while(vecI < size) {
            if (vecI == Idx && innerVecI == Jdx) {
                return(cells[brdI]);
            }

            brdI+=size;
            innerVecI++;
            if (innerVecI == size) {
                innerVecI = 0;
                vecI++;
                brdI = vecI;
            }
        }
    }
    if (findMissingOne(diagonals, sign)) {
        vecI = 0, innerVecI = 0, brdI = 0;
        indeces = getIndex(diagonals);
        Idx = indeces[0];
        Jdx = indeces[1];
        
        while(vecI < 1) {
            if (vecI == Idx && innerVecI == Jdx) {
                return(cells[brdI]);
            }

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
            if (vecI == Idx && innerVecI == Jdx) {
                return(cells[brdI]);
            }

            brdI+=size-1;
            innerVecI++;
            if (innerVecI == size) {
                innerVecI = 0;
                vecI++;
            }
        }
    }
    return("null");
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
    char alphL = ((*b).cells[0])[0];
    char alphR = ((*b).cells[(*b).cells.size()-1])[0];
    char numL = ((*b).cells[0])[1];
    char numR = ((*b).cells[(*b).cells.size()-1])[1];

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
    std::cout << getName() << ", " << getSign() << ": Enter a cell ["<< alphL <<"-"<< alphR <<"]["<< numL <<"-"<< numR <<"]: " << botCell << std::endl;
    (*b).set(botCell, getSign());
}