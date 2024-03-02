#ifndef CHECK_BOARD_UTILITY_H
#define CHECK_BOARD_UTILITY_H

#include "./board.h"
#include "./move.h"
#include "./tile.h"

#include <unordered_set>

void deleteNullMove();

Move* checkBoardUp(Tile*** g_board, int b_size, std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves, Tile* check_tile, char curr_player);
Move* checkBoardDown(Tile*** g_board, int b_size, std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves, Tile* check_tile, char curr_player);

Move* checkBoardLeft(Tile*** g_board, int b_size, std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves, Tile* check_tile, char curr_player);
Move* checkBoardRight(Tile*** g_board, int b_size, std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves, Tile* check_tile, char curr_player);

Move* checkBoardLUD(Tile*** g_board, int b_size, std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves, Tile* check_tile, char curr_player);
Move* checkBoardRUD(Tile*** g_board, int b_size, std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves, Tile* check_tile, char curr_player);

Move* checkBoardLDD(Tile*** g_board, int b_size, std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves, Tile* check_tile, char curr_player);
Move* checkBoardRDD(Tile*** g_board, int b_size, std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves, Tile* check_tile, char curr_player);

#endif
