#include <fstream>
#include <iostream>

#include "../include/board.h"

using namespace std;

int main() {

    Board board = Board("input-files/01-test1.txt");
    cout << board.getCurrTurnPlayer() << endl;

    Tile tile = Tile(0, 1, '.');
    cout << tile.getIcol() << endl;

}
