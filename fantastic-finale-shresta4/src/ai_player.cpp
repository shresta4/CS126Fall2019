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
	// if they have 4 in a row, try to block by putting the last remaining one 

	// if they have 3 in a row, try to block 

	// if u have 0, then place in the middle somewhere 

	// if you have 1, place next to it 
	// same w/ 2 
	// same w/ 3

	// if you have 4, place another one somewhere else 

	// if ^^ that gives an invalid move, pick next available piece 
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