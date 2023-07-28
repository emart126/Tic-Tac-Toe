// ------------------------------
// Tic-Tac-Toe Program: 7/28/2023
// ------------------------------

#include <iostream>
#include <string>
#include "board.h"
#include "player.h"
#include "AI.h"

using namespace std;

int main() {
    int boardSize = 0;
    std::string name1;
    std::string winnerSign;
    std::string again;
    bool p1Turn = true;

    // user chooses their name
    cout << "Welcome to TIC-Tac-Toe Game!" << endl;
    cout << "Please enter a name: ";
    std::cin >> name1;
    Player player1 = Player(name1, "X");
    AI player2 = AI("Bob", "O");

    // user chooses size of board
    while (true) {
        cout << "Choose an n x n board size [3-9]: ";
        std::cin >> boardSize;
        if (boardSize < 3 || boardSize > 9) {
            cout << "Invalid choice" << endl;
        }
        else {
            break;
        }
    }
    
    // begin the game
    while (true) {
        // take turns until board has a done condtion
        Board B = Board(boardSize);
        while (true) {
            B.show();
            if (p1Turn) {
                player1.choose(&B);
                p1Turn = false;
            }
            else {
                player2.choose(&B);
                p1Turn = true;
            }

            if (B.isDone()) {
                break;
            }
        }
        B.show();

        // find whoeis the winner based on boards state
        winnerSign = B.getWinner();
        if (winnerSign == player1.getSign()) {
            cout << player1.getName() << " is the winner!" << endl;
        }
        else if (winnerSign == player2.getSign()) {
            cout << player2.getName() << " is the winner!" << endl;
        }
        else {
            cout << "It is a tie!" << endl;
        }

        // ask if user wants to play again
        cout << "Would you like to play again? [Y/N]" << endl;
        std::cin >> again;
        again[0] = toupper(again[0]);
        if (again != "Y") {
            break;
        }
    }

    return(0);
}