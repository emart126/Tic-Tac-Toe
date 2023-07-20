#include <string>
#include <vector>

#ifndef BOARD_H
#define BOARD_H

using namespace std;

// board is a list of cells that are represented by strings (" ", "O", and "X")
class Board {
    private:
        // Board fields
        string sign;
        int size;
        vector<int> board;
        string winner;

    public:
        // gets size of the board
        int getSize();

        // sets size of the board
        void setSize();

        // sets board winner and returns the winner's sign O or X
        string getWinner();

        // set cell c in the board to sign s
        void set(string c, char s);

        // check if the given cell c is an empty cell on the current board
        bool isEmpty(string c);

        // check if their is an end condition to see if the game is done
        bool isDone();

        // print the board to show it
        void show();
};

#endif