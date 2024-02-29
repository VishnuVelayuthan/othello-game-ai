#include "../include/board.h"

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

int Board::BOARD_SIZE = 12;

Board::Board(std::string file_name) {

    ifstream infile = std::ifstream(file_name);

    if (!infile) {
        std::runtime_error("Input file does not exist");
    }

    string line;
    istringstream buffer;


    // read which player's turn 
    getline(infile, line);
    buffer = istringstream(line);
    buffer >> this->curr_turn_player;

    // read timings left
    double x_time;
    double o_time;
    getline(infile, line);
    buffer = istringstream(line);
    buffer >> x_time >> o_time;

    // Read board into 2D Tile Array
    this->g_board = new Tile**[this->BOARD_SIZE];
    
    char curr_tile_p;
    for (int i = 0; i < this->BOARD_SIZE; i++) {
        getline(infile, line);
        buffer = istringstream(line);
        this->g_board[i] = new Tile*[this->BOARD_SIZE];
        
        string::const_iterator li_it = line.begin();
        for (int j = 0; j < this->BOARD_SIZE; j++) {
            // curr_tile_p = *(li_it);
            buffer >> curr_tile_p;
            this->g_board[i][j] = new Tile(i, j, curr_tile_p);
            ++li_it;
        }

    }

}

Board::~Board() {
    for (int i = 0; i < this->BOARD_SIZE; i++) {
        for (int j = 0; j < this->BOARD_SIZE; j++) {
            delete this->g_board[i][j];
        } 
        delete [] this->g_board[i];
    }
}

char Board::getCurrTurnPlayer() {
    return this->curr_turn_player;
}

Board* Board::makeMove(char move) {
    return nullptr;
}