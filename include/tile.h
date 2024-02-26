
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

    int getIrow() {return this->i_row;};
    int getIcol() {return this->i_col;};
    char getCcol() {return this->c_col;};

    char getPlayerOcc() {return this->p_occ;};
    void setPlayerOcc(char player_occ) {this->p_occ = player_occ;};
    bool isOccupied() {return (this->p_occ != '.');};

private:
    int i_row; // number from 1 - 12
    int i_col; // number from 1 - 12
    char c_col; // letter from a - l

    char p_occ; 

};

#endif
