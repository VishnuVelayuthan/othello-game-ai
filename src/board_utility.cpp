#include "../include/board_utility.h"
#include <algorithm>

using namespace std;

static Move* null_move = new Move(-1,-1,'.');

Move* checkBoardUp(Tile*** g_board, int b_size, Tile* check_tile, char curr_player) {

    int check_row = check_tile->getIrow();
    int check_col = check_tile->getIcol();

    if (check_row == 0) 
        return null_move;

    Tile* curr_tile = g_board[check_row-1][check_col];

    if (!curr_tile->isOccupied() || curr_tile->getPlayerOcc() == curr_player)
        return null_move;
    
    for (int k = check_row-2; k >= 0; k--) {
        curr_tile = g_board[k][check_col];

        if (curr_tile->getPlayerOcc() == curr_player) 
            return null_move;
        else if (!curr_tile->isOccupied())
            return new Move(k, check_col, curr_player);
    }

    return null_move;
}

Move* checkBoardDown(Tile*** g_board, int b_size, Tile* check_tile, char curr_player) {

    int check_row = check_tile->getIrow();
    int check_col = check_tile->getIcol();

    if (check_row == b_size - 1) return null_move;

    Tile* curr_tile = g_board[check_row+1][check_col];

    if (!curr_tile->isOccupied() || curr_tile->getPlayerOcc() == curr_player)
        return null_move;

    for (int k = check_row+2; k < b_size; k++) {
        curr_tile = g_board[k][check_col];

        if (curr_tile->getPlayerOcc() == curr_player) 
            return null_move;
        else if (!curr_tile->isOccupied())
            return new Move(k, check_col, curr_player);
    }

    return null_move;

}

Move* checkBoardRight(Tile*** g_board, int b_size, Tile* check_tile, char curr_player) {
    int check_row = check_tile->getIrow();
    int check_col = check_tile->getIcol();

    if (check_col == b_size - 1) return null_move;
    
    Tile* curr_tile = g_board[check_row][check_col+1];

    if (!curr_tile->isOccupied() || curr_tile->getPlayerOcc() == curr_player)
        return null_move;

    for (int k = check_col+2; k < b_size; k++) {
        curr_tile = g_board[check_row][k];

        if (curr_tile->getPlayerOcc() == curr_player) 
            return null_move;
        else if (!curr_tile->isOccupied())
            return new Move(check_row, k, curr_player);
    }

    return null_move;

}


Move* checkBoardLeft(Tile*** g_board, int b_size, Tile* check_tile, char curr_player) {

    int check_row = check_tile->getIrow();
    int check_col = check_tile->getIcol();

    if (check_col == 0) return null_move;
    
    Tile* curr_tile = g_board[check_row][check_col-1];

    if (!curr_tile->isOccupied() || curr_tile->getPlayerOcc() == curr_player)
        return null_move;

    for (int k = check_col-2; k >= 0; k--) {
        curr_tile = g_board[check_row][k];

        if (curr_tile->getPlayerOcc() == curr_player) 
            return null_move;
        else if (!curr_tile->isOccupied())
            return new Move(check_row, k, curr_player);
    }

    return null_move;
}


Move* checkBoardLUD(Tile*** g_board, int b_size, Tile* check_tile, char curr_player) {
    int check_row = check_tile->getIrow();
    int check_col = check_tile->getIcol();

    if (check_col == 0 || check_row == 0) return null_move;

    Tile* curr_tile = g_board[check_row-1][check_col-1];

    if (!curr_tile->isOccupied() || curr_tile->getPlayerOcc() == curr_player)
        return null_move;

    for (int k = 2; k <= std::min(check_row, check_col) ; k++) {
        curr_tile = g_board[check_row - k][check_col - k];

        if (curr_tile->getPlayerOcc() == curr_player) 
            return null_move;
        else if (!curr_tile->isOccupied())
            return new Move(check_row, k, curr_player);
    }

    return null_move;
}


Move* checkBoardRUD(Tile*** g_board, int b_size, Tile* check_tile, char curr_player) {

    int check_row = check_tile->getIrow();
    int check_col = check_tile->getIcol();

    if ((check_col == (b_size - 1))  || check_row == 0) return null_move;

    Tile* curr_tile = g_board[check_row-1][check_col+1];

    if (!curr_tile->isOccupied() || curr_tile->getPlayerOcc() == curr_player)
        return null_move;

    for (int k = 2; k <= std::min(check_row, b_size - check_col) ; k++) {
        curr_tile = g_board[check_row - k][check_col + k];

        if (curr_tile->getPlayerOcc() == curr_player) 
            return null_move;
        else if (!curr_tile->isOccupied())
            return new Move(check_row, k, curr_player);
    }

    return null_move;
}


Move* checkBoardLDD(Tile*** g_board, int b_size, Tile* check_tile, char curr_player) {

    int check_row = check_tile->getIrow();
    int check_col = check_tile->getIcol();

    if (check_col == 0  || check_row == b_size-1) return null_move;

    Tile* curr_tile = g_board[check_row+1][check_col-1];

    if (!curr_tile->isOccupied() || curr_tile->getPlayerOcc() == curr_player)
        return null_move;

    for (int k = 2; k <= std::min(b_size - check_row,  check_col) ; k++) {
        curr_tile = g_board[check_row + k][check_col - k];

        if (curr_tile->getPlayerOcc() == curr_player) 
            return null_move;
        else if (!curr_tile->isOccupied())
            return new Move(check_row, k, curr_player);
    }

    return null_move;
}


Move* checkBoardRDD(Tile*** g_board, int b_size, Tile* check_tile, char curr_player) {

    int check_row = check_tile->getIrow();
    int check_col = check_tile->getIcol();

    if (check_col == b_size-1  || check_row == b_size-1) return null_move;

    Tile* curr_tile = g_board[check_row+1][check_col+1];

    if (!curr_tile->isOccupied() || curr_tile->getPlayerOcc() == curr_player)
        return null_move;

    for (int k = 2; k <= std::min(b_size - check_row,  b_size - check_col) ; k++) {
        curr_tile = g_board[check_row + k][check_col + k];

        if (curr_tile->getPlayerOcc() == curr_player) 
            return null_move;
        else if (!curr_tile->isOccupied())
            return new Move(check_row, k, curr_player);
    }

    return null_move;
}



