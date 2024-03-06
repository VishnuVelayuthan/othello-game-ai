#ifndef PLAY_GAME_H
#define PLAY_GAME_H

#include "./player.h"
#include "./snapshots.h" 

#include <string>

Snapshots* playGame(Player* x, Player* o, bool is_record_o);

void serializeSnapshots(Snapshots* game_data, std::string name);

#endif
