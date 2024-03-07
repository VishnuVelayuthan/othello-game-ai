#ifndef BOARD_H
#define BOARD_H

#include "./move.h"
#include "./tile.h"
#include "./openai/nlohmann/json.hpp"

#include <string>
#include <unordered_set>

struct MovePointerDefEqual{
    bool operator()(const Move* a, const Move* b) const {
        return *(a) == *(b);
    }
};

class Board {
public:
    static constexpr int BOARD_SIZE = 12;
    static constexpr int N_STARTING_PIECES = 8;

    Board(std::string file_name);
    Board();

    ~Board(); 

    char getCurrTurnPlayer();
    Tile*** getGameBoard() {return this->g_board;};
    double getNumXTiles() {return this->n_x_tiles;};
    double getNumOTiles() {return this->n_o_tiles;};
    int moveCount() {return n_x_tiles + n_o_tiles + 1 - N_STARTING_PIECES;};

    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* getAllowedMoves() {return this->allowed_moves;};
    
    Board* copyBoard();
    void makeMove(Move* n_move);
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* calculateBoardMoves(char player);
    Move* findMove(std::string move_str);

    std::string toString();
    std::string allowedMovesToString();

    nlohmann::json toJson() const;

private:
    Tile*** g_board;
    char curr_turn_player;

    int n_x_tiles;
    int n_o_tiles; 

    int n_allowed_moves;
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* allowed_moves;

    void updateXOtileCount();
};

#endif
