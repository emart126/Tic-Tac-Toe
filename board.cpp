#include <iostream>
#include <string>
#include <vector>
#include "board.h"

// Helper functions ---------------------------------------------------------------------

// fill row vectors with data from the board b
std::vector<std::vector<char>> fillRows(std::vector<char> b, int size) {
    int brdI, vecI, innerVecI = 0;
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
std::vector<std::vector<char>> fillCols(std::vector<char> b, int size) {
    int brdI, vecI, innerVecI = 0;
    std::vector<std::vector<char>> cols(size, std::vector<char> (size, ' ')); 

    while(vecI < size) {
        cols[vecI][innerVecI] = b[brdI];
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
std::vector<std::vector<char>> fillDiagonals(std::vector<char> b, int size) {
    int brdI, vecI, innerVecI = 0;
    std::vector<std::vector<char>> diagonals(2, std::vector<char> (size, ' '));

    while(vecI < 1) {
        diagonals[vecI][innerVecI] = b[brdI];
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
        diagonals[vecI][innerVecI] = b[brdI];
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
char findWinner(std::vector<std::vector<char>> vectors) {
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
                return(vec[0]);
            }
        }
    }
    return(' ');
}

// convert char to string
std::string charToStr(char x) {
    std::string s(1, x);
    return(s);
}

// Class constructors -------------------------------------------------------------------

// creates new Board in the empty state
Board::Board() {
    // fill vars
    sign = ' ';
    winner = ' ';
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
    winner = ' ';
    size = n;

    // fill board with empty spaces
    board.reserve(size*size);
    for (int i = 0; i < board.size(); i++) {
        board[i] = sign;
    }

    // create cells of board
    std::vector<std::string> alphabet = {"A","B","C","D","E","F","G","H","I"};
    std::vector<std::string> gameCols = {alphabet.begin(), alphabet.begin()+size};

    // std::cout << "s: " << gameCols.size() << std::endl;
    // for (int i = 0; i < gameCols.size(); i++) {
    //     std::cout << gameCols[i] << " ";
    // }
    // std::cout << std::endl;

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
    std::vector<std::vector<char>> rows = fillRows(board, size);
    std::vector<std::vector<char>> columns = fillCols(board, size);  
    std::vector<std::vector<char>> diagonals = fillDiagonals(board, size);

    // check if there is a winner
    char winnerSign, currSign = ' ';
    currSign = findWinner(rows);
    if (currSign != ' ') {
        winner = currSign;
        return(winner);
    }
    currSign = findWinner(columns);
    if (currSign != ' ') {
        winner = currSign;
        return(winner);
    }
    currSign = findWinner(diagonals);
    if (currSign != ' ') {
        winner = currSign;
        return(winner);
    }
    return(' ');
    
}

// set cell c in the board to sign s
void Board::set(std::string c, char s) {
    int index;
    for (int i = 0; i < cells.size(); i++) {
        if (cells[i] == c) {
            index = i;
            std::cout << "setting " << i << std::endl;
            break;
        }
    }
    board[index] = s;
}

// Other functions ----------------------------------------------------------------------

// check if the given cell c is an empty cell on the current board
bool isEmpty(std::string c);

// check if their is an end condition to see if the game is done
bool isDone();

// print the board to show it
void Board::show() {
    for (int i = 0; i < size; i++) {
        std::cout << board[i] << " ";
    }
    std::cout << std::endl;

    std::string line = " +";
    std::string gameColumns = "";
    std::vector<std::string> alphabet = {"A","B","C","D","E","F","G","H","I"};
    std::vector<std::string> gameCols = {alphabet.begin(), alphabet.begin()+size};
    std::vector<std::vector<char>> rows = fillRows(board, size);

    for (int i = 1; i <= size; i++) {
        line+="---+";
    }
    for (int i = 0; i < gameCols.size(); i++) {
        gameColumns+="   "+gameCols[i];
    }

    std::cout << gameColumns << std::endl << line << std::endl;
    std::string currRow;
    for (int i = 0; i < size; i++) {
        currRow = std::to_string(i+1)+"|";
        for (int j = 0; j < size; j++) {
            currRow+=(" " + charToStr(rows[i][j]) + " |");
        }
        std::cout << currRow << std::endl << line << std::endl;
    }
}



int main() {
    Board myB = Board();
    myB.show();
    myB.set("A1", 'X');
    myB.set("B1", 'X');
    myB.set("C1", 'X');
    myB.show();
    std::cout << myB.getWinner() << std::endl;

    return(0);
}