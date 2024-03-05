#include "../include/eval_board.h"
#include "../include/board.h"
#include "../include/tile.h"

static double DISK_PARITY_WEIGHT = 1.0;
static double MOBILITY_WEIGHT = 2.0;
static double CORNER_OCCUPANCY_WEIGHT = 5.0;
static double STABILITY_WEIGHT = 3.0;
static double EDGE_OCCUPANCY_WEIGHT = 2.5;

static double TILE_EVAL_BOARD[Board::BOARD_SIZE][Board::BOARD_SIZE]  {
    {100, -30, 6, 2, 2, 2, 2, 2, 2, 6, -30, 100}, 
    {-30, -50, 0, 0, 0, 0, 0, 0, 0, 0, -50, -30}, 
    {6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6}, 
    {-30, -50, 0, 0, 0, 0, 0, 0, 0, 0, -50, -30}, 
    {100, -30, 6, 2, 2, 2, 2, 2, 2, 6, -30, 100}
};

static int CORNER_INDS[4][2] = {
    {0,0}, {0, Board::BOARD_SIZE},
    {Board::BOARD_SIZE, 0}, {Board::BOARD_SIZE, Board::BOARD_SIZE}
};



double calcStaticTileScore(Board* e_board, char player);


// minimize player's moves and maximizes our moves
// want a placement eval static array 
double evaluateBoard(Board* e_board, char opt_player) {

    int move_num = 1 + e_board->getNumXTiles() + e_board->getNumOTiles();
    bool is_u_board = opt_player == e_board->getCurrTurnPlayer();

    // User's score 
    int u_disk_parity = opt_player == 'X' ? 
        e_board->getNumXTiles() : e_board->getNumOTiles();
    double u_static_tile_score = calcStaticTileScore(e_board, opt_player);
    
    int num_moves = (e_board->getAllowedMoves())->size();



    return 0;

}

double calcStaticTileScore(Board* e_board, char player) {

    double score = 0;
    Tile* curr_tile;
    Tile*** g_board = e_board->getGameBoard();
    for (int i = 0; i < Board::BOARD_SIZE; i++) {
        for (int j = 0; j < Board::BOARD_SIZE; j++) {
            curr_tile = g_board[i][j];

            if (curr_tile->getPlayerOcc() != player) continue;

            score += TILE_EVAL_BOARD[i][j]; 
        }
    }

    return score;

}


