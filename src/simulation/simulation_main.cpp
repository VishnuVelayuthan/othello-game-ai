#include "../../include/board.h"
#include "../../include/move.h"

#include "../../include/openai/openai.hpp"
#include "../../include/openai/nlohmann/json.hpp"
#include "../../include/simulation/snapshots.h"
#include "../../include/simulation/player.h"
#include "../../include/simulation/simulation.h"
#include "../../include/evaluate/game_partition.h"

#include "../../include/eval_board.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

    openai::start(); 

    int PRE_GAME_NUM = 77; // change every run
    int num_games = 40;
    int periodic_parition_store = 3;

    nlohmann::json j;
    
    std::ifstream file("data/serialized-game-partitions/game-partition83.json");
    file >> j;

    Player* p1 = new MinimaxPlayer();
    Player* p2 = new OpenAIPlayer();


    Snapshots* curr_game_data;
    GamePartition** game_partitions = deserializeGamePartitionArr(j);

    initializeGamePartitions();
    for (int i = 0; i < num_games; i++) {

        if (i % 2 == 0)
            curr_game_data = playGame(p1, p2, false);
        else 
            curr_game_data = playGame(p1, p2, true);

        if (curr_game_data == nullptr) {
            i--;
            continue;
        }

        for (int i = 0; i < GamePartition::NUM_GAME_PARTITIONS; i++) {
            game_partitions[i]->update((*curr_game_data)[i], curr_game_data->getWinner());
        }

        csvifySnapshots(curr_game_data);
        serializeSnapshots(curr_game_data, PRE_GAME_NUM + i);

        if (i % periodic_parition_store == 0 && i != 0)
            serializeGamePartitions(game_partitions, PRE_GAME_NUM + i);
    }

}
