#include "gomoku_board.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <string>
#include <vector>

using namespace std;
using json = nlohmann::json;

GomokuBoard::GomokuBoard() {
    board =
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "...........";
    ai = AI_Player();
    human = HumanPlayer();
    GenerateLookupTable();
}

GomokuBoard::GomokuBoard(string stored_board, AI_Player a, HumanPlayer h) {
    board = stored_board;
    ai = a;
    human = h;
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
        int diagonal_end = (BOARD_SIZE * BOARD_SIZE - 1) -
                           (BOARD_SIZE - (diagonal_start + 1) / BOARD_SIZE);

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

bool GomokuBoard::PlacePiece(int loc, char player_piece) {
    if (loc < 0 || loc > BOARD_SIZE * BOARD_SIZE - 1) {
        cout << "Invalid move." << endl;
        return false;                // invalid
    } else if (board[loc] != EMPTY_SPACE) {  // space already taken
        cout << "Invalid move." << endl;
        return false;
    } else {
        board[loc] = player_piece;
    }
}

string GomokuBoard::GetWinner() {
    if (PlayerWins(ai.piece)) {
        return ai.id;
    } else if (PlayerWins(human.piece)) {
        return human.id;
    } else if (count(board.begin(), board.end(), EMPTY_SPACE) == 0) {
        return "tie";  // code for tie
    }
    return "no_result";  // code for no winner yet
}

bool GomokuBoard::PlayerWins(char player_piece) {
    for (int i = 0; i < lookup.size(); i++) {
        bool win = true;
        vector<int> combo = lookup[i];
        for (int j = 0; j < combo.size(); j++) {
            if (board[combo[j]] != player_piece) {
                win = false;
            }
        }
        if (win) {
            return true;
        }
    }
    return false;
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

/*void GomokuBoard::WriteBoardToJson(string json_file) {
    json j;
    j["board"] = board;
    j["player_1_id"] = player_1_id;
    j["player_0_id"] = player_0_id;

    ofstream file(json_file);
    file << j << endl;
    file.close();
    cout << "Hello";

        std::ifstream
i("C:\\Users\\Shresta\\source\\repos\\CS126FA19\\fantastic-finale-shresta4\\fantastic-finale-shresta4\\src\\sample_board_test.json");
    json j2;
    i >> j2;
    cout << j2["board"];

}*/