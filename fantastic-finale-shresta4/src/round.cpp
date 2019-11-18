#include "round.h"
#include <iostream>
#include "gomoku_board.h"

using namespace std;

Round::Round(AI_Player a, HumanPlayer h, GomokuBoard g) {
    ai = a;
    human = h;
    gb = g;
    current_player_id = 0;
}
void Round::PlayRound() {
    while (gb.GetWinner() == NO_RESULT) {
        if (current_player_id == ai.GetId()) {
            int potential_move = ai.GetNextMove(gb.board, human.GetId());
            gb.PlacePiece(potential_move, current_player_id);
            current_player_id = human.GetId();
        } else {
            int potential_move = human.GetNextMove();
            gb.PlacePiece(potential_move, current_player_id);
            current_player_id = ai.GetId();
        }
        cout << gb;
    }
    int win_status = gb.GetWinner();
    if (win_status == TIE_CODE) {
        cout << "Round over. Result: Tie." << endl;
    } else if (win_status = ai.GetId()) {
        cout << "Round over. Result: Player " << ai.GetId() << " won.";
    } else {
        cout << "Round over. Result: Player " << human.GetId() << " won.";
    }
}