#ifndef PLAYER_H
#define PLAYER_H 

#include "../board.h"
#include "../eval_board.h"

class Player {
public:
    Player(char player_sym, bool is_ai) :
        player_sym(player_sym), is_ai(is_ai) {};

    virtual Move* play(Board* board) = 0;

protected:
    char player_sym;
    bool is_ai;

};


class MinimaxPlayer : Player {
public: 
    MinimaxPlayer(char player_sym) : Player(player_sym, false){};

    inline Move* play(Board* board) override;

private:
    static constexpr int PLY_COUNT = 8;
};

class OpenAIPlayer: Player {
public:
    OpenAIPlayer(char player_sym) : Player(player_sym, true) {};

    inline Move* play(Board* board) override;
};


#endif 
