#pragma once
class HumanPlayer {
   public:
    int id;
    int wins;
    HumanPlayer(int h_id, int current_wins);
    int GetNextMove();
    void AddWin();
    int GetId();
};
