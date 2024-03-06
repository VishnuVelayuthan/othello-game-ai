#include "../../include/simulation/simulation.h"
#include "../../include/board.h"


SnapShots* playGame(Player* x, Player* o, bool is_record_o) {

    x->setPlayerSymbol('X');
    o->setPlayerSymbol('O');

    Board* game_board = new Board("input-files/03-basic-start.txt");
    
    int MAX_MOVES = Board::BOARD_SIZE * Board::BOARD_SIZE - Board::N_STARTING_PIECES;
    int MOVES_PER_SNAP = MAX_MOVES / (GamePartition::NUM_GAME_PARTITIONS);

    SnapShots* game_data = new Snapshots();

    int completed_move = 0;
    int x_completed_move = 0;
    int o_completed_move = 0;
    Move* curr_move;
    while (game_board->getNumOTiles() + game_board->getNumOTiles() != Board::BOARD_SIZE * Board::BOARD_SIZE) {

        // first o plays
        curr_move = o->play(game_board);
        if (curr_move) {
            game_board->makeMove(curr_move);
            completed_move++;    
            o_completed_move++;
        }

        if (completed_move % MOVES_PER_SNAP == is_record_o && completed_move != is_record_o)
            game_data.add(completed_move / MOVES_PER_SNAP, game_board);

        if (completed_move == MAX_MOVES)
            break;

        // second x plays
        curr_move = x->play(game_board);
        if (curr_move) {
            game_board->makeMove(curr_move);
            completed_move++;    
            x_completed_move++;
        }

        if (completed_move % MOVES_PER_SNAP == is_record_o && is_record_o != is_record_o)
            game_data->add(completed_move / MOVES_PER_SNAP, game_board);

        if (completed_move == MAX_MOVES)
            break;
        
    }
 
    game_data->add(NUM_GAME_PARTITIONS, game_board);

    int n_x_ti = board->getNumXTiles();
    int n_o_ti = board->getNumOTiles();

    if (n_x_ti == n_o_ti)
        game_data->setWinner('D');
    else 
        game_data->setWinner(n_o_ti > n_x_ti ? 'O' : 'X');

    delete game_board;
    return game_data;
}
