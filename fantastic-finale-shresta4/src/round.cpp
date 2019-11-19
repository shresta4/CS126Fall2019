#include "round.h"
#include <iostream>
#include "gomoku_board.h"

using namespace std;

Round::Round(AI_Player &a, HumanPlayer &h, GomokuBoard &g)
    : ai(a), human(h), gb(g) {
    ai = a;
    human = h;
    gb = g;

    // first player is X
    if (ai.piece == 'X') {
        current_player_id = ai.id;
    } else {
        current_player_id = human.id;
    }
}
void Round::PlayRound() {
    while (gb.GetWinner() == "no_result") {
        cout << "____________________________________________" << endl;
        cout << gb << endl;
        if (current_player_id == ai.id) {
            cout << "ai turn" << endl;
            int potential_move =
                ai.GetNextMove(gb.board, human.piece, EMPTY_SPACE);
            gb.PlacePiece(potential_move, ai.piece);
            current_player_id = human.id;
        } else {
            bool moved = false;
            do {
                int potential_move = human.GetNextMove();
                moved = gb.PlacePiece(potential_move, human.piece);
            } while (!moved);
            current_player_id = ai.id;
            cout << "human turn, but skipping" << endl;
        }
    }
    cout << gb << endl;
    string win_status = gb.GetWinner();
    if (win_status == "tie") {
        cout << "Round over. Result: Tie." << endl;
    } else if (win_status == ai.id) {
        cout << "Round over. Result: Player " << ai.id << " won.";
    } else {
        cout << "Round over. Result: Player " << human.id << " won.";
    }
}