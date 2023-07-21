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

// check if there exists a winner by checking if there is a vector where all the elements are the same sign
void findWinner(std::vector<std::vector<char>> vectors, Board b) {
    bool exists;
    std::vector<char> vec;

    for (int i = 0; i < vectors.size()-1; i++) {
        exists = true;
        vec = vectors[i];
        if (vec[0] != ' ') {
            for (int j = 0; j < vec.size()-1; j++) {
                if (vec[j] != vec[j+1]) {
                    exists = false;
                    break;
                }
            }
            if (exists) {
                b.winner = vec[0];
            }
        }
    }
}

// Class constructors -------------------------------------------------------------------

// creates new Board in the empty state
Board::Board() {
    // fill vars
    sign = ' ';
    winner = '';
    size = 3;

    // fill board with empty spaces
    board.reserve(size*size);
    for (int i = 0; i < board.size(); i++) {
        board[i] = sign;
    }

    // create cells of board
    std::vector<std::string> gameCols = {"A","B","C"};
    for (int i = 1; i <= size; i++) {
        for (int j = 0; j < gameCols.size(); j++) {
            cells.push_back(gameCols[j]+std::to_string(i));
        }
    }
    
}

// constructor given an n x n size  
Board::Board(int n) {
    //fill vars
    sign = ' ';
    winner = '';
    size = n;

    // fill board with empty spaces
    board.reserve(size*size);
    for (int i = 0; i < board.size(); i++) {
        board[i] = sign;
    }

    // create cells of board
    std::vector<std::string> alphabet = {"A","B","C","D","E","F","G","H","I"};
    std::vector<std::string> gameCols = {alphabet.begin(), alphabet.begin()+size+1}
    for (int i = 1; i <= size; i++) {
        for (int j = 0; j < gameCols.size(); j++) {
            cells.push_back(gameCols[j]+std::to_string(i));
        }
    }
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
    findWinner(rows, board);
    findWinner(columns, board);
    findWinner(diagonals, board);
    return(winner);
}

// set cell c in the board to sign s
void Board::set(std::string c, char s) {
    
}

// Other functions ----------------------------------------------------------------------

// check if the given cell c is an empty cell on the current board
bool isEmpty(std::string c);

// check if their is an end condition to see if the game is done
bool isDone();

// print the board to show it
void show();
