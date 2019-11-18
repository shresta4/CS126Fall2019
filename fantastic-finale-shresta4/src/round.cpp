#include "round.h"
#include <iostream>
#include "gomoku_board.h"

using namespace std;

Round::Round(AI_Player &a, HumanPlayer &h, GomokuBoard &g)
    : ai(a), human(h), gb(g) {
    ai = a;
    human = h;
    gb = g;
    current_player_id = ai.id;
}
void Round::PlayRound() {
    while (gb.GetWinner() == "no_result") {
        if (current_player_id == ai.id) {
            cout << "ai turn"; 
            int potential_move = ai.GetNextMove(gb.board, human.piece, EMPTY_SPACE);
            gb.PlacePiece(potential_move, ai.piece);
            cout << "^^ placed piece by " << current_player_id << endl; 
            current_player_id = human.id;
            cout << current_player_id << endl;
        } else {
            int potential_move = human.GetNextMove();
            gb.PlacePiece(potential_move, human.piece);
            current_player_id = ai.id;
            cout << "human turn, but skipping" << endl; 
            cout << current_player_id << endl; 
        }
        cout << gb;
        cout << "__________________________________________________" << endl; 
    }
    string win_status = gb.GetWinner();
    if (win_status == "tie") {
        cout << "Round over. Result: Tie." << endl;
    } else if (win_status == ai.id) {
        cout << "Round over. Result: Player " << ai.id << " won.";
    } else {
        cout << "Round over. Result: Player " << human.id << " won.";
    }
}