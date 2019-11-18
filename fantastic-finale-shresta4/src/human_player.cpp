#include "human_player.h"
#include <iostream>
#include <string>

using namespace std;

HumanPlayer::HumanPlayer() {
    id = "user";
    piece = 'O';
    wins = 0;
}

HumanPlayer::HumanPlayer(string i, char p, int current_wins) {
    id = i;
    piece = p;
    wins = current_wins;
}

int HumanPlayer::GetNextMove() {
    cout << endl << id << " turn. Enter move: ";
    int move;
    try {
        cin >> move;
    } catch (...) {
        return -1;
    }
    return move;
}

void HumanPlayer::AddWin() { wins++; }