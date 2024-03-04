#include "../include/eval_board.h"

double evaluateBoard(Board* e_board, char opt_player) {
    return opt_player == 'X' ? 
        e_board->getNumXTiles() :
        e_board->getNumOTiles();
}
