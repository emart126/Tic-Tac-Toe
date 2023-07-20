#include <string>
#include <vector>

#ifndef BOARD_H
#define BOARD_H

// board is a list of cells that are represented by strings (" ", "O", and "X")
class Board {
    private:
        // Board fields
        std::string sign;
        int size;
        std::vector<std::string> board;
        std::string winner;

    public:
        // Class constructors -----------------------------------------------------------

        // constructor
        Board();

        // constructor given an n x n size  
        Board(int n);

        // Access functions -------------------------------------------------------------

        // gets size of the board
        int getSize();

        // Manipulation functions -------------------------------------------------------

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
};

#endif