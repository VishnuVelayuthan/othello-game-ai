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

        snapshots[location-1] = new Snapshot(board, x_moves, o_moves, location == Board::BOARD_SIZE);
    };
    
    void setWinner(char winner) {this->winner = winner;};
    char getWinner() {return this->winner;};

    Snapshot* operator[] (int i) {
        return snapshots[i];
    };

    void addMove(Move* move) {
        Move* a_m = new Move(move);
        moves.push_back(a_m);
    };


private:
    Snapshot** snapshots;
    char winner;

    std::vector<Move*> moves;


};

#endif 
