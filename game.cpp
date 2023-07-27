#include <iostream>
#include <string>
#include "board.h"
#include "player.h"

using namespace std;

int main() {
    std::string name;
    std::string winnerSign;
    std::string again;
    bool p1Turn = true;

    cout << "Welcome to TIC-Tac-Toe Game!" << endl;
    cout << "Please enter a name to start: ";
    cin >> name;
    Player player1 = Player(name, "X");
    Player player2 = Player("Bob", "O");
    
    while (true) {
        Board B = Board();
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

        winnerSign = B.getWinner();
        if (winnerSign == player1.getSign()) {
            cout << player1.getName() << "is the winner!" << endl;
        }
        else if (winnerSign == player2.getSign()) {
            cout << player2.getName() << "is the winner!" << endl;
        }
        else {
            cout << "It is a tie!" << endl;
        }

        cout << "Would you like to play again? [Y/N]" << endl;
        cin >> again;
        again[0] = toupper(again[0]);
        if (again != "Y") {
            break;
        }
    }

    return(0);
}