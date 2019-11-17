#pragma once

#include "ai_player.h"
#include "gomoku_board.h"
#include "human_player.h"

using namespace std;

class Round {
    AI_Player ai;
    HumanPlayer human;
    GomokuBoard gb;
    int current_player_id;

    Round(AI_Player a, HumanPlayer h, GomokuBoard g);
    void PlayRound();
};
