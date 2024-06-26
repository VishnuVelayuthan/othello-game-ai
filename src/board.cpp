#include "../include/board.h"

#include "./flip_board_utility.h"
#include "./check_board_utility.h"

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

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
    double curr_time;
    double opp_time;
    getline(infile, line);
    buffer = istringstream(line);
    buffer >> curr_time >> opp_time;

    if (curr_turn_player == 'X')
        this->curr_turn_time = curr_time;
    else 
        this->curr_turn_time = opp_time;

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

    this->allowed_moves = this->calculateBoardMoves(this->curr_turn_player);


}

Board::~Board() {
    for (int i = 0; i < this->BOARD_SIZE; i++) {
        for (int j = 0; j < this->BOARD_SIZE; j++) {
            delete this->g_board[i][j];
        } 
        delete [] this->g_board[i];
    }

    delete g_board;

    for (Move* move : *(allowed_moves)) 
        delete move;

    allowed_moves->clear();
    delete allowed_moves;
}

void Board::updateXOtileCount() {
    this->n_o_tiles = 0;
    this->n_x_tiles = 0;

    Tile* curr_tile;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            curr_tile = this->g_board[i][j];
            if (!curr_tile->isOccupied()) continue;

            if (curr_tile->getPlayerOcc() == 'X') n_x_tiles++;
            else n_o_tiles++;
        }
    }
}




std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* Board::calculateBoardMoves(char player) {

    std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>*
        allowed_moves = new unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>();
    
    Tile* curr_tile;
    Move* new_move;
    for (int i = 0; i < BOARD_SIZE; i++) {

        for (int j = 0; j < BOARD_SIZE; j++) {
            curr_tile = g_board[i][j];

            if (!curr_tile->isOccupied() || !curr_tile->isPlayerOcc(player)) 
                continue;

            // Check Up potential
            new_move = checkBoardUp(g_board, BOARD_SIZE, allowed_moves, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check down potential move
            new_move = checkBoardDown(g_board, BOARD_SIZE, allowed_moves, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check left poetential move
            new_move = checkBoardLeft(g_board, BOARD_SIZE, allowed_moves, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);
            
            // Check right poetential move
            new_move = checkBoardRight(g_board, BOARD_SIZE, allowed_moves, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check left upper diagonal poetential move
            new_move = checkBoardLUD(g_board, BOARD_SIZE, allowed_moves, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check right upper diagonal poetential move
            new_move = checkBoardRUD(g_board, BOARD_SIZE, allowed_moves, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check left down diagonal poetential move
            new_move = checkBoardLDD(g_board, BOARD_SIZE, allowed_moves, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);

            // Check right down diagonal poetential move
            new_move = checkBoardRDD(g_board, BOARD_SIZE, allowed_moves, curr_tile, player);
            if (!new_move->isNull())
                allowed_moves->insert(new_move);
        }

    }
    
    this->n_allowed_moves = allowed_moves->size();

    return allowed_moves;
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

    if (n_move == nullptr) {
        this->flipPlayer();
        this->updateAllowedMoves();
        return;
    }

    const  std::vector<FlipType>& n_move_fts = n_move->getFlipTypes();

    FlipType curr_ft;
    for (int i = 0; i < n_move_fts.size(); i++) {
        curr_ft = n_move_fts[i];

        switch (curr_ft){
            case FlipType::UP:            
                flipPiecesUp(this->g_board, BOARD_SIZE, n_move);
                break;
            case FlipType::DOWN:
                flipPiecesDown(this->g_board, BOARD_SIZE, n_move);
                break;
            case FlipType::LEFT:
                flipPiecesLeft(this->g_board, BOARD_SIZE, n_move);
                break;
            case FlipType::RIGHT:
                flipPiecesRight(this->g_board, BOARD_SIZE, n_move);
            case FlipType::LUD:
                flipPiecesLUD(this->g_board, BOARD_SIZE, n_move);
                break;
            case FlipType::RUD:
                flipPiecesRUD(this->g_board, BOARD_SIZE, n_move);
                break;
            case FlipType::LDD:
                flipPiecesLDD(this->g_board, BOARD_SIZE, n_move);
                break;
            default:
                flipPiecesRDD(this->g_board, BOARD_SIZE, n_move);
                break;
        }

    }

    this->curr_turn_player = curr_turn_player == 'X' ? 'O' : 'X';

    this->updateXOtileCount();
    
    // rewmove late 
    // for (Move* move : *allowed_moves) 
    //     delete move;
    // allowed_moves->clear();
    // delete allowed_moves;

    updateAllowedMoves();
}

Move* Board::findMove(string move_str) {
    int r; 
    int c; 

    move_str.erase(remove(move_str.begin(), move_str.end(), '('), move_str.end());
    move_str.erase(remove(move_str.begin(), move_str.end(), ')'), move_str.end());
    std::istringstream iss(move_str);
    char delimiter; 
    iss >> r >> delimiter >> c;

    for (Move* move : *allowed_moves) 
        if (move->isMove(r,c))
            return move;

    return nullptr;
}

char Board::getCurrTurnPlayer() {
    return this->curr_turn_player;
}

string Board::toString() {
    string board_string = "";

    Tile* curr_tile;
    for (int i = 0; i < BOARD_SIZE; i++) {

        for (int j = 0; j < BOARD_SIZE; j++) {
            curr_tile = g_board[i][j];

            board_string += curr_tile->getPlayerOcc();
        }

        board_string += "\u000A";
    }

    return board_string;
}

string Board::allowedMovesToString() {
    string m_str = "";
    for (Move* move : *allowed_moves) 
        m_str += move->toString() + " ";
    return m_str;
}

void Board::flipPlayer() {
    this->curr_turn_player = curr_turn_player == 'X' ? 'O' : 'X';
}

void Board::updateAllowedMoves() {
    this->allowed_moves = this->calculateBoardMoves(curr_turn_player);
}

char Board::whoWon() {
    if (n_o_tiles > n_x_tiles + 1) 
        return 'O';
    else if (n_o_tiles < n_x_tiles + 1) 
        return 'X';
    else 
        return 'D';
}

bool Board::isTerminalBoard() {
    int num_curr_moves = allowed_moves->size();

    if (num_curr_moves == 0) {
        std::unordered_set<Move*, std::hash<Move*>, MovePointerDefEqual>* next_moves;
        next_moves = this->calculateBoardMoves(curr_turn_player == 'X' ? 'O' : 'X');

        int next_num_legal_moves = next_moves->size();

        next_moves->clear();
        delete next_moves;

        if (next_num_legal_moves == 0)
            return true;
    }

    return false;
}


nlohmann::json Board::toJson() const {
    nlohmann::json j;

    // Convert board state to JSON
    nlohmann::json boardJson = nlohmann::json::array();
    for (int i = 0; i < Board::BOARD_SIZE; ++i) {
        nlohmann::json rowJson = nlohmann::json::array();
        for (int j = 0; j < Board::BOARD_SIZE; ++j) {
            // Assuming Tile has a toJson() method that returns nlohmann::json
            rowJson.push_back(this->g_board[i][j]->toJson());
        }
        boardJson.push_back(rowJson);
    }
    j["board"] = boardJson;

    // Serialize other attributes
    j["curr_turn_player"] = std::string(1, this->curr_turn_player);
    j["n_x_tiles"] = this->n_x_tiles;
    j["n_o_tiles"] = this->n_o_tiles;

    // Assuming you have a way to serialize allowed_moves if necessary
    // This part is omitted for brevity as it depends on the Move class implementation

    return j;
}
