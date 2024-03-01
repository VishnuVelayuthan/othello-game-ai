#ifndef BOARD_H
#define BOARD_H

#include "./move.h"
#include "./tile.h"
#include "./board_utility.h"

#include <string>
#include <unordered_set>

class Board {
public:
    static int BOARD_SIZE;

    Board(std::string file_name);
    Board(Board curr_board, Move n_move);
    ~Board(); 

    char getCurrTurnPlayer();
    Board* makeMove(char move);

private:
    Tile*** g_board;

    void calculateBoardMoves(char player);
    char curr_turn_player;

    int n_x_tiles;
    int n_o_tiles; 

    int n_allowed_moves;
    std::unordered_set<Move*>* allowed_moves;

};

#endif
