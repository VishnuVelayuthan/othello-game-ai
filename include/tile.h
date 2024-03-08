#ifndef TILE_H 
#define TILE_H 

#include "./openai/nlohmann/json.hpp"

class Tile{
public:
    Tile(int row, int col, char player_occ) {
        this->i_row = row;
        this->i_col = col;
        this->c_col = (97 + col);
        this->p_occ = player_occ;
    };

    Tile(Tile* o_tile) {
        this->i_row = o_tile->i_row;
        this->i_col = o_tile->i_col;
        this->c_col = (97 + o_tile->i_col);
        this->p_occ = o_tile->p_occ;
    }

    inline int getIrow() {return this->i_row;};
    inline int getIcol() {return this->i_col;};
    inline char getCcol() {return this->c_col;};

    inline char getPlayerOcc() {return this->p_occ;};
    inline void setPlayerOcc(char player_occ) {this->p_occ = player_occ;};

    inline bool isOccupied() {return (this->p_occ != '.');};
    inline bool isPlayerOcc(char player) {return this->p_occ == player;};

    inline nlohmann::json toJson() {
        nlohmann::json j;
        j.emplace("i_row", i_row);
        j.emplace("i_col", i_col); 
        j.emplace("c_col", c_col);
        j.emplace("p_occ", p_occ);
        return j;
    };

private:
    int i_row; // number from 1 - 12
    int i_col; // number from 1 - 12
    char c_col; // letter from a - l

    char p_occ;
};

#endif
