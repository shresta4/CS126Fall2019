#pragma once

#include <string>
#include <vector>

constexpr int BOARD_SIZE = 19;
constexpr int GOAL = 5;
constexpr char EMPTY_SPACE = '.';

using namespace std;

class AI_Player {
   public:
    string id;
    char piece;
    int wins;
    int best_move = 50;
    char opp_piece;
    vector<vector<int>> lookup;
    AI_Player();
    AI_Player(string i, char p, int current_wins);
    int GetNextMove(string board, int opponent_piece, char EMPTY_SPACE);
    void AddWin();
    int AI_Player::BasicStrategy(string board, int opponent_piece);
    int AI_Player::BestChancePosition(string board, int opponent_piece);
    int AI_Player::Minimax(string board, char player, int depth,
                           bool maximizing_player, char opponent);
    int AI_Player::HeuristicCalculator(string board, char player,
                                       char opponent);
    string AI_Player::MakeTemporaryMove(string board, char player,
                                        int position);
    vector<int> AI_Player::NextMoves(string board, char player, char opponent); 
    void AI_Player::GenerateLookupTable();
};
