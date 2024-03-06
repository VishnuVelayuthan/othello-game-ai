#include "../../include/simulation/play_game.h"
#include "../../include/board.h"


SnapShots* playGame(Player* x, Player* o) {

    x->setPlayerSymbol('X');
    o->setPlayerSymbol('O');

    Board* game_board = new Board("input-files/03-basic-start.txt");
    
    int MAX_MOVES = Board::BOARD_SIZE * Board::BOARD_SIZE - Board::N_STARTING_PIECES;

    int completed_move = 0;
    Move* curr_move;
    while (game_board->getNumOTiles() + game_board->getNumOTiles() != Board::BOARD_SIZE * Board::BOARD_SIZE) {

        // first o plays
        curr_move = o->play(game_board);
        if (curr_move) {
            game_board->makeMove(curr_move);
            move++;    
        }

        curr_move = x->play(game_board);
        if (curr_move) {
            game_board->makeMove(curr_move);
            move++;    
        }
        
        if )
    }


}
