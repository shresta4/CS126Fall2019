#include "ai_player.h"
#include "gomoku_board.h"

AI_Player::AI_Player(int ai_id, int current_wins) {
    id = ai_id;
    wins = current_wins;
}

int AI_Player::GetNextMove(string board, int opponent_id) { // currently returns next available move
    for (int i = 0; i < board.size(); i++) {
        if (board[i] == EMPTY_SPACE) {
            return i; 
		}
    }
	return -1; 
}

void AI_Player::AddWin() {
	wins++; 
}

int AI_Player::GetId() {
	return id; 
}