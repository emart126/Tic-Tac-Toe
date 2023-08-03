#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "board.h"
#include "AI.h"

// Helper Functions ------------------------------------------------------------

// get row vectors with data from the board b
std::vector<std::vector<std::string>> getRows(std::vector<std::string> b, int size) {
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

// get column vectors with data from the board b
std::vector<std::vector<std::string>> getCols(std::vector<std::string> b, int size) {
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

// get diagonal vectors with data from the board b
std::vector<std::vector<std::string>> getDiagonals(std::vector<std::string> b, int size) {
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
bool findMissingOne(std::vector<std::vector<std::string>> vec, std::string sign, int* I, int* J) {
    int empty;
    for (int i = 0; i < vec.size(); i++) {
        empty = 0;
        for (int j = 0; j < vec[i].size(); j++) {
            if (vec[i][j] == " ") {
                empty+=1;
                *I = i;
                *J = j;
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

// find if there exists a cell that wins the game in this bots favor
std::string winningCell(std::vector<std::string> b, std::vector<std::string> cells, std::string sign, int size) {
    std::vector<std::vector<std::string>> rows = getRows(b, size);
    std::vector<std::vector<std::string>> columns = getCols(b, size);  
    std::vector<std::vector<std::string>> diagonals = getDiagonals(b, size);

    std::vector<int> indeces;
    int Idx, Jdx;
    int vecI, innerVecI, brdI;

    if (findMissingOne(rows, sign, &Idx, &Jdx)) {
        vecI = 0, innerVecI = 0, brdI = 0;

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
    if (findMissingOne(columns, sign, &Idx, &Jdx)) {
        vecI = 0, innerVecI = 0, brdI = 0;

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
    if (findMissingOne(diagonals, sign, &Idx, &Jdx)) {
        vecI = 0, innerVecI = 0, brdI = 0;
        
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

// find if there exists a cell that stops the opponent from winning
std::string stopOpponent(std::vector<std::string> b, std::vector<std::string> cells, std::string oppSign, int size) {
    std::string oppWinningCell = winningCell(b, cells, oppSign, size);
    if (oppWinningCell != "null") {
        return(oppWinningCell);
    }
    return("null");
}


// Class constructor -----------------------------------------------------------

AI::AI(std::string n, std::string s) {
    setName(n);
    setSign(s);
}

// Access functions ------------------------------------------------------------

// get sign of oppenent
std::string AI::getOppSign(Board* b) {
    std::string mySign = getSign();
    for (int i = 0; i < (*b).board.size(); i++) {
        if ((*b).board[i] != mySign && (*b).board[i] != " ") {
            return((*b).board[i]);
        }
    }
    return("null");
}

// Manipulation functions ------------------------------------------------------

// allow the ai to choose a cell on the board
void AI::choose(Board* b) {
    int random;
    char alphL = ((*b).cells[0])[0];
    char alphR = ((*b).cells[(*b).cells.size()-1])[0];
    char numL = ((*b).cells[0])[1];
    char numR = ((*b).cells[(*b).cells.size()-1])[1];
    int rowSize = numR - '0';

    bool needCell = true;
    std::string oppSign;
    std::string botCell;
    std::string checkCell;

    // find cell to win game
    checkCell = winningCell((*b).board, (*b).cells, getSign(), rowSize);
    if (needCell && checkCell != "null") {
        botCell = checkCell;
        needCell = false;
    }

    // find cell to stop opponent from winning
    oppSign = getOppSign(b);
    if (oppSign != "null") {
        checkCell = stopOpponent((*b).board, (*b).cells, oppSign, rowSize);
        if (needCell && checkCell != "null") {
            botCell = checkCell;
            needCell = false;
        }
    }

    // attempt to make a line (choose longest line on current board thats possible to win)

    // choose random cell
    while (needCell) {
        random = rand() % ((*b).cells.size()); // random num from 0 to board size - 1
        botCell = (*b).cells[random];
        if ((*b).isEmpty(botCell)) {
            break;
        }
    }
    std::cout << getName() << ", " << getSign() << ": Enter a cell ["<< alphL <<"-"<< alphR <<"]["<< numL <<"-"<< numR <<"]: " << botCell << std::endl;
    (*b).set(botCell, getSign());
}