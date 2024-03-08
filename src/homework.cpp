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

    Board* board = new Board("input-files/11-v.txt");
    cout << "Initial Board State: " << endl;
    cout << board->toString() << endl;

    Move* opt_move = minimaxAlphaBetaSearch(board, 4);

    // for (FlipType f : opt_move->getFlipTypes())
    //     cout << "FlipType: " <<  << endl;

    cout << (opt_move->getFlipTypes()).size() << endl;
    
    Board* move_board = board->copyBoard();
    move_board->makeMove(opt_move);
    cout << "Move: " << opt_move->getIrow() << " " << opt_move->getIcol() << endl;
    cout << move_board->toString() << endl;
    cout << move_board->allowedMovesToString()<< endl;
    
    
    deleteGamePartitions();
    deleteNullMove();    
    delete board;
}
