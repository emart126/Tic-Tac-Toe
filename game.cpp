#include <iostream>
#include <string>
#include "board.h"
#include "player.h"

using namespace std;

int main() {
    Board myB = Board(4);
    Player one = Player("Bob", "x");
    Player two = Player("Alice", "o");
    cout << "p1: " << one.getName() << ", " << one.getSign() << endl;
    cout << "p2: " << two.getName() << ", " << two.getSign() << endl;
    myB.show();
    one.choose(&myB);
    myB.show();
    two.choose(&myB);
    myB.show();
    one.choose(&myB);
    myB.show();
    two.choose(&myB);
    myB.show();
    one.choose(&myB);
    myB.show();
    two.choose(&myB);
    myB.show();
    cout << "winner: " << myB.getWinner() << endl;

    return(0);
}