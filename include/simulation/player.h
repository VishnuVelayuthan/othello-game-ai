#ifndef PLAYER_H
#define PLAYER_H 

#include "../board.h"
#include "openai.hpp"

class Player {
public:
    Player(bool is_ai) : is_ai(is_ai) {};

    virtual Move* play(Board* board) = 0;

    void setPlayerSymbol(char player) {this->player_sym = player;};
    void getPlayerSymbol() {return player_sym;};
protected:
    char player_sym;
    bool is_ai;

};


// class MinimaxPlayer : Player {
// public: 
//     MinimaxPlayer(char player_sym) : Player(player_sym, false){};
//
//     inline Move* play(Board* board) override;
//
// private:
//     static constexpr int PLY_COUNT = 8;
// };

class OpenAIPlayer: Player {
public:
    OpenAIPlayer() : Player(true) {
        openai::start();
    };

    inline Move* play(Board* board) override;
};


#endif 
