#include <fstream>
#include <iostream>
#include <unordered_set>

#include "../include/board.h"
#include "../include/check_board_utility.h"
#include "../include/eval_board.h"

using namespace std;

int main() {

    // initialize game partitions from json 
    initializeGamePartitions();

    Board* board = new Board("input-files/01-test1.txt");
    cout << "Initial Board State: " << endl;
    cout << board->toString() << endl;

    Move* opt_move = minimaxAlphaBetaSearch(board, 1);
    
    Board* move_board = board->copyBoard();
    move_board->makeMove(opt_move);
    cout << "Move: " << opt_move->getIrow() << " " << opt_move->getIcol() << endl;
    cout << move_board->toString() << endl;
    
    
    deleteGamePartitions();
    deleteNullMove();    
    delete board;
}
