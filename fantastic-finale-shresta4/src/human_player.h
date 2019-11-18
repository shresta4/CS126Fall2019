#pragma once

#include <string>

using namespace std; 

class HumanPlayer {
   public:
    string id;
    char piece;
    int wins;
    HumanPlayer();
    HumanPlayer(string i, char p, int current_wins);
    int GetNextMove();
    void AddWin();
};
