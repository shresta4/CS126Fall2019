#include "ai_player.h"
#include <iostream>

using namespace std;

AI_Player::AI_Player() {
    id = "computer";
    piece = 'X';
    wins = 0;
}

AI_Player::AI_Player(string i, char p, int current_wins) {
    id = i;
    piece = p; 
    wins = current_wins;
}

int AI_Player::GetNextMove(
    string board, int opponent_piece, char EMPTY_SPACE) {  // currently returns next available move
    for (int i = 0; i < board.size(); i++) {
        if (board[i] == EMPTY_SPACE) {
            cout << "AI placing piece at " << i << endl;
            return i;
        }
    }
    return -1;
}

void AI_Player::AddWin() { wins++; }