#ifndef GAME_PARTITION_H 
#define GAME_PARTITION_H 

#include "../board.h"
#include "./tile.h"

#include <vector>
#include <unordered_map>
#include <tuple>

using namespace std;

class GamePartition {
public:
    static constexpr NUM_GAME_PARTITIONS = 10;
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
        Board* g_board = snapshot->g_board;

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
                            tuple<int, int, int, int> key = make_tuple<int, int, int, int>(i, j, h, k);
                            if (winner == 'D')
                                tile_relation_weights[key] = tile_relation_weights[key] + 0.5;
                            else 
                                tile_relation_weights[key] = tile_relation_weights[key] + 
                                    lower_tile == winner ? 1 : -1;
                        }
                    }
                }
            }
        }
    };

private:
    double** tile_weights;
    unordered_map<tuple<int, int, int, int>, double> tile_relation_weights;

    double num_disk_parity;
    double t_disk_parity_dev;

    double t_legal_move_ratio_mean;
    double t_legal_move_ration_dev;
};


#endif
