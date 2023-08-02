#include <string>
#include <vector>

#ifndef BOARD_H
#define BOARD_H

// board is a list of cells that are represented by strings (" ", "O", and "X")
class Board {
    private:
        // Board fields (private)
        std::string sign;
        std::string winner;
        int size;

    public:
        // Board fields (public)
        std::vector<std::string> cells;
        std::vector<std::string> board;

        // Class constructors -----------------------------------------------------------

        // constructor
        Board();

        // constructor given an n x n size  
        Board(int n);

        // Access functions -------------------------------------------------------------

        // gets size of the board
        int getSize();

        // Manipulation functions -------------------------------------------------------

        // sets board winner and returns the winner's sign O or X
        std::string getWinner();

        // set cell c in the board to sign s
        void set(std::string c, std::string s);

        // Other functions --------------------------------------------------------------

        // check if the given cell c is an empty cell on the current board
        bool isEmpty(std::string c);

        // check if their is an end condition to see if the game is done
        bool isDone();

        // print the board to show it
        void show();
};

#endif