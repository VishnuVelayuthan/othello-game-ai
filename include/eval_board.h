#ifndef EVAL_BOARD_H
#define EVAL_BOARD_H

#include "./move.h"
#include "./board.h"

class MMScoreMove {
public:
    inline MMScoreMove(double score, Move* move) : m_score(score), m_move(move){};
    ~MMScoreMove(){};

    double getScore() {return this->m_score;};
    Move* getMove() {return this->m_move;};

    void setScore(int score) {this->m_score = score;};
    void setMove(Move* move) {this->m_move = move;};

private:
    double m_score;
    Move* m_move;
};

double evaluateBoard(Board* e_board, char opt_player);
Move* minimaxSearch(Board* s_board, int ply_count);
Move* minimaxAlphaBetaSearch(Board* s_board, int ply_count);

void initializeGamePartitions();
void deleteGamePartitions();

#endif
