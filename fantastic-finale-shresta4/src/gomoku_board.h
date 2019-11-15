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

    GomokuBoard();                            // empty board
    GomokuBoard(string json_file);            // resume game stored in json file
    void WriteBoardToJson(string json_file);  // saves game
    void GenerateLookupTable();  // creates table of all possible
                                                // winning combinations
    bool PlacePiece(
        int loc,
        int player_id);  // places piece, B = X, W = O, false iff invalid move
    friend ostream &operator<<(ostream &output,
                               const GomokuBoard &gb);  // display
	// evaluate state of game method 
};