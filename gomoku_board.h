#pragma once

using namespace std;
constexpr int BOARD_SIZE = 19;

class GomokuBoard {
	string board; 
	vector<vector<int>> lookup; 

    GomokuBoard(); // empty board
    GomokuBoard(string json_file); // resume game stored in json file
    void WriteBoardToJson(string json_file); // saves game 
	void GenerateLookupTable(); // creates table of all possible winning combinations
    bool PlacePiece(int loc, int player_id); // places piece, B = 1, W = 0, false iff invalid move
    friend ostream &operator<<(ostream &output, const GomokuBoard &gb); // display
};