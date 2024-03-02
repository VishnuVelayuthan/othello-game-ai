#include <fstream>
#include <iostream>
#include <unordered_set>

#include "../include/board.h"
#include "../include/check_board_utility.h"

using namespace std;

int main() {

    Board board = Board("input-files/01-test1.txt");
    cout << board.getCurrTurnPlayer() << endl;

    Board* move_board = board.copyBoard();
    unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves = board.getAllowedMoves();
    
    int i = 0;
    for (Move* move : *allowed_moves) {
        if (i != 5) {
            i++;
            continue;
        }
        move_board->makeMove(move);
        cout << move->getIrow() << " " << move->getIcol() << endl;
        break;
    }

    cout << move_board->toString() << endl;
    // Null Move object in Check Board
    deleteNullMove();    
}
