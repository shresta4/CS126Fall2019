#pragma once

#include <string>
#include <vector>
#include "ai_player.h"
#include "human_player.h"

using namespace std;
constexpr int BOARD_SIZE = 19;
constexpr int GOAL = 5;
constexpr char EMPTY_SPACE = '.';
// string tie_code = "Tie.";
// string no_result = "No result.";

class GomokuBoard {
   public:
    string board;
    vector<vector<int>> lookup;
    AI_Player ai;
    HumanPlayer human; 

    GomokuBoard();  // empty board
    GomokuBoard(string stored_board, AI_Player a,
                HumanPlayer h);                    // resume game stored in json file
    // void WriteBoardToJson(string json_file);  // saves game
    void GenerateLookupTable();               // creates table of all possible
                                              // winning combinations
    bool PlacePiece(int loc,
                    char player_piece);  // places piece, B = X (1), W = O (0),
                                     // false iff invalid move
    string GetWinner();
    bool PlayerWins(char player_piece);
    friend ostream &operator<<(ostream &output,
                               const GomokuBoard &gb);  // display
    // evaluate state of game method
};