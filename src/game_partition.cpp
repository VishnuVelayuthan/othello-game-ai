#include "../include/evaluate/game_partition.h"

#include <sstream>
#include <cmath>

using json = nlohmann::json;
using namespace std;


GamePartition::GamePartition() {
    this->tile_weights = new double*[Board::BOARD_SIZE];
    for (int i = 0; i < Board::BOARD_SIZE; i++) {
        this->tile_weights[i] = new double[Board::BOARD_SIZE];
    }
};

GamePartition::~GamePartition() {
    for (int i = 0; i < Board::BOARD_SIZE; i++) {
        delete this->tile_weights[i]; 
    }
    delete [] this->tile_weights;
};

json GamePartition::toJson() const {
    json j;

    // Serialize tile_weights
    json weightsJson = json::array();
    for (int i = 0; i < Board::BOARD_SIZE; ++i) {
        json rowJson = json::array();
        for (int j = 0; j < Board::BOARD_SIZE; ++j) {
            rowJson.push_back(tile_weights[i][j]);
        }
        weightsJson.push_back(rowJson);
    }
    j["tile_weights"] = weightsJson;

    // Serialize tile_relation_weights
    json relationWeightsJson = json::object();
    for (const auto& [key, value] : tile_relation_weights) {
        // Convert tuple key to string or suitable format
        std::string keyStr = std::to_string(std::get<0>(key)) + "," +
                             std::to_string(std::get<1>(key)) + "," +
                             std::to_string(std::get<2>(key)) + "," +
                             std::to_string(std::get<3>(key));
        relationWeightsJson[keyStr] = value;
    }
    j["tile_relation_weights"] = relationWeightsJson;

    // Serialize simple variables
    // j["num_disk_parity"] = num_disk_parity;
    // j["t_disk_parity_dev"] = t_disk_parity_dev;
    // j["t_legal_move_ratio_mean"] = t_legal_move_ratio_mean;
    // j["t_legal_move_ratio_dev"] = t_legal_move_ratio_dev;

    return j;
};

void GamePartition::update(Snapshot* snapshot, char winner) {

        if (snapshot == nullptr) 
            return;

        Board* g_board = snapshot->getBoard();

        Tile*** tile_board = g_board->getGameBoard();
        
        // Updating tile weights
        Tile* curr_tile;
        for (int i = 0; i < Board::BOARD_SIZE; i++) {

            for (int j = 0; j < Board::BOARD_SIZE; j++) {
                curr_tile = tile_board[i][j];

                if (!curr_tile->isOccupied()) 
                    continue;
                else if (curr_tile->getPlayerOcc() == winner)
                    tile_weights[i][j] = tile_weights[i][j] + 1;
                else 
                    tile_weights[i][j] = tile_weights[i][j] - 1;
            }
            
        }

        // Updating tile relation tile weights 
        Tile* upper_tile;
        Tile* lower_tile;
        for (int i = 0; i < Board::BOARD_SIZE; i++) {
            for (int j = 0; j < Board::BOARD_SIZE; j++) {
                upper_tile = tile_board[i][j];
                if (!upper_tile->isOccupied())
                    continue;

                for (int k = i; k < Board::BOARD_SIZE; k++) {
                    for (int h = j; j < Board::BOARD_SIZE; j++) {
                        lower_tile = tile_board[k][h];

                        if (!lower_tile->isOccupied())
                            continue;
                        else if (lower_tile->getPlayerOcc() == upper_tile->getPlayerOcc()) {
                            tuple<int, int, int, int> key = std::make_tuple(i, j, h, k);
                            if (winner == 'D')
                                tile_relation_weights[key] = tile_relation_weights[key] + 0.5;
                            else {
                                int to_add = lower_tile->getPlayerOcc() == winner ? 1 : -1; 
                                tile_relation_weights[key] = tile_relation_weights[key] + to_add;
                            }
                        }
                    }
                }
            }
        }
    }



