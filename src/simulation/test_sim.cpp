#include "../../include/board.h"
#include "../../include/move.h"

#include "../../include/openai/openai.hpp"
#include "../../include/openai/nlohmann/json.hpp"
#include "../../include/simulation/snapshots.h"
#include "../../include/simulation/player.h"
#include "../../include/simulation/simulation.h"
#include "../../include/evaluate/game_partition.h"
#include "../../include/evaluate/game_partition.h"
#include "../../include/evaluate/game_partition_json.h"


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

    cout << "asdfadf" << endl;

    nlohmann::json j = nlohmann::json::parse(GAME_PARTITION_JSON);

    GamePartition** og = deserializeGamePartitionArr(j);

    for (int i = 0; i < GamePartition::NUM_GAME_PARTITIONS; i++) {
        cout << (og[i]->toJson()).dump(4) << endl;
    }

    string filePath = "data/serialized-game-partitions/game-partition13.json";
    std::ifstream file(filePath);
    string json_str;
    file >> j;
    cout << "Here it is: " << j.dump(4) << endl;
    GamePartition** sec = deserializeGamePartitionArr(j);

    cout << "======================================" << endl;

    for (int i = 0; i < GamePartition::NUM_GAME_PARTITIONS; i++) {
        og[i]->aggregateData(sec[i]);
        cout << (og[i]->toJson()).dump(4) << endl;
    }
    
    filePath = "data/serialized-game-partitions/game-partition75.json";
    file = ifstream(filePath);
    sec = deserializeGamePartitionArr(j);

    for (int i = 0; i < GamePartition::NUM_GAME_PARTITIONS; i++) {
        og[i]->aggregateData(sec[i]);
        cout << (og[i]->toJson()).dump(4) << endl;
    }
    
    filePath = "data/serialized-game-partitions/game-partition44.json";
    file = ifstream(filePath);
    sec = deserializeGamePartitionArr(j);

    for (int i = 0; i < GamePartition::NUM_GAME_PARTITIONS; i++) {
        og[i]->aggregateData(sec[i]);
        cout << (og[i]->toJson()).dump(4) << endl;
    }

    serializeGamePartitions(og, 80);
}
