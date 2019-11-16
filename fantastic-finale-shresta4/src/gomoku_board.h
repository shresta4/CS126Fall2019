#pragma once

#include <string>
#include <vector>

using namespace std;
constexpr int BOARD_SIZE = 19;
constexpr int GOAL = 5;

class GomokuBoard {
   public:
    string board;
    vector<vector<int>> lookup;
    int player_1_id;
    int player_0_id;

    GomokuBoard();                            // empty board
    GomokuBoard(string stored_board, int id_1, int id_0);            // resume game stored in json file
    void WriteBoardToJson(string json_file);  // saves game
    void GenerateLookupTable();               // creates table of all possible
                                              // winning combinations
    bool PlacePiece(int loc,
                    int player_id);  // places piece, B = X (1), W = O (0),
                                     // false iff invalid move
    int GetWinner();
    bool PlayerWins(int player_id);
    friend ostream &operator<<(ostream &output,
                               const GomokuBoard &gb);  // display
    // evaluate state of game method
};