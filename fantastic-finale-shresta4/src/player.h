#pragma once
#include <string>

using namespace std;

class Player {
    int id;
    int wins;
    void SetId(int given_id) { id = given_id; }
    void ResetWins() { wins = 0; }
    virtual int GetMove(string board, int opponent_id);
    void AddWin() { wins++; }
};