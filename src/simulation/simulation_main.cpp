#include "../../include/board.h"
#include "../../include/move.h"

#include "../../include/openai/openai.hpp"
#include "../../include/openai/nlohmann/json.hpp"
#include "../../include/simulation/snapshots.h"
#include "../../include/simulation/player.h"
#include "../../include/simulation/simulation.h"
#include "../../include/evaluate/game_partition.h"


#include <iostream>
#include <string>

using namespace std;

int main() {

    openai::start(); 

    int num_games = 1;
    int periodic_parition_store = 10;

    Player* p1 = new OpenAIPlayer();
    Player* p2 = new OpenAIPlayer();

    Snapshots* curr_game_data;
    GamePartition** game_partitions = new GamePartition*[Board::BOARD_SIZE];
    for (int i = 0; i < Board::BOARD_SIZE; i++) 
        game_partitions[i] = new GamePartition();

    for (int i = 0; i < num_games; i++) {

        if (i % 2 == 0)
            curr_game_data = playGame(p1, p2, false);
        else 
            curr_game_data = playGame(p1, p2, true);

        // saveGameData(curr_game_data);
        for (int i = 0; i < GamePartition::NUM_GAME_PARTITIONS; i++) {
            game_partitions[i]->update((*curr_game_data)[i], curr_game_data->getWinner());
        }

        // if (i + 1 % periodic_parition_store == 0) 
            // savePartitionData(game_partitions);
    }

    GamePartition* test1 = game_partitions[3];
}
