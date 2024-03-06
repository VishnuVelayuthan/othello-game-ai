#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "../board.h"

#include <unordered_set>
#include <iostream>

class Snapshot {
public:
    Snapshot(Board* board, int x_moves, int o_moves, bool is_final) {
        g_board = board->copyBoard();

        curr_player_turn = g_board->getCurrTurnPlayer();

        n_x_tiles = g_board->getNumXTiles();
        n_o_tiles = g_board->getNumOTiles();

        n_x_moves = x_moves;
        n_o_moves = o_moves;

        if (is_final) {
            n_x_lm = 0;
            n_o_lm = 0;
            return;
        }

        if (curr_player_turn == 'X') {
            std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* a_m = g_board->getAllowedMoves();
            if (!a_m) {
                n_x_lm = 0;
                std::cout << "Buggin" << std::endl;
            }
            else
                n_x_lm = a_m->size();
        }
        else {
            std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* a_m = g_board->getAllowedMoves();
            if (!a_m) {
                n_o_lm = 0;
                std::cout << "Buggin" << std::endl;

            }
            else
                n_o_lm = a_m->size();
        }
    };


    Board* getBoard() {return this->g_board;};
private:
    Board* g_board;

    char curr_player_turn;

    // on current turn
    int n_x_tiles;
    int n_o_tiles;

    // maybe on next turn
    int n_x_lm;
    int n_o_lm;

    // on current turn
    int n_x_moves;
    int n_o_moves;

};

#endif 
