#ifndef PLAY_GAME_H
#define PLAY_GAME_H

#include "./player.h"
#include "./snapshots.h" 
#include "../evaluate/game_partition.h"

#include <string>

Snapshots* playGame(Player* x, Player* o, bool is_record_o);

void serializeSnapshots(Snapshots* game_data, int game_num);
void csvifySnapshots(Snapshots* game_data);
void serializeGamePartitions(GamePartition** g_p, int game_num);

GamePartition** deserializeGamePartitionArr(json j);

#endif
