#include "../../include/simulation/player.h" 

#include "../../include/eval_board.h"
#include "openai.hpp"

Move* MinimaxPlayer::play(Board* board) {
    return minimaxAlphaBetaSearch(board, PLY_COUNT);
}

Move* OpenAIPlayer::play(Board* board) { 
    auto completion = openai::completion().create(R"({
            "model": "text-davinci-003",
            "prompt": "Say this is a test",
            "max_tokens": 7,
            "temperature": 0
        })"_json); // Using user-defined (raw) string literals
    std::cout << "Response is:\n" << completion.dump(2) << '\n'; 

}
