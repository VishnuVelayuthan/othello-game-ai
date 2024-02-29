
#include "../include/move.h"
#include "../include/board.h";

Move checkBoardUp(Tile*** g_board, Tile* check_tile, char curr_player) {

    int check_row = check_tile->getIrow();
    int check_col = check_tile->getIcol();
    
    Tile* curr_tile;
    for (int k = check_row-1; k >= 0; k--) {
        curr_tile = g_board[k][check_col];

        if (curr_tile->getPlayerOcc() == curr_player) 
            return Move(-1,-1,'.');
        else if (!curr_tile->isOccupied())
            return Move(k, check_col, curr_player);
    }
}

Move checkBoardDown(Tile*** g_board, int b_size, Tile* check_tile, char curr_player) {

    int check_row = check_tile->getIrow();
    int check_col = check_tile->getIcol();

    Tile* curr_tile;
    for (int k = check_row+1; k < b_size; k++) {
        curr_tile = g_board[k][check_col];

        if (curr_tile->getPlayerOcc() == curr_player) 
            return Move(-1,-1,'.');
        else if (!curr_tile->isOccupied())
            return Move(k, check_col, curr_player);
    }

}

