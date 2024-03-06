#ifndef GAME_PARTITION_H 
#define GAME_PARTITION_H 

#include "../board.h"
#include "../tile.h"

#include "../simulation/snapshot.h"


#include <vector>
#include <unordered_map>
#include <tuple>
#include <functional>
#include <iostream>

using namespace std;

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
    GamePartition(){
        tile_weights = new double*[Board::BOARD_SIZE];
        for (int i = 0; i < Board::BOARD_SIZE; i++) {
            tile_weights[i] = new double[Board::BOARD_SIZE];
        }
        
    };
    ~GamePartition() {
        for (int i = 0; i < Board::BOARD_SIZE; i++) {
            delete tile_weights[i]; 
        }
        delete [] tile_weights;
    };

    void update(Snapshot* snapshot, char winner) {
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

        cout << "---------------------------------" << endl;
        for (auto it = tile_relation_weights.begin(); it != tile_relation_weights.end(); ++it) 
             cout << "Key: " << get<0>(it->first) << get<1>(it->first) << get<2>(it->first) << "  Value: " << it->second << endl;


    };

private:
    double** tile_weights;
    unordered_map<tuple<int, int, int, int>, double, hash_tuple> tile_relation_weights;

    double num_disk_parity;
    double t_disk_parity_dev;

    double t_legal_move_ratio_mean;
    double t_legal_move_ration_dev;
};


#endif
