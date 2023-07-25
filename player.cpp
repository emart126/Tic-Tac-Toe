#include <string>
#include <vector>
#include "board.h"


 // Class constructor -----------------------------------------------------------

Player::Player(std::string n, std::string s) {
    // fill vars
    name = n;
    sign = s;
}

// Access functions -------------------------------------------------------------

// get instance of player's name
std::string Board::getName() {
    return(name);
}

// get instance of player's sign
std::string Board::getSign() {
    return(sign);
}

// Manipulation functions -------------------------------------------------------

// allow player to choose and set a cell on board b
void Board::choose(Board b) {
    std::string alphR = (b.cells[0])[0];
    std::string alphL = (b.cells[b.cells.size()-1])[0];
    std::string numR = (b.cells[0])[1];
    std::string numL = (b.cells[b.cells.size()-1])[1];

    bool validInput = false;
    bool continueLoop = true;
    std::string userCell;

    while (continueLoop) {
        std::cout << name << ", " << sign << ": Enter a cell ["<< alphR <<"-"<< alphL <<"]["<< numR <<"-"<< numL <<"]: " << endl;
        cin >> userCell;
        userCell[0] = toupper(userCell[0]);
    }
}
