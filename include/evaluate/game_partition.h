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

    static GamePartition* fromJson(const nlohmann::json& j);

    void setTileWeight(int i, int j, double weight);
    void insertTileRelation(tuple<int,int,int,int> key, double weight);

    void aggregateData(GamePartition* second_gp); 

    double calcDPZ(int u_disk_parity);
    double calcLMZ(int num_legal_moves);
    double calcNMZ(int num_moves);

    double calcTileScore(Board* e_board, char player);
    double calcTileRelationScore(Board* e_board, char player);

    inline void setDPAvg(double dp_avg) {this->disk_parity_avg=dp_avg;};
    inline void setDPDev(double dp_dev){this->disk_parity_dev=dp_dev;};

    inline void setLMAvg(double lm_avg){this->legal_move_avg=lm_avg;};
    inline void setLMDev(double lm_dev){this->legal_move_dev=lm_dev;};

    inline void setNMAvg(double nm_avg){this->n_moves_avg=nm_avg;};
    inline void setNMDev(double nm_dev){this->n_moves_dev=nm_dev;};

private:
    double** tile_weights;
    unordered_map<tuple<int, int, int, int>, double, hash_tuple> tile_relation_weights;

    double disk_parity_avg;
    double disk_parity_dev;

    double legal_move_avg;
    double legal_move_dev;

    double n_moves_avg;
    double n_moves_dev;
};


#endif