GamePartition* GamePartition::fromJson(const nlohmann::json& j) {
        GamePartition* partition = new GamePartition();

        // Assuming tile_weights is already allocated with fixed dimensions
        // and you have a method to set each weight, e.g., setTileWeight(x, y, weight)
        for (int i = 0; i < Board::BOARD_SIZE; ++i) {
            for (int k = 0; k < Board::BOARD_SIZE; ++k) {
                partition->setTileWeight(i, k, j["tile_weights"][i][k]);
            }
        }

        // Deserialize tile_relation_weights
        for (const auto& [key, value] : j["tile_relation_weights"].items()) {
            std::istringstream keyStream(key);
            std::string segment;
            std::vector<int> tupleValues;

            while (std::getline(keyStream, segment, ',')) {
                tupleValues.push_back(std::stoi(segment));
            }

            std::tuple<int, int, int, int> tupleKey = std::make_tuple(tupleValues[0], tupleValues[1], tupleValues[2], tupleValues[3]);
            partition->tile_relation_weights[tupleKey] = value;
        }

        // Deserialize simple variables
        // partition->num_disk_parity = j["num_disk_parity"];
        // partition->t_disk_parity_dev = j["t_disk_parity_dev"];
        // partition->t_legal_move_ratio_mean = j["t_legal_move_ratio_mean"];
        // partition->t_legal_move_ratio_dev = j["t_legal_move_ratio_dev"];
        return partition;
    }

void GamePartition::setTileWeight(int i, int j, double weight) {
    this->tile_weights[i][j] = weight;
}

GamePartition** deserializeJson(nlohmann::json j) {

    GamePartition** game_partitions = new GamePartition*[GamePartition::NUM_GAME_PARTITIONS];

    int g_i = 0;
    GamePartition* curr_gp;
    for (const auto& item : j) {
        curr_gp = new GamePartition();
        // Access the array
        auto array = item["tile_weights"];

        int i = 0;
        for (auto tile_weight_row : array) {
            int j = 0;
            for (double tile_weight : tile_weight_row) {
                curr_gp->setTileWeight(i, j, tile_weight);
                j++;
            }
            i++;  
        }

        // Access the map
        auto map = item["map"];
        for (auto& [key, value] : map.items()) {
            std::cout << key << ": " << value << std::endl;
        }
        
        g_i++;
    }
}


void GamePartition::aggregateData(GamePartition* second_gp) {

    for(int i = 0; i < Board::BOARD_SIZE; i++) {
        for (int j = 0; j < Board::BOARD_SIZE; j++) {
            cout << "  Tile Weights before: " << tile_weights[i][j] << endl;
            this->tile_weights[i][j] += second_gp->tile_weights[i][j];
            cout << "  Tile Weights after: " << tile_weights[i][j] << endl;
        }
    }

    for (auto& pair : this->tile_relation_weights) {
        tile_relation_weights[pair.first] = pair.second + second_gp->tile_relation_weights[pair.first];
    }

    for (auto& pair : second_gp->tile_relation_weights) {
        tile_relation_weights[pair.first] = pair.second + this->tile_relation_weights[pair.first];
    }
}

double GamePartition::calcDPZ(int u_disk_parity) {
    return (u_disk_parity - this->disk_parity_avg) / this->disk_parity_dev;
}

double GamePartition::calcLMZ(int num_legal_moves) {
    return (num_legal_moves - this->legal_move_avg) / this->legal_move_dev;
}

double GamePartition::calcNMZ(int num_moves) {
    return (num_moves - this->n_moves_avg) / this->n_moves_dev;
}

double GamePartition::calcTileScore(Board* e_board, char player) {
    Tile*** g_board = e_board->getGameBoard();

    double score = 0;
    for (int i = 0; i < Board::BOARD_SIZE; i++) {
        for (int j = 0; j < Board::BOARD_SIZE; j++) {
            if (g_board[i][j]->getPlayerOcc() == player) 
                score += tile_weights[i][j];
        }
    }

    return score;
}

double GamePartition::calcTileRelationScore(Board* e_board, char player) {
    Tile*** g_board = e_board->getGameBoard();

    
    Tile* t1;
    Tile* t2;
    tuple<int, int, int, int> key;
    double score = 0;
    double total_score = 0;
    for (const auto& pair : tile_relation_weights) {        
        key = pair.first;
        t1 = g_board[get<0>(key)][get<1>(key)];
        t2 = g_board[get<2>(key)][get<3>(key)];

        if (t1->getPlayerOcc() == t2->getPlayerOcc() && t1->getPlayerOcc() == player)
            score += pair.second; 

        total_score += pair.second;
    }

    return score / total_score;
}
