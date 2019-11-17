#pragma once

// #include "player.h"
#include <string>

using namespace std;

class AI_Player {
   public:
    int id;
    int wins;
    AI_Player(); 
    AI_Player(int ai_id, int current_wins);
    int GetNextMove(string board, int opponent_id);
    void AddWin();
    int GetId();
};
