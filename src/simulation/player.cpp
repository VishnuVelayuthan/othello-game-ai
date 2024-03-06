#include "../../include/simulation/player.h" 

#include "../../include/eval_board.h"
#include "../../include/openai/openai.hpp"

#include <string>

using namespace std;

// Move* MinimaxPlayer::play(Board* board) {
//     return minimaxAlphaBetaSearch(board, PLY_COUNT);
// }

Move* OpenAIPlayer::play(Board* board) { 

    if ((board->getAllowedMoves())->size() == 0) 
        return nullptr;

    string prompt = "Think step by step. ";
    prompt = "You are a grandmaster Othello player playing a variation of the standard game. ";
    prompt += "Instead of a 8x8 board, it's a 12x12 board with rows and cols labeled 0-12. ";
    prompt += "Your job is given a board, legal moves and what player, make the most accurate move. ";
    prompt += "Remember, you must try and get stable disks, think critically about future moves, and ";
    prompt += "maximize your chance of victory. ";
    

    prompt += "Here is .the board: \u000A" + board->toString();
    prompt += "It's move: " + to_string(board->moveCount()); + "\u000A";
    prompt += "Here are your legal moves: " + board->allowedMovesToString();
    prompt += "It's " + string(1, board->getCurrTurnPlayer()) + " to play. All you return is (row, col)";
 
    nlohmann::json j = {
        {"model", "gpt-4"},
        {"messages", nlohmann::json::array({
            {{"role", "user"}, {"content", prompt}}
        })},
        {"temperature", 0.7}
    };

    string json_str = j.dump();

    auto jsonObject = nlohmann::json::parse(json_str);

    auto& openai = openai::instance();
    auto completion = openai::_detail::CategoryChat(openai).create(jsonObject); // Using user-defined (raw) string literals

    string move_str = completion["choices"][0]["message"]["content"];

    return board->findMove(move_str);    
}
