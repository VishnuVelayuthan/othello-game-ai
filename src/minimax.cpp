#include "../include/eval_board.h"

#include <limits>
#include <unordered_set>
#include <iostream>


MMScoreMove* minimaxMaxABValue(Board* cs_board, int ply_count, char opt_player, double alpha, double beta);
MMScoreMove* minimaxMinABValue(Board* cs_board, int ply_count, char opt_player, double alpha, double beta);

Move* minimaxAlphaBetaSearch(Board* s_board, int ply_count) {

    char opt_player = s_board->getCurrTurnPlayer();

    MMScoreMove* opt_mmsm = minimaxMaxABValue(s_board, ply_count, opt_player, 
            -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());

    Move* opt_move = opt_mmsm->getMove();
    delete opt_mmsm;

    return opt_move;
}

MMScoreMove* minimaxMaxABValue(Board* cs_board, int ply_count, char opt_player, double alpha, double beta) {
    if (ply_count == 0 || cs_board->isTerminalBoard()) 
        return new MMScoreMove(evaluateBoard(cs_board, opt_player), nullptr);

    MMScoreMove* max_min_sm = new MMScoreMove(-std::numeric_limits<double>::infinity(), nullptr);
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* cs_operators = cs_board->getAllowedMoves();

    MMScoreMove* curr_min;
    double curr_min_score;
    Board* new_board;
    Move* curr_operator;
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>::iterator it;
    for (it = cs_operators->begin(); it != cs_operators->end(); ++it){
        curr_operator = *it;

        new_board = cs_board->copyBoard();
        new_board->makeMove(curr_operator);

        curr_min = minimaxMinABValue(new_board, ply_count - 1, opt_player, alpha, beta);
        curr_min_score = curr_min->getScore();
        
        // TODO Need a tie condition 
        if (curr_min_score > max_min_sm->getScore()) {
            max_min_sm->setScore(curr_min_score);
            max_min_sm->setMove(curr_operator);
            alpha = std::max(alpha, curr_min_score);
        }

        delete curr_min;
        delete new_board;

        // TODO Need a tie condition 
        if (curr_min_score >= beta) 
            return max_min_sm;
    }
    
    if (cs_operators->size() == 0) {
        new_board = cs_board->copyBoard();
        new_board->makeMove(nullptr);
        max_min_sm = minimaxMinABValue(new_board, ply_count - 1, opt_player, alpha, beta);
        delete new_board;
    }

    return max_min_sm;
} 

MMScoreMove* minimaxMinABValue(Board* cs_board, int ply_count, char opt_player, double alpha, double beta) {
    if (ply_count == 0 || cs_board->isTerminalBoard()) 
        return new MMScoreMove(evaluateBoard(cs_board, opt_player), nullptr);

    MMScoreMove* min_max_sm = new MMScoreMove(std::numeric_limits<double>::infinity(), nullptr);
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* cs_operators = cs_board->getAllowedMoves();

    MMScoreMove* curr_max;
    double curr_max_score;
    Board* new_board;
    Move* curr_operator;
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>::iterator it;
    for (it = cs_operators->begin(); it != cs_operators->end(); ++it) {
        curr_operator = *it;

        new_board = cs_board->copyBoard();
        new_board->makeMove(curr_operator);

        curr_max = minimaxMaxABValue(new_board, ply_count - 1, opt_player, alpha, beta);
        curr_max_score = curr_max->getScore();
        
        // TODO need a tie condition
        if (curr_max_score < min_max_sm->getScore()) {
            min_max_sm->setScore(curr_max_score);
            min_max_sm->setMove(curr_operator);
            beta = std::min(beta, curr_max_score);
        }

        delete curr_max;
        delete new_board;

        // Need a tie condition
        if (curr_max_score <= alpha)
            return min_max_sm;
    }

    if (cs_operators->size() == 0) {
        new_board = cs_board->copyBoard();
        new_board->makeMove(nullptr);
        min_max_sm = minimaxMaxABValue(new_board, ply_count - 1, opt_player, alpha, beta);
        delete new_board;
    }
    return min_max_sm;
}


