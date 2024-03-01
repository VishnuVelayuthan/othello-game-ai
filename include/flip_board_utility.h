#ifndef FLIP_BOARD_H
#define FLIP_BOARD_H

#include "./move.h"
#include "./board.h"

void flipPiecesUp(Tile*** g_board, int b_size, Move* n_move);
void flipPiecesDown(Tile*** g_board, int b_size, Move* n_move);

void flipPiecesLeft(Tile*** g_board, int b_size, Move* n_move);
void flipPiecesRight(Tile*** g_board, int b_size, Move* n_move);

void flipPiecesLUD(Tile*** g_board, int b_size, Move* n_move);
void flipPiecesRUD(Tile*** g_board, int b_size, Move* n_move);

void flipPiecesLDD(Tile*** g_board, int b_size, Move* n_move);
void flipPiecesRDD(Tile*** g_board, int b_size, Move* n_move);

#endif
