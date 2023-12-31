#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "player.h"

#ifndef AI_H
#define AI_H

// AI is an entity class in the game that is able to manipulatae and play on a board
class AI : public Player {
    public:
        // Class constructor ------------------------------------------------------------
        AI(std::string n, std::string s);

        // Access functions -------------------------------------------------------------

        // get sign of oppenent
        std::string getOppSign(Board* b);

        // Manipulation functions -------------------------------------------------------

        // allow the ai to choose a cell on the board
        void choose(Board* b);
};

#endif