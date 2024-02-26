#ifndef BOARD_H
#define BOARD_H

#include "./move.h"

#include <string>
#include <unordered_set>

class Board {
public:
    Board(std::string file_name);
    Board(Board curr_board, char move);
    ~Board(); 

    char getCurrTurnPlayer();

private:
    Tile** g_board;

    std::unordered_set<Move> calculateBoardMoves(char player);
    char curr_turn_player;

    int n_x_tiles;
    int n_o_tiles; 

    int n_allowed_moves;
    unordered_set<Move> allowed_moves;

};

#endif
