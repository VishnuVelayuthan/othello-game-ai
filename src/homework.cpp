#include <fstream>
#include <iostream>
#include <unordered_set>

#include "../include/board.h"
#include "../include/check_board_utility.h"
#include "../include/eval_board.h"

using namespace std;

int main() {

    Board* board = new Board("input-files/08-debug-end.txt");
    cout << "Initial Board State: " << endl;
    cout << board->toString() << endl;

    // Move* opt_move = minimaxAlphaBetaSearch(board, 1);
    
    // move_board->makeMove(opt_move);
    // cout << "Move: " << opt_move->getIrow() << " " << opt_move->getIcol() << endl;
    // cout << move_board->toString() << endl;
    

    
    

    // Board* move_board = board.copyBoard();
    // unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves = board.getAllowedMoves();
    // 
    // int i = 0;
    // for (Move* move : *allowed_moves) {
    //     if (i != 0) {
    //         i++;
    //         continue;
    //     }
    //     move_board->makeMove(move);
    //     cout << "Move: " << move->getIrow() << " " << move->getIcol() << endl;
    //     break;
    // }
    
    // Null Move object in Check Board
    deleteNullMove();    
    delete board;
}
