#ifndef GAME_PARTITION_H 
#define GAME_PARTITION_H 

#include "../board.h"

class GamePartition {
public:
    static constexpr NUM_GAME_PARTITIONS = 10;
    GamePartition();
    ~GamePartition();


private:
    double tile_weights[Board::BOARD_SIZE][Board::BOARD_SIZE];
    double tile_relation_weights[Board::BOARD_SIZE * Board::BOARD_SIZE][Board::BOARD_SIZE * Board::BOARD_SIZE];

    double t_disk_parity_mean;
    double t_disk_parity_dev;

    double t_legal_move_ratio_mean;
    double t_legal_move_ration_dev;
};


#endif
