#include "../../include/simulation/simulation.h"
#include "../../include/openai/nlohmann/json.hpp"
#include "../../include/simulation/snapshot.h"
#include "../../include/simulation/snapshots.h"

#include <tuple>
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

void serializeSnapshots(Snapshots* game_data, string name) {

}

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
