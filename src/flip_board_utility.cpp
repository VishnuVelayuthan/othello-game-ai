#include "../include/flip_board_utility.h"

void flipPiecesUp(Tile*** g_board, int b_size, Move* n_move) {

    int flip_row = n_move->getIrow();
    int flip_col = n_move->getIcol();
    char flip_player = n_move->getPlayer();

    if (flip_row <= 1) 
        return;

    Tile* curr_tile; 

    for (int i = 1; i < flip_row; i++) {
        curr_tile = g_board[flip_row - i][flip_col];

        if (curr_tile->getPlayerOcc() == flip_player) 
            return;
        else
            curr_tile->setPlayerOcc(flip_player); 
    }
}

void flipPiecesDown(Tile*** g_board, int b_size, Move* n_move) {

    int flip_row = n_move->getIrow();
    int flip_col = n_move->getIcol();
    char flip_player = n_move->getPlayer();

    if (flip_row >= b_size-2) 
        return;

    Tile* curr_tile; 

    for (int i = 1; i < b_size - flip_row; i++) {
        curr_tile = g_board[flip_row + i][flip_col];

        if (curr_tile->getPlayerOcc() == flip_player) 
            return;
        else
            curr_tile->setPlayerOcc(flip_player); 
    }
}

void flipPiecesLeft(Tile*** g_board, int b_size, Move* n_move) {

    int flip_row = n_move->getIrow();
    int flip_col = n_move->getIcol();
    char flip_player = n_move->getPlayer();

    if (flip_col <= 1) 
        return;

    Tile* curr_tile; 
    for (int i = 1; i < flip_col; i++) {
        curr_tile = g_board[flip_row][flip_col - i];

        if (curr_tile->getPlayerOcc() == flip_player) 
            return;
        else
            curr_tile->setPlayerOcc(flip_player); 
    }
}

void flipPiecesRight(Tile*** g_board, int b_size, Move* n_move) {

    int flip_row = n_move->getIrow();
    int flip_col = n_move->getIcol();
    char flip_player = n_move->getPlayer();

    if (flip_col >= b_size - 2) 
        return;

    Tile* curr_tile; 
    for (int i = 1; i < b_size - flip_col; i++) {
        curr_tile = g_board[flip_row][flip_col + i];

        if (curr_tile->getPlayerOcc() == flip_player) 
            return;
        else
            curr_tile->setPlayerOcc(flip_player); 
    }
}

void flipPiecesLUD(Tile*** g_board, int b_size, Move* n_move) {

    int flip_row = n_move->getIrow();
    int flip_col = n_move->getIcol();
    char flip_player = n_move->getPlayer();

    if (flip_col >= b_size - 2) 
        return;

    Tile* curr_tile; 
    for (int i = 1; i < b_size - flip_col; i++) {
        curr_tile = g_board[flip_row][flip_col + i];

        if (curr_tile->getPlayerOcc() == flip_player) 
            return;
        else
            curr_tile->setPlayerOcc(flip_player); 
    }
}



void flipPiecesRUD(Tile*** g_board, int b_size, Move* n_move) {
}
void flipPiecesLDD(Tile*** g_board, int b_size, Move* n_move) {
}
void flipPiecesRDD(Tile*** g_board, int b_size, Move* n_move) {
}

