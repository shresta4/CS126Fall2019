#include "human_player.h"
#include <iostream>
#include <sstream>
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
    cout << endl << id << " turn. (-128 to save and end game.) Enter move: ";
    string str_move;

    int move;
    try {
        getline(cin, str_move, '\n');
        stringstream stream_str_move(str_move);
        stream_str_move >> move;
        // cin >> move;
    } catch (...) {
        return -1;
    }
    return move;
}

void HumanPlayer::AddWin() { wins++; }