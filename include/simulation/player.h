#ifndef PLAYER_H
#define PLAYER_H 

#include "../board.h"
#include "../openai/openai.hpp"

class Player {
public:
    Player(bool is_ai) : is_ai(is_ai) {};

    virtual Move* play(Board* board) {return nullptr;};

    void setPlayerSymbol(char player) {this->player_sym = player;};
    char getPlayerSymbol() {return player_sym;};
protected:
    char player_sym;
    bool is_ai;

};


class MinimaxPlayer : public Player {
public: 
    MinimaxPlayer() : Player(false){};

    Move* play(Board* board) override;

private:
    static constexpr int PLY_COUNT = 8;
};

class OpenAIPlayer: public Player {
public:
    OpenAIPlayer() : Player(true) {
        openai::start();
    };

    Move* play(Board* board) override;
};


#endif 
