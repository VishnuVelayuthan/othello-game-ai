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
    GamePartition* game_partitions;

    for (int i = 0; i < num_games; i++) {

        if (i % 2 == 0)
            curr_game_data = playGame(p1, p2, false);
        else 
            curr_game_data = playGame(p1, p2, true);

        // saveGameData(curr_game_data);
        // updatePartitionData(curr_game_data);

        // if (i + 1 % periodic_parition_store == 0) 
            // savePartitionData(game_partitions);
    }

}
