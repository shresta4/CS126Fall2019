#include "gomoku_board.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

GomokuBoard::GomokuBoard() {
    board =  "......................................................................"
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "..........."; 
    ai = AI_Player();

    // create the user object
    cout << "Select a user name: ";
    string user_name;
    cin >> user_name;
    while (user_name.length() == 0 || user_name == "computer" ||
           user_name == "tie" || user_name == "no_result") {
        cout << endl << "Please enter a valid name/one that is not taken yet: ";
        cin >> user_name;
    }
    cout << endl << "Do you want to be X or O? ";
    char user_piece;
    string entire_input;
    cin >> entire_input;
    user_piece = entire_input[0];
    while (user_piece != 'X' && user_piece != 'O') {
        cout << endl << "Please enter either X or O: ";
        cin >> entire_input;
        user_piece = entire_input[0];
    }
    char ai_piece;
    if (user_piece == 'X') {
        ai_piece = 'O';
    } else {
        ai_piece = 'X';
    }

    human = HumanPlayer(user_name, user_piece, 0);
    ai = AI_Player("computer", ai_piece, 0);
    GenerateLookupTable();
}

GomokuBoard::GomokuBoard(string user_name, char user_piece, int user_wins,
                         string ai_name, char ai_piece, int ai_wins,
                         string stored_board) {
    board = stored_board;
    ai = AI_Player(ai_name, ai_piece, ai_wins);
    human = HumanPlayer(user_name, user_piece, user_wins);
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
    if (loc == -1) {
        cout << "Invalid move." << endl;
        return false;
    }
    if (loc < 0 || loc > BOARD_SIZE * BOARD_SIZE - 1) {
        cout << "Invalid move." << endl;
        return false;                        // invalid
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
