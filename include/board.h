#ifndef BOARD_H
#define BOARD_H

#include "./move.h"
#include "./tile.h"
#include "./check_board_utility.h"
#include "./flip_board_utility.h"

#include <string>
#include <unordered_set>

class Board {
public:
    static int BOARD_SIZE;

    Board(std::string file_name);
    Board();

    ~Board(); 

    char getCurrTurnPlayer();
    
    Board* copyBoard();
    void makeMove(Move* n_move);

private:
    Tile*** g_board;
    char curr_turn_player;

    int n_x_tiles;
    int n_o_tiles; 

    int n_allowed_moves;
    std::unordered_set<Move*>* allowed_moves;

    void calculateBoardMoves(char player);
    void updateXOtileCount();
};

#endif
