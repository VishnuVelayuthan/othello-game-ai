#ifndef BOARD_H
#define BOARD_H

#include "./move.h"
#include "./tile.h"

#include <string>
#include <unordered_set>

struct MovePointerDefEqual{
    bool operator()(const Move* a, const Move* b) const {
        return *(a) == *(b);
    }
};

class Board {
public:
    static int BOARD_SIZE;

    Board(std::string file_name);
    Board();

    ~Board(); 

    char getCurrTurnPlayer();
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* getAllowedMoves() {return this->allowed_moves;};
    
    Board* copyBoard();
    void makeMove(Move* n_move);

    std::string toString();

private:
    Tile*** g_board;
    char curr_turn_player;

    int n_x_tiles;
    int n_o_tiles; 

    int n_allowed_moves;
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves;

    void calculateBoardMoves(char player);
    void updateXOtileCount();
};

#endif
