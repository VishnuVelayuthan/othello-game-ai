
#ifndef TILE_H 
#define TILE_H 

class Tile{
public:
    Tile(int row, int col, char player_occ) {
        this->i_row = row;
        this->i_col = col;
        this->c_col = (97 + col);

        this->p_occ = player_occ;
    };

    inline int getIrow() {return this->i_row;};
    inline int getIcol() {return this->i_col;};
    inline char getCcol() {return this->c_col;};

    inline char getPlayerOcc() {return this->p_occ;};
    inline void setPlayerOcc(char player_occ) {this->p_occ = player_occ;};

    inline bool isOccupied() {return (this->p_occ != '.');};
    inline bool isPlayerOcc(char player) {return this->p_occ == player;};

private:
    int i_row; // number from 1 - 12
    int i_col; // number from 1 - 12
    char c_col; // letter from a - l

    char p_occ;

};

#endif
