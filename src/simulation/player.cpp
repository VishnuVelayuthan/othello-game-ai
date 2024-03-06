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
    prompt += "maximize your chance of victory. Do not let it be a draw. You cannot end up on two seperate islands. ";
    prompt += "You should try and take the corners and not give up the corners cause those are stable disks. Employ a ";
    prompt += "strategy of evaporation in the first phase of the game. Any opportunity to take corners, take."; 

    prompt += "Here is the board: \u000A" + board->toString();
    prompt += "It's move: " + to_string(board->moveCount()); + "\u000A";
    prompt += "Here are your legal moves: " + board->allowedMovesToString();
    prompt += "It's " + string(1, board->getCurrTurnPlayer()) + " to play. ";
    prompt += "Remember, DON'T GIVE UP CORNERS. AND TAKE CORNERS. NOR PLAY IN THE ADJACENT CORNER SQUARES UNLESS STRATEGICALLY. ";
    prompt += "All you return is (row, col). Nothing more.";
 
    nlohmann::json j = {
        {"model", "gpt-4"},
        {"messages", nlohmann::json::array({
            {{"role", "user"}, {"content", prompt}}
        })},
        {"temperature", 0.5}
    };

    string json_str = j.dump();

    auto jsonObject = nlohmann::json::parse(json_str);

    Move* new_m;
    auto& openai = openai::instance();
    auto completion = openai::_detail::CategoryChat(openai).create(jsonObject); // Using user-defined (raw) string literals

    string move_str = completion["choices"][0]["message"]["content"];

    cout << move_str << endl;
    cout << board->allowedMovesToString() << endl;

    new_m = board->findMove(move_str);



    Board* next_move = board->copyBoard();
    next_move->makeMove(new_m);
    
    // To prevent beginning draw 
    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* nn_am = next_move->calculateBoardMoves(
        next_move->getCurrTurnPlayer() == 'X' ? 'O' : 'X'
    );
    if ((next_move->getAllowedMoves())->size() <= 3 && nn_am->size() <= 3 && next_move->moveCount() <= 8) {
        std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* curr_moves = 
            board->getAllowedMoves();
        for (Move* move : *curr_moves)  {
            if (new_m != move) {
                new_m = move;
                break;
            }
        }
        
    }

    return new_m;    
}
