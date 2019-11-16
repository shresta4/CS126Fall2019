#include "human_player.h"
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer(int h_id, int current_wins) {
    id = h_id;
    wins = current_wins;
}

int HumanPlayer::GetNextMove() {
    cout << endl << "Player " << id << " turn. Enter move: ";
    int move;
    cin >> move;
    return move;
}

void HumanPlayer::AddWin() { wins++; }