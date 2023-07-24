#include <iostream>
#include <string>
#include <vector>
#include "board.h"

// Helper functions ---------------------------------------------------------------------

// fill row vectors with data from the board b
std::vector<std::vector<std::string>> fillRows(std::vector<std::string> b, int size) {
    int brdI = 0, vecI = 0, innerVecI = 0;
    std::vector<std::vector<std::string>> rows(size, std::vector<std::string> (size, " "));
    
    while(vecI < size) {
        rows[vecI][innerVecI] = b[brdI];
        brdI++;

        innerVecI++;
        if (innerVecI == size) {
            innerVecI = 0;
            vecI++;
        }
    }
    return(rows);
}

// fill column vectors with data from the board b
std::vector<std::vector<std::string>> fillCols(std::vector<std::string> b, int size) {
    int brdI = 0, vecI = 0, innerVecI = 0;
    std::vector<std::vector<std::string>> cols(size, std::vector<std::string> (size, " ")); 

    while(vecI < size) {
        cols[vecI][innerVecI] = b[brdI];
        brdI+=size;

        innerVecI++;
        if (innerVecI == size) {
            innerVecI = 0;
            vecI++;
            brdI = vecI;
        }
    }
    return(cols);
}

// fill diagonal vectors with data from the board b
std::vector<std::vector<std::string>> fillDiagonals(std::vector<std::string> b, int size) {
    int brdI = 0, vecI = 0, innerVecI = 0;
    std::vector<std::vector<std::string>> diagonals(2, std::vector<std::string> (size, " "));

    while(vecI < 1) {
        diagonals[vecI][innerVecI] = b[brdI];
        brdI+=size+1;

        innerVecI++;
        if (innerVecI == size) {
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
        if (innerVecI == size) {
            innerVecI = 0;
            vecI++;
        }
    }
    return(diagonals);
}

// check if there exists a winner by checking if there is a vector where all the elements are the same sign
std::string findWinner(std::vector<std::vector<std::string>> vectors) {
    bool exists;
    std::vector<std::string> vec;

    for (int i = 0; i < vectors.size(); i++) {
        exists = true;
        vec = vectors[i];
        if (vec[0] != " ") {
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
    return(" ");
}

// Class constructors -------------------------------------------------------------------

// creates new Board in the empty state
Board::Board() {
    // fill vars
    sign = " ";
    winner = " ";
    size = 3;

    // fill board with empty spaces
    board.resize(size*size, sign);

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
    sign = " ";
    winner = " ";
    size = n;

    // fill board with empty spaces
    board.resize(size*size, sign);

    // create cells of board
    std::vector<std::string> alphabet = {"A","B","C","D","E","F","G","H","I"};
    std::vector<std::string> gameCols = {alphabet.begin(), alphabet.begin()+size};

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
std::string Board::getWinner() {
    // fill vectors to get rows, cols and diagonals
    std::vector<std::vector<std::string>> rows = fillRows(board, size);
    std::vector<std::vector<std::string>> columns = fillCols(board, size);  
    std::vector<std::vector<std::string>> diagonals = fillDiagonals(board, size);

    // check if there is a winner
    std::string winnerSign, currSign = " ";
    currSign = findWinner(rows);
    if (currSign != " ") {
        winner = currSign;
        return(winner);
    }
    currSign = findWinner(columns);
    if (currSign != " ") {
        winner = currSign;
        return(winner);
    }
    currSign = findWinner(diagonals);
    if (currSign != " ") {
        winner = currSign;
        return(winner);
    }
    return(" ");
    
}

// set cell c in the board to sign s
void Board::set(std::string c, std::string s) {
    int index;
    for (int i = 0; i < cells.size(); i++) {
        if (cells[i] == c) {
            index = i;
            break;
        }
    }
    board[index] = s;
}

// Other functions ----------------------------------------------------------------------

// check if the given cell c is an empty cell on the current board
bool Board::isEmpty(std::string c) {
    int index;
    for (int i = 0; i < cells.size(); i++) {
        if (cells[i] == c) {
            index = i;
            break;
        }
    }
    if (board[index] == " ") {
        return(true);
    }
    else {
        return(false);
    }
}

// check if their is an end condition to see if the game is done
bool Board::isDone() {
    // fill vectors to get rows, cols and diagonals
    std::vector<std::vector<std::string>> rows = fillRows(board, size);
    std::vector<std::vector<std::string>> columns = fillCols(board, size);  
    std::vector<std::vector<std::string>> diagonals = fillDiagonals(board, size);

    // check if a winner exists and
    std::string winnerSign, currSign = " ";
    currSign = findWinner(rows);
    if (currSign != " ") {
        return(true);
    }
    currSign = findWinner(columns);
    if (currSign != " ") {
        return(true);
    }
    currSign = findWinner(diagonals);
    if (currSign != " ") {
        return(true);
    }
    return(false);
}

// print the board to show it
void Board::show() {
    std::string line = " +";
    std::string gameColumns = "";
    std::vector<std::string> alphabet = {"A","B","C","D","E","F","G","H","I"};
    std::vector<std::string> gameCols = {alphabet.begin(), alphabet.begin()+size};
    std::vector<std::vector<std::string>> rows = fillRows(board, size);

    for (int i = 1; i <= size; i++) {
        line+="---+";
    }
    for (int i = 0; i < gameCols.size(); i++) {
        gameColumns+="   "+gameCols[i];
    }

    std::cout << gameColumns << std::endl << line << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i+1 << "|";
        for (int j = 0; j < size; j++) {
            std::cout << " " << rows[i][j] << " |";
        }
        std::cout << std::endl << line << std::endl;
    }
}



// int main() {
//     Board myB = Board(5);
//     myB.show();
//     myB.set("A1", "X");
//     myB.set("A2", "O");
//     myB.set("A3", "O");
//     myB.set("B1", "O");
//     myB.set("B2", "X");
//     myB.set("B3", "X");
//     myB.set("C1", "O");
//     myB.set("C2", "X");
//     myB.show();
//     if (myB.isDone()) {
//         std::cout << "error" << std::endl;
//     }
//     else {
//         std::cout << "game isnt done" << std::endl;
//     }
//     if (myB.isEmpty("C3")) {
//         std::cout << "c3 is empty" << std::endl;
//     }
//     myB.set("C3", "X");
//     myB.set("D4", "X");
//     myB.set("E5", "X");
//     myB.show();
//     if (myB.isDone()) {
//         std::cout << "game is now done" << std::endl; 
//     }
//     std::cout << "Winner is : " << myB.getWinner() << std::endl;

//     return(0);
// }