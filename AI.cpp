#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "board.h"
#include "AI.h"

// Helper Functions ------------------------------------------------------------

// return row vectors with data from the board b
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

// return column vectors with data from the board b
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

// return diagonal vectors with data from the board b
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

// ------------------

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

// find if there exists a cell that wins the game in this bots favor and return that cell
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

// find if there exists a cell that stops the opponent from winning and return that cell
std::string stopOpponent(std::vector<std::string> b, std::vector<std::string> cells, std::string oppSign, int size) {
    std::string oppWinningCell = winningCell(b, cells, oppSign, size);
    if (oppWinningCell != "null") {
        return(oppWinningCell);
    }
    return("null");
}

// ------------------

// return a list of indices of the vectors with a possible win state, otherwise return empty list 
std::vector<int> arePossibleLines(std::vector<std::vector<std::string>> vec, std::string sign) {
    std::vector<int> possibleLines = {};
    bool currLine;
    for (int i = 0; i < vec.size(); i++) {
        currLine = true;
        for (int j = 0; j < vec[i].size(); j++) {
            if (vec[i][j] != sign || vec[i][j] != " ") {
                currLine = false;
            }
        }
        if (currLine) {
            possibleLines.push_back(i);
        }
    }
    return(possibleLines);
}

// return the amount of signs in this line
int signCount(std::vector<std::string> vec, std::string sign) {
    int count = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == sign) {
            count+=1;
        }
    }
    return(count);
}

// return longest possible winning line given vec and indeces of possible winning lines
std::vector<std::string> longestVec(std::vector<std::vector<std::string>> vec, std::string sign, int* iMax) {
    int currCount;
    int indexOfMax = -1;
    int maxCount = -1;
    std::vector<int> lineIndeces;
    std::vector<std::string> longestPossibleVec = {};

    // get possible lines within vecs by index
    lineIndeces = arePossibleLines(vec, sign);
    if (lineIndeces.size() == 0) {
        std::cout << "got no possible lines within vecs by index" << std::endl;
        *iMax = -1;
        return(longestPossibleVec);
    }
    
    // check the amount of signs there are in each possible line
    for (int i = 0; i < lineIndeces.size(); i++) {
        currCount = signCount(vec[lineIndeces[i]], sign);
        if (currCount > maxCount) {
            maxCount = currCount;
            indexOfMax = lineIndeces[i];
        }
    }

    // get the line with the largest amount 
    if (indexOfMax != -1) {
        longestPossibleVec = vec[indexOfMax];
        *iMax = indexOfMax; 
    }
    else {
        longestPossibleVec = vec[lineIndeces[0]];
        *iMax = 0;
    }
    return(longestPossibleVec);
}

// convert index and line to list of all indeces within the line of the real board
std::vector<int> getIndecesOfLine(int i, std::vector<std::vector<std::string>> vec, std::string line, int size) {
    std::vector<int> result;
    int startingIndex;
    if (line == "row") {
        startingIndex = i*size;
        for (int k = startingIndex; k < size; k++) {
            result.push_back(k);
        }
    }
    else if (line == "column") {
        startingIndex = i;
        for (int k = startingIndex; k < size*size; k+=size) {
            result.push_back(k);
        }
    }
    else if (line == "diagonal") {
        if (i == 0) {
            startingIndex = 0;
            for (int k = startingIndex; k < size*size; k+=size+1) {
                result.push_back(k);
            }
        }
        else if (i == 1) {
            startingIndex = size-1;
            for (int k = startingIndex; k < size*size; k+=size-1) {
                result.push_back(k);
            }
        }
    }
    return(result);
}

// find if there exists a longest line that can be added to that will later win the game and return a cell within this line
std::string continueLine(std::vector<std::string> b, std::vector<std::string> cells, std::string sign, int size) {
    std::vector<std::vector<std::string>> rows = getRows(b, size);
    std::vector<std::vector<std::string>> columns = getCols(b, size);  
    std::vector<std::vector<std::string>> diagonals = getDiagonals(b, size);

    int indexLongRow = -1;
    int indexLongCol = -1;
    int indexLongDiag = -1;
    std::string l;

    std::vector<std::string> longestPossibleRow = longestVec(rows, sign, &indexLongRow);
    std::vector<std::string> longestPossibleCol = longestVec(columns, sign, &indexLongCol);
    std::vector<std::string> longestPossibleDiag = longestVec(diagonals, sign, &indexLongDiag);

    // no possible winning lines
    if (longestPossibleRow.size() == 0 && longestPossibleCol.size() == 0 && longestPossibleDiag.size() == 0) {
        std::cout << "no possible winning line at the moment" << std::endl;
        return("null");
    }

    int indexOfLongest = -1;
    std::vector<std::vector<std::string>> LongestRowColDiag = {longestPossibleRow, longestPossibleCol, longestPossibleDiag};
    std::vector<std::string> longestPossibleLine = longestVec(LongestRowColDiag, sign, &indexOfLongest);

    std::vector<std::vector<std::string>> whichDirectedLine;
    if (indexOfLongest == 0) {
        indexOfLongest = indexLongRow;
        whichDirectedLine = rows;
        l = "row";
    }
    else if (indexOfLongest == 1) {
        indexOfLongest = indexLongCol;
        whichDirectedLine = columns;
        l = "column";
    }
    else if (indexOfLongest == 2) {
        indexOfLongest = indexLongDiag;
        whichDirectedLine = diagonals;
        l = "diagonal";
    }
    
    std::vector<int> resultingLine = getIndecesOfLine(indexOfLongest, whichDirectedLine, l, size);
    // printing resulting line
    std::cout << "Print line:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << resultingLine[i] << " ";
    }
    std::cout << std::endl;

    // get random index from resultingList and convert to string cell

    // work in progress
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
    if (needCell && oppSign != "null") {
        checkCell = stopOpponent((*b).board, (*b).cells, oppSign, rowSize);
        if (checkCell != "null") {
            botCell = checkCell;
            needCell = false;
        }
    }

    // attempt to make a line (choose a cell on the longest line on the current board thats possible to win with)
    checkCell = continueLine((*b).board, (*b).cells, getSign(), rowSize);
    if (needCell && checkCell != "null") {
        botCell = checkCell;
        needCell = false;
    }

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