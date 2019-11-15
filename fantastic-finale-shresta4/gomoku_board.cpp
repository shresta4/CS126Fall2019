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

vector<vector<int>> GomokuBoard::GenerateLookupTable() {
    // rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        int row_start = i * BOARD_SIZE;  // each iteration of the loop will make
                                         // this: 0, 19, 38, etc.
        int row_end =
            row_start + (BOARD_SIZE -
                         1);  // each iteration will make this: 18, 37, 56, etc.

        // make every possible '5 in a row' within that row
        for (int j = row_start; j < row_end - GOAL; j++) {
            vector<int> sequence = new vector<int>();
            for (int k = j; k < j + GOAL; k++) {
                sequence.push_back(k);
            }
            lookup.push_back(sequence);
            sequence = new vector<int>();
        }
    }

    // cols

    // diagonals top left to bottom right

    // diagonals top right to bottom left

    cout << lookup;
    return lookup;  // later make this a void function
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