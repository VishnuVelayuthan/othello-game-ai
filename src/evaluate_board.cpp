#include "../include/eval_board.h"
#include "../include/board.h"
#include "../include/tile.h"
#include "../include/evaluate/game_partition.h"
#include "../include/evaluate/game_partition_json.h"
#include "../include/openai/nlohmann/json.hpp"

static double DISK_PARITY_WEIGHT = 1.0;
static double MOBILITY_WEIGHT = 2.0;
static double CORNER_OCCUPANCY_WEIGHT = 5.0;
static double STABILITY_WEIGHT = 3.0;
static double EDGE_OCCUPANCY_WEIGHT = 2.5;

static int MOVE_BRACKET = (Board::BOARD_SIZE * Board::BOARD_SIZE - 8) / GamePartition::NUM_GAME_PARTITIONS;

static GamePartition* game_partitions[GamePartition::NUM_GAME_PARTITIONS];

void initializeGamePartition() {
    nlohmann::json gp_json = nlohmann::json::parse(GAME_PARTITION_JSON);
    nlohmann::json stats_json = nlohmann::json::parse(GAME_STATS_JSON);

    int i = 0; // not the best code i've written 
    for (const auto& jPartition : gp_json) {
        GamePartition* partition = GamePartition::fromJson(jPartition);
        game_partitions[i] = partition;
        i++;
    }

    // i = 0;
    // for (const auto& j_stats : stats_json) {
    //     game_partition[i]
    // }

}

// minimize player's moves and maximizes our moves
// want a placement eval static array 
double evaluateBoard(Board* e_board, char opt_player) {

    int move_num = 1 + e_board->getNumXTiles() + e_board->getNumOTiles();
    bool is_u_board = opt_player == e_board->getCurrTurnPlayer();

    // User's score 
    int u_disk_parity = opt_player == 'X' ? 
        e_board->getNumXTiles() : e_board->getNumOTiles();
    
    int num_legal_moves = (e_board->getAllowedMoves())->size();
    
    GamePartition* curr_gp = game_partitions[move_num / MOVE_BRACKET];

    // tile z-score 
    double dp_z = curr_gp->calcDPZ(u_disk_parity);
    
    // legal moves z-score 
    double lm_z = curr_gp->calcLMZ(num_legal_moves);
    
    // tile score 
    double tile_score = curr_gp->calcTileScore(e_board, opt_player);
    
    // tile relation score 
    double tile_relation_score = curr_gp->calcTileRelationScore(e_board, opt_player);


    return 0;

}
