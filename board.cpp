#include <string>
#include <vector>
#include "board.h"

// Board Constructor
Board::Board() {
    sign = " ";
    size = 3;
    board = {};
    winner = "";
}

// gets size of the board
int getSize();

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
