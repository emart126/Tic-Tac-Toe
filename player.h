#include <iostream>
#include <string>
#include <vector>
#include "board.h"

#ifndef PLAYER_H
#define PLAYER_H

// player is an entity class in the game that is able to manipulatae and play on a board
class Player {
    private:
        // Player fields
        std::string name;
        std::string sign;

    public:
        // Class constructor -----------------------------------------------------------
        Player(std::string n, std::string s);

        // Access functions -------------------------------------------------------------

        // get instance of player's name
        std::string getName();

        // get instance of player's sign
        std::string getSign();

        // Manipulation functions -------------------------------------------------------

        // promt the use to choose a cell on the board, if the cell they chose is empty,
        // update the board otherwise print a message that tells the user its an invalid cell
        // and continue until it gets a valid input
        Board choose(Board b);
};

#endif