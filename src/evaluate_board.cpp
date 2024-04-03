#include "../include/eval_board.h"
#include "../include/board.h"
#include "../include/tile.h"
#include "../include/evaluate/game_partition.h"
#include "../include/evaluate/game_partition_json.h"
#include "../include/openai/nlohmann/json.hpp"

#include <cmath>
#include <limits>
#include <unordered_set>

using namespace std;

static double DISK_PARITY_WEIGHT = -1.0;
static double LEGAL_MOVE_WEIGHT = 2.0;
static double TILE_SCORE_WEIGHT = 0.5;
static double NUM_MOVES_WEIGHT = 1.0;
static double RELATION_SCORE_WEIGHT = 0.5;

static double MAX_DOUBLE = numeric_limits<double>::max();
static double MIN_DOUBLE = numeric_limits<double>::min();

static int MOVE_BRACKET = (Board::BOARD_SIZE * Board::BOARD_SIZE) / GamePartition::NUM_GAME_PARTITIONS;

static GamePartition* game_partitions[GamePartition::NUM_GAME_PARTITIONS];

void initializeGamePartitions() {
    nlohmann::json gp_json = nlohmann::json::parse(GAME_PARTITION_JSON);
    nlohmann::json stats_json = nlohmann::json::parse(GAME_STATS_JSON);

    int i = 0; // not the best code i've written 
    for (const auto& jPartition : gp_json) {
        GamePartition* partition = GamePartition::fromJson(jPartition);
        game_partitions[i] = partition;
        i++;
    }

    i = 0;
    for (const auto& j_stats : stats_json) {
        game_partitions[i]->setDPAvg(j_stats["mean"]["Tiles"]);
        game_partitions[i]->setLMAvg(j_stats["mean"]["LM"]);
        game_partitions[i]->setNMAvg(j_stats["mean"]["Moves"]);

        game_partitions[i]->setDPDev(j_stats["std"]["Tiles"]);
        game_partitions[i]->setLMDev(j_stats["std"]["LM"]);
        game_partitions[i]->setNMDev(j_stats["std"]["Moves"]);


        // cout << j_stats["std"]["Tiles"] << endl;
        i++;
    }
}

void deleteGamePartitions() {
    for (int i = 0; i < GamePartition::NUM_GAME_PARTITIONS; i++) 
        delete game_partitions[i];
}

// minimize player's moves and maximizes our moves
// want a placement eval static array 
double evaluateBoard(Board* e_board, char opt_player) {

    int move_num = 1 + e_board->getNumXTiles() + e_board->getNumOTiles() - 8;
    bool is_u_x = opt_player == 'X';
    bool is_u_curr = opt_player == e_board->getCurrTurnPlayer();

    // User's score 
    int u_disk_parity = is_u_x ? 
        e_board->getNumXTiles() : e_board->getNumOTiles();
    
    int num_legal_moves = (e_board->getAllowedMoves())->size();

    // case for when current player doesn't have any legal moves
    // get calculate legal moves of next player 
    // if that's equal then go into win or lose condition
    if (num_legal_moves == 0) {
        std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* next_moves;
        next_moves = e_board->calculateBoardMoves(is_u_x ? 'O' : 'X');

        int next_num_legal_moves = next_moves->size();

        next_moves->clear();
        delete next_moves;

        if (next_num_legal_moves == 0) {
            char who_won = e_board->whoWon();
            switch (who_won){
                case 'X':
                    return is_u_x ? MAX_DOUBLE : MIN_DOUBLE;
                case 'Y':
                    return is_u_x ? MIN_DOUBLE : MAX_DOUBLE;
                default:
                    return 0;
            }
    }

        // if original player is not our player then we happy 
        return is_u_curr ? MIN_DOUBLE / 2 : MAX_DOUBLE / 2; 
    }
    
    GamePartition* curr_gp = game_partitions[move_num / MOVE_BRACKET];

    // tile z-score 
    double dp_z = abs(curr_gp->calcDPZ(u_disk_parity));
    // legal moves z-score 
    double lm_z = abs(curr_gp->calcLMZ(num_legal_moves));

    // double nm_z = curr_gp->calcLMZ(moves_num);
    
    // tile score 
    double tile_score = curr_gp->calcTileScore(e_board, opt_player);
    
    // tile relation score 
    double tile_relation_score = curr_gp->calcTileRelationScore(e_board, opt_player);

    // cout << "  Disk Parity: " << dp_z << endl;
    // cout << "  Lm: " << lm_z << endl;
    // cout << "  Tile RS: " << tile_relation_score << endl;
    // cout << "  Tile Sc: " << tile_score << endl;


    return (
        dp_z +
        lm_z * LEGAL_MOVE_WEIGHT + 
        tile_score * TILE_SCORE_WEIGHT + 
        tile_relation_score * RELATION_SCORE_WEIGHT
    );

}
