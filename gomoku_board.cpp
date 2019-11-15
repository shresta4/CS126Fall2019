#include "gomoku_board.h"
#include <string>
#include <vector>

using namespace std;

GomokuBoard::GomokuBoard() {
    board =
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "...........";
    lookup = GenerateLookupTable();
}

GomokuBoard::GomokuBoard(string json_file) {
    // read from
    // json!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    board = "";
    lookup = GenerateLookupTable();
}

bool GomokuBoard::PlacePiece(int loc, int player_id) {
    if (board[loc] != '.') {  // space already taken
        return false;
    } else {
        board[loc] = player_id;
        /*
                might have to do something like this
                board.substr(0, loc) + to_string(player_id) + board.substr(loc +
           1);
                */
    }
}

ostream &operator<<(ostream &output, const GomokuBoard &gb) {
    int index = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        output << endl;
        for (int j = 0; j < BOARD_SIZE; j++) {
            output << gb.board[index] << " "; 
            index++; 
        }
    }
    output << endl;
    return output;
}