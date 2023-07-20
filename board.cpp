#include <iostream>
#include <string>
#include <vector>
#include "board.h"

// Class constructors -------------------------------------------------------------------

// creates new Board in the empty state
Board::Board() {
    sign = " ";
    size = 3;
    board.reserve(size*size);
    for (int i = 0; i < board.size(); i++) {
        board[i] = sign;
    }
    winner = "";
}

// constructor given an n x n size  
Board::Board(int n) {
    sign = " ";
    size = n;
    board.reserve(size*size);
    for (int i = 0; i < board.size(); i++) {
        board[i] = sign;
    }
    winner = "";
}

// Access functions ---------------------------------------------------------------------

// gets size of the board
int Board::getSize() {
    return(size);
}

// Manipulation functions ---------------------------------------------------------------

// sets size of the board
void setSize();

// sets board winner and returns the winner's sign O or X
std::string getWinner();

// set cell c in the board to sign s
void set(std::string c, char s);

// check if the given cell c is an empty cell on the current board
bool isEmpty(std::string c);

// check if their is an end condition to see if the game is done
bool isDone();

// print the board to show it
void show();



// temp tests
int main() {
    Board myB = Board(10);
    std::cout << myB.getSize() << std::endl;
    return(0);
}
