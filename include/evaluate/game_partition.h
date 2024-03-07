#ifndef GAME_PARTITION_H 
#define GAME_PARTITION_H 

#include "../board.h"
#include "../tile.h"

#include "../simulation/snapshot.h"
#include "../openai/nlohmann/json.hpp"


#include <vector>
#include <unordered_map>
#include <tuple>
#include <functional>
#include <iostream>

using namespace std;
using json = nlohmann::json;

struct hash_tuple {
    template <class T>
    std::size_t operator () (const T &tuple) const {
        auto hash1 = std::hash<int>{}(std::get<0>(tuple));
        auto hash2 = std::hash<int>{}(std::get<1>(tuple));
        auto hash3 = std::hash<int>{}(std::get<2>(tuple));
        auto hash4 = std::hash<int>{}(std::get<3>(tuple));
        return hash1 ^ (hash2 << 1) ^ (hash3 << 2) ^ (hash4 << 3); // Simple hash combination
    }
};

class GamePartition {
public:
    static constexpr int NUM_GAME_PARTITIONS = 10;
    
    GamePartition(); 
    ~GamePartition();

    void update(Snapshot* snapshot, char winner);
    json toJson() const;

private:
    double** tile_weights;
    unordered_map<tuple<int, int, int, int>, double, hash_tuple> tile_relation_weights;

    double num_disk_parity;
    double t_disk_parity_dev;

    double t_legal_move_ratio_mean;
    double t_legal_move_ration_dev;
};


#endif
