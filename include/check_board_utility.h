#ifndef CHECK_BOARD_UTILITY_H
#define CHECK_BOARD_UTILITY_H

#include "./move.h"
#include "./board.h"

Move* checkBoardUp(Tile*** g_board, int b_size, Tile* check_tile, char curr_player);
Move* checkBoardDown(Tile*** g_board, int b_size, Tile* check_tile, char curr_player);

Move* checkBoardLeft(Tile*** g_board, int b_size, Tile* check_tile, char curr_player);
Move* checkBoardRight(Tile*** g_board, int b_size, Tile* check_tile, char curr_player);

Move* checkBoardLUD(Tile*** g_board, int b_size, Tile* check_tile, char curr_player);
Move* checkBoardRUD(Tile*** g_board, int b_size, Tile* check_tile, char curr_player);

Move* checkBoardLDD(Tile*** g_board, int b_size, Tile* check_tile, char curr_player);
Move* checkBoardRDD(Tile*** g_board, int b_size, Tile* check_tile, char curr_player);

#endif
