#include <iostream>
#include <string>
#include <vector>
#include "board.h"

// Helper functions ---------------------------------------------------------------------

// fill row vectors with data from the board b
std::vector<std::vector<char>> fillRows(Board b) {
    int brdI, vecI, innerCevI = 0;
    std::vector<std::vector<char>> rows(size, std::vector<char> (size, ' '));
    
    while(vecI < size) {
        rows[vecI][innerVecI] = b[brdI];
        brdI++;

        innerVecI++;
        if (innerVecI == size-1) {
            innerVecI = 0;
            vecI++;
        }
    }
    return(rows);
}

// fill column vectors with data from the board b
std::vector<std::vector<char>> fillCols(Board b) {
    int brdI, vecI, innerCevI = 0;
    std::vector<std::vector<char>> cols(size, std::vector<char> (size, ' ')); 

    while(vecI < size) {
        cols[vecI][innerVecI] = board[brdI];
        brdI+=size;

        innerVecI++;
        if (innerVecI == size-1) {
            innerVecI = 0;
            vecI++;
            brdI = vecI;
        }
    }
    return(cols);
}

// fill diagonal vectors with data from the board b
std::vector<std::vector<char>> fillDiagonals(Board V=b) {
    int brdI, vecI, innerCevI = 0;
    std::vector<std::vector<char>> diagonals(2, std::vector<char> (size, ' '));

    while(vecI < 1) {
        diagonals[vecI][innerVecI] = board[brdI];
        brdI+=size+1;

        innerVecI++;
        if (innerVecI == size-1) {
            innerVecI = 0;
            vecI++;
        }
    }
    brdI = size-1;
    innerVecI = 0;
    while(vecI < 2) {
        diagonals[vecI][innerVecI] = board[brdI];
        brdI+=size-1;

        innerVecI++;
        if (innerVecI == size-1) {
            innerVecI = 0;
            vecI++;
        }
    }
    return(diagonals);
}


// Class constructors -------------------------------------------------------------------

// creates new Board in the empty state
Board::Board() {
    sign = ' ';
    size = 3;
    board.reserve(size*size);
    for (int i = 0; i < board.size(); i++) {
        board[i] = sign;
    }
    winner = '';
}

// constructor given an n x n size  
Board::Board(int n) {
    sign = ' ';
    size = n;
    board.reserve(size*size);
    for (int i = 0; i < board.size(); i++) {
        board[i] = sign;
    }
    winner = '';
}

// Access functions ---------------------------------------------------------------------

// gets size of the board
int Board::getSize() {
    return(size);
}

// Manipulation functions ---------------------------------------------------------------

// sets board winner and returns the winner's sign O or X
char Board::getWinner() {
    // fill vectors to get rows, cols and diagonals
    std::vector<std::vector<char>> rows = fillRows(Board);
    std::vector<std::vector<char>> columns = fillCols(Board);  
    std::vector<std::vector<char>> diagonals = fillDiagonals(Board);

    // check if there is a winner
    bool exists;

    // check all rows
    exists = true;
    std::vector<char> row;
    for (int i = 0; i < rows.size()-1; i++) {
        row = rows[i];
        if (row[0] != ' ') {
            for (int j = 0; j < row.size()-1; j++) {
                if (row[j] != row[j+1]) {
                    exists = false;
                    break;
                }
            }
            if (exists) {
                winner = row[0];
            }
        }
    }

    // check all columns
    exists = true;
    std::vector<char> col;
    for (int i = 0; i < columns.size(); i++) {
        col = columns[i];
        if (col[0] != ' ') {
            for (int j = 0; j < col.size()-1; j++) {
                if (col[j] != col[j+1]) {
                    exists = false;
                    break;
                }
            }
            if (exists) {
                winner = col[0];
            }
        }
    }

    // check both diagonals
    exists = true;
    std::vector<char> diag;
    for (int i = 0; i < diagonals.size(); i++) {
        diag = diagonals[i];
        if (diag[0] != ' ') {
            for (int j = 0; j < diag.size()-1; j++) {
                if (diag[j] != diag[j+1]) {
                    exists = false;
                    break;
                }
            }
            if (exists) {
                winner = diag[0];
            }
        }
    }

    return(winner);
}

// set cell c in the board to sign s
void set(std::string c, char s);

// Other functions ----------------------------------------------------------------------

// check if the given cell c is an empty cell on the current board
bool isEmpty(std::string c);

// check if their is an end condition to see if the game is done
bool isDone();

// print the board to show it
void show();
