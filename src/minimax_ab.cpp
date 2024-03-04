#include "../include/eval_board.h"

#include <limits>
#include <unordered_set>
#include <iostream>


MMScoreMove* minimaxMaxValue(Board* cs_board, int ply_count, char opt_player);
MMScoreMove* minimaxMinValue(Board* cs_board, int ply_count, char opt_player);

Move* minimaxSearch(Board* s_board, int ply_count) {

    char opt_player = s_board->getCurrTurnPlayer();

    MMScoreMove* opt_mmsm = minimaxMaxValue(s_board, ply_count, opt_player);

    Move* opt_move = opt_mmsm->getMove();
    delete opt_mmsm;

    return opt_move;
}

MMScoreMove* minimaxMaxValue(Board* cs_board, int ply_count, char opt_player) {
    if (ply_count == 0) 
        return new MMScoreMove(evaluateBoard(cs_board, opt_player), nullptr);

    MMScoreMove* max_min_sm = new MMScoreMove(-std::numeric_limits<double>::infinity(), nullptr);
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* cs_operators = cs_board->getAllowedMoves();

    MMScoreMove* curr_min;
    Board* new_board;
    Move* curr_operator;
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>::iterator it;
    for (it = cs_operators->begin(); it != cs_operators->end(); ++it){
        curr_operator = *it;

        new_board = cs_board->copyBoard();
        new_board->makeMove(curr_operator);

        curr_min = minimaxMinValue(new_board, ply_count - 1, opt_player);
        
        if (curr_min->getScore() > max_min_sm->getScore()) {
            max_min_sm->setScore(curr_min->getScore());
            max_min_sm->setMove(curr_operator);
        }

        delete curr_min;
        delete new_board;
    }

    return max_min_sm;
} 

MMScoreMove* minimaxMinValue(Board* cs_board, int ply_count, char opt_player) { 
    if (ply_count == 0) 
        return new MMScoreMove(evaluateBoard(cs_board, opt_player), nullptr);

    MMScoreMove* min_max_sm = new MMScoreMove(std::numeric_limits<double>::infinity(), nullptr);
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* cs_operators = cs_board->getAllowedMoves();

    MMScoreMove* curr_max;
    Board* new_board;
    Move* curr_operator;
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>::iterator it;
    for (it = cs_operators->begin(); it != cs_operators->end(); ++it) {
        curr_operator = *it;

        new_board = cs_board->copyBoard();
        new_board->makeMove(curr_operator);

        curr_max = minimaxMaxValue(new_board, ply_count - 1, opt_player);
        
        if (curr_max->getScore() < min_max_sm->getScore()) {
            min_max_sm->setScore(curr_max->getScore());
            min_max_sm->setMove(curr_operator);
        }

        delete curr_max;
        delete new_board;
    }

    return min_max_sm;
}


