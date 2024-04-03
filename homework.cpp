#include <fstream>
#include <iostream>
#include <unordered_set>

#include "include/board.h"
#include "include/check_board_utility.h"
#include "include/eval_board.h"

using namespace std;

int main() {

    initializeGamePartitions();

    // Board* board = new Board("input.txt");
    Board* board = new Board("13-illegal-move.txt");

    int depth = 4;

    double curr_time = board->getTurnTime();
    int num_lm = (board->getAllowedMoves())->size();
 
    if (curr_time > 290)
        depth = 4;
    else if (curr_time > 200 && num_lm < 6) 
        depth = 8;
    else if (curr_time >= 200 && num_lm >= 6)
        depth = 6;
    else if (curr_time < 200 && num_lm < 6) 
        depth = 6;
    else if (curr_time < 100 && num_lm >= 6)
        depth = 4;
    else if (curr_time < 50)
        depth = 4;

    Move* opt_move = minimaxAlphaBetaSearch(board, depth);
    
    std::ofstream outFile("output.txt");
    char col_l =  opt_move->getIcol() + 97;
    outFile << col_l << opt_move->getIrow();

    Board* move_board = board->copyBoard();
    
    

    deleteGamePartitions();
    deleteNullMove();    
    delete board;
    delete opt_move;
}


// comment out and run make 
// #include "src/board.cpp"
// #include "src/check_board_utility.cpp"
// #include "src/flip_board_utility.cpp"
// #include "src/evaluate_board.cpp"
// #include "src/game_partition.cpp"
// #include "src/minimax.cpp"
// #include "src/minimax_ab.cpp"



