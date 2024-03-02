#include "../include/flip_board_utility.h"

void flipPiecesUp(Tile*** g_board, int b_size, Move* n_move) {

    int flip_row = n_move->getIrow();
    int flip_col = n_move->getIcol();
    char flip_player = n_move->getPlayer();

    if (flip_row == 0) 
        return;

    Tile* curr_tile = g_board[flip_row-1][flip_col];

    if (!curr_tile->isOccupied() || curr_tile->getPlayerOcc() == flip_player)
        return;
    
    for (int k = flip_row-2; k >= 0; k--) {
        curr_tile = g_board[k][flip_col];

        if (curr_tile->getPlayerOcc() == flip_player) 
            return;
        else if (!curr_tile->isOccupied())
            return new Move(k, check_col, curr_player);
    }


}
