#pragma once
class HumanPlayer {
    int id;
    int wins;
    HumanPlayer(int h_id, int current_wins);
    int GetNextMove();
    void AddWin();
};
