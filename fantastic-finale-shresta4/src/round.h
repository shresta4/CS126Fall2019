#pragma once


#include "gomoku_board.h"


using namespace std;

class Round {
   public:
    AI_Player &ai;
    HumanPlayer &human;
    GomokuBoard &gb;
    string current_player_id;
    Round(AI_Player &a, HumanPlayer &h, GomokuBoard &g);
    void PlayRound();
};
