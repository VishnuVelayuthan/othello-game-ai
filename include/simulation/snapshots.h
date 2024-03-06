#ifndef SNAPSHOTS_H
#define SNAPSHOTS_H 

#include "./snapshot.h"
#include "../board.h"

#include <vector>

class Snapshots {
public:
    Snapshots() {
        snapshots = new Snapshot*[Board::BOARD_SIZE];
    };

    ~Snapshots() {
        for (int i = 0; i < Board::BOARD_SIZE; i++) {
            delete snapshots[i];
        }
        delete [] snapshots;

        for (int i = 0; i < moves.size(); i++) {
            delete moves[i];
        }
    };

    void add(int location, Board* board, int x_moves, int o_moves) {
        if (snapshots[location-1])
            return;

        snapshots[location-1] = new Snapshot(board, location == Board::BOARD_SIZE);
    };
    
    void setWinner(char winner) {this->winner = winner;};

    void addMove(Move* move) {
        Move* a_m = new Move(move);
        moves.add(a_m);
    };


private:
    Snapshot** snapshots;
    char winnner;

    std::vector<Move*> moves;


};

#endif 
