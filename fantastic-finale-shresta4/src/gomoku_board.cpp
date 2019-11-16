#include "gomoku_board.h"
#include <iostream>
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
    GenerateLookupTable();
    for (int i = 0; i < lookup.size(); i++) {
        for (int j = 0; j < lookup[i].size(); j++) {
            cout << lookup[i][j] << " ";
        }
        cout << endl;
    }
}

GomokuBoard::GomokuBoard(string json_file) {
    // read from
    // json!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    board = "";
    GenerateLookupTable();
}

void GomokuBoard::GenerateLookupTable() {
    // rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        int row_start = i * BOARD_SIZE;  // each iteration of the loop will make
                                         // this: 0, 19, 38, etc.
        int row_end =
            row_start + (BOARD_SIZE -
                         1);  // each iteration will make this: 18, 37, 56, etc.

        // make every possible '5 in a row' within that row
        for (int j = row_start; j <= row_end - GOAL + 1; j++) {
            vector<int> sequence = vector<int>();
            for (int k = j; k < j + GOAL; k++) {
                sequence.push_back(k);
            }
            lookup.push_back(sequence);
            sequence = vector<int>();
        }
    }

    // cols
    for (int i = 0; i < BOARD_SIZE; i++) {
        int col_start = i;
        int col_end = i + (BOARD_SIZE - 1) * BOARD_SIZE;

        // make every possible '5 in a column' within that column
        for (int j = col_start; j <= col_end - GOAL * BOARD_SIZE + BOARD_SIZE;
             j += BOARD_SIZE) {
            vector<int> sequence = vector<int>();
            for (int k = j; k < j + GOAL * BOARD_SIZE; k += BOARD_SIZE) {
                sequence.push_back(k);
            }
            lookup.push_back(sequence);
            sequence = vector<int>();
        }
    }
    // diagonals top left to bottom right, upper half
    for (int i = 0; i < BOARD_SIZE; i++) {
        int diagonal_start = i;
        int diagonal_end = i + (BOARD_SIZE - 1 - i) * (BOARD_SIZE + 1);

        // make every possible '5 in a diagonal' within that diagonal
        for (int j = diagonal_start;
             j <= diagonal_end - GOAL * BOARD_SIZE + (BOARD_SIZE + 1);
             j += (BOARD_SIZE + 1)) {
            vector<int> sequence = vector<int>();
            for (int k = j; k < j + GOAL * (BOARD_SIZE + 1);
                 k += (BOARD_SIZE + 1)) {
                sequence.push_back(k);
            }
            lookup.push_back(sequence);
            sequence = vector<int>();
        }
    }

    // diagonals top left to bottom right, lower half
    for (int i = 1; i < BOARD_SIZE;
         i++) {  // start at 19 and go down the first column
        int diagonal_start = i * BOARD_SIZE;
        int diagonal_end = BOARD_SIZE * BOARD_SIZE - (i + 1);

        // make every possible '5 in a diagonal' within that diagonal
        for (int j = diagonal_start;
             j <= diagonal_end - GOAL * BOARD_SIZE + (BOARD_SIZE + 1);
             j += (BOARD_SIZE + 1)) {
            vector<int> sequence = vector<int>();
            for (int k = j; k < j + GOAL * (BOARD_SIZE + 1);
                 k += (BOARD_SIZE + 1)) {
                sequence.push_back(k);
            }
            lookup.push_back(sequence);
            sequence = vector<int>();
        }
    }

    // diagonals top right to bottom left, top half
    for (int i = 0; i < BOARD_SIZE; i++) {
        int diagonal_start = i;
        int diagonal_end = i * BOARD_SIZE;

        // make every possible '5 in a diagonal' within that diagonal
        for (int j = diagonal_start;
             j <= diagonal_end - (GOAL - 1) * (BOARD_SIZE - 1);
             j += (BOARD_SIZE - 1)) {
            vector<int> sequence = vector<int>();
            for (int k = j; k < j + (GOAL) * (BOARD_SIZE - 1);
                 k += (BOARD_SIZE - 1)) {
                sequence.push_back(k);
            }
            lookup.push_back(sequence);
            sequence = vector<int>();
        }
    }

	// diagonals top right to bottom left, bottom half
    for (int i = BOARD_SIZE * 2 - 1; i < BOARD_SIZE * BOARD_SIZE; i++) {
        int diagonal_start = i;
        int diagonal_end = (BOARD_SIZE * BOARD_SIZE - 1) - (BOARD_SIZE - (diagonal_start + 1) / BOARD_SIZE);

        // make every possible '5 in a diagonal' within that diagonal
        for (int j = diagonal_start;
             j <= diagonal_end - (GOAL - 1) * (BOARD_SIZE - 1);
             j += (BOARD_SIZE - 1)) {
            vector<int> sequence = vector<int>();
            for (int k = j; k < j + (GOAL) * (BOARD_SIZE - 1);
                 k += (BOARD_SIZE - 1)) {
                sequence.push_back(k);
            }
            lookup.push_back(sequence);
            sequence = vector<int>();
        }
    }
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

int GetWinner() {

}

bool GomokuBoard::PlayerWins(int player_id) {
    for (int i = 0; i < lookup.size(); i++) {
		
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