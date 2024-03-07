#include "../../include/simulation/simulation.h"
#include "../../include/openai/nlohmann/json.hpp"
#include "../../include/simulation/snapshot.h"
#include "../../include/simulation/snapshots.h"

#include <tuple>
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

using json = nlohmann::json;

void csvifySnapshots(Snapshots* game_data) {

    Snapshot* curr_snap;
    ofstream curr_csv;
    for (int i = 0; i < GamePartition::NUM_GAME_PARTITIONS; i++) {
        curr_csv = ofstream("data/csv-snapshots/snapshot-" + to_string(i) + ".csv", ios::app);
        curr_snap = (*game_data)[i];

        curr_csv << game_data->getWinner() << ", " << 
                    curr_snap->curr_player_turn << ", ";

        curr_csv << curr_snap->n_x_tiles << ", " << 
                    curr_snap->n_x_moves << ", " << 
                    curr_snap->n_x_lm << ", ";

        curr_csv << curr_snap->n_o_tiles << ", " << 
                    curr_snap->n_o_moves << ", " << 
                    curr_snap->n_o_lm << endl;

    }
}


void serializeSnapshots(Snapshots* game_data, int game_num) {
    ofstream json_file = ofstream("data/serialized-snapshots/game-snapshot-" + to_string(game_num) + ".json", ios::app);
    json_file << (game_data->toJson()).dump(4);
    json_file.close();
}

void serializeGamePartitions(GamePartition** g_p, int game_num) {
    ofstream json_file = ofstream("data/serialized-game-partitions/game-partition" + to_string(game_num) + ".json", ios::app);

    nlohmann::json jsonArray = nlohmann::json::array();
    for (int i = 0; i < GamePartition::NUM_GAME_PARTITIONS; i++)
        jsonArray.push_back(g_p[i]->toJson());

    json_file << jsonArray.dump(4);
    json_file.close();
}


nlohmann::json Snapshots::toJson() const {
    nlohmann::json j;

    // Serialize snapshots
    nlohmann::json snapshotsJson = nlohmann::json::array();
    for (int i = 0; i < Board::BOARD_SIZE; ++i) {
        if (snapshots[i] != nullptr) {
            snapshotsJson.push_back(snapshots[i]->toJson());
        } else {
            snapshotsJson.push_back(nullptr);
        }
    }

    j["snapshots"] = snapshotsJson;

    // Serialize moves
    nlohmann::json movesJson = nlohmann::json::array();
    for (auto& move : moves) {
        movesJson.push_back(move->toJson());
    }

    j["moves"] = movesJson;

    j["winner"] = std::string(1, winner);

    return j;
}

json Snapshot::toJson() {
    json j;

    // Serialize only the essential and simple attributes
    j["curr_player_turn"] = curr_player_turn;
    j["n_x_tiles"] = n_x_tiles;
    j["n_o_tiles"] = n_o_tiles;
    j["n_x_lm"] = n_x_lm;
    j["n_o_lm"] = n_o_lm;
    j["n_x_moves"] = n_x_moves;
    j["n_o_moves"] = n_o_moves;
    // Assume Board::toJSON exists
    j["board"] = g_board->toJson();
    return j;
}




