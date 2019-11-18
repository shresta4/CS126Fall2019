#pragma once

// #include "player.h"
#include <string>

using namespace std;

class AI_Player {
   public:
    string id;
    char piece;
    int wins;
    AI_Player();
    AI_Player(string i, char p, int current_wins);
    int GetNextMove(string board, int opponent_piece, char EMPTY_SPACE);
    void AddWin();
};
