#include "../include/board.h"

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

int Board::BOARD_SIZE = 12;

Board::Board() : g_board(), curr_turn_player(), n_x_tiles(), n_o_tiles(), allowed_moves() {}

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
        
        for (int j = 0; j < this->BOARD_SIZE; j++) {
            buffer >> curr_tile_p;
            this->g_board[i][j] = new Tile(i, j, curr_tile_p);

            if (curr_tile_p == 'X') 
                n_x_tiles++;
            else if (curr_tile_p == 'O')
                n_o_tiles++;
        }

    }

    this->calculateBoardMoves(this->curr_turn_player);


}

Board::~Board() {
    for (int i = 0; i < this->BOARD_SIZE; i++) {
        for (int j = 0; j < this->BOARD_SIZE; j++) {
            delete this->g_board[i][j];
        } 
        delete [] this->g_board[i];
    }

    unordered_set<Move*>::iterator it;
    for (it = allowed_moves->begin(); it != allowed_moves->end(); ++it) 
        delete *(it);

    delete [] allowed_moves;
}

char Board::getCurrTurnPlayer() {
    return this->curr_turn_player;
}

void Board::calculateBoardMoves(char player) {

    this->allowed_moves = new unordered_set<Move*>();
    
    Tile* curr_tile;
    Move* new_move;
    for (int i = 0; i < BOARD_SIZE; i++) {

        for (int j = 0; j < BOARD_SIZE; j++) {
            curr_tile = g_board[i][j];

            if (!curr_tile->isOccupied() || !curr_tile->isPlayerOcc(player)) 
                continue;

            // Check Up potential
            new_move = checkBoardUp(g_board, BOARD_SIZE, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check down potential move
            new_move = checkBoardDown(g_board, BOARD_SIZE, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check left poetential move
            new_move = checkBoardLeft(g_board, BOARD_SIZE, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);
            
            // Check right poetential move
            new_move = checkBoardRight(g_board, BOARD_SIZE, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check left upper diagonal poetential move
            new_move = checkBoardLUD(g_board, BOARD_SIZE, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check right upper diagonal poetential move
            new_move = checkBoardRUD(g_board, BOARD_SIZE, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check left down diagonal poetential move
            new_move = checkBoardLDD(g_board, BOARD_SIZE, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check right down diagonal poetential move
            new_move = checkBoardRDD(g_board, BOARD_SIZE, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

        }

    }
    
    this->n_allowed_moves = allowed_moves->size();
}

Board* Board::copyBoard() {

    Board* n_board = new Board();

    Tile*** n_g_board = new Tile**[BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++) {
        n_g_board[i] = new Tile*[BOARD_SIZE];
        for (int j = 0; j < BOARD_SIZE; j++) {
            n_g_board[i][j] = new Tile(this->g_board[i][j]);
        }
    }

    n_board->g_board = n_g_board;
    n_board->curr_turn_player = this->curr_turn_player;

    n_board->n_o_tiles = this->n_o_tiles;
    n_board->n_x_tiles = this->n_x_tiles;

    return n_board;
}

void Board::makeMove(Move* n_move) {

}
