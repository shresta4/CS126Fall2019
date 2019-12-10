#include "ai_player.h"
#include <algorithm>
#include <iostream>

using namespace std;

AI_Player::AI_Player() {
    id = "computer";
    piece = 'X';
    opp_piece = 'O';
    wins = 0;
    GenerateLookupTable();
}

AI_Player::AI_Player(string i, char p, int current_wins) {
    id = i;
    piece = p;
    if (piece == 'X') {
        opp_piece = 'O';
    } else {
        opp_piece = 'X';
    }
    wins = current_wins;
    GenerateLookupTable();
}

int AI_Player::GetNextMove(
    const string &board, int opponent_piece,
    char EMPTY_SPACE) {  // currently returns next available
    cout << "Getting next ai move" << endl; 
    Minimax(board, piece, 3, true, opp_piece);
    if (board[best_move] == EMPTY_SPACE) {
        return best_move;
    }

    // if ^^ that gives an invalid move, pick next available piece
    for (int i = 0; i < board.size(); i++) {
        if (board[i] == EMPTY_SPACE) {
            cout << "AI placing piece at " << i << endl;
            return i;
        }
    }
    return -1;
}

void AI_Player::AddWin() { wins++; }

/** BASIC STRATEGY **/
// look for winning combos with a piece already in and return the one with the
// highest chance (4 pieces, 3 pieces, etc.) ---- outdated
/*int AI_Player::BestChancePosition(string board, int opponent_piece) {
    vector<int> best_vector = lookup[0];
    int max_pieces_placed = 0;

    for (int i = 0; i < lookup.size(); i++) {
        int ai_piece_count = 0;
        for (int j = 0; j < lookup[j].size(); j++) {
            if (board[lookup[i][j]] == piece) {
                ai_piece_count++;
            } else if (board[lookup[i][j]] ==
                       opponent_piece) {  // no chance of win here
                ai_piece_count = -1 * BOARD_SIZE;
            }
        }
        if (ai_piece_count >= max_pieces_placed) {
            max_pieces_placed = ai_piece_count;
            best_vector = lookup[i];
        }
        ai_piece_count = 0;
    }

    // find an empty place to put piece in the best vector
    for (int i = 0; i < best_vector.size(); i++) {
        if (board[best_vector[i]] == EMPTY_SPACE) {
            return best_vector[i];
        }
    }
    return 0;
}
*/

/** MINIMAX **/
int AI_Player::HeuristicCalculator(const string &board, char player, char opponent) {
    int value = 0;
    for (int i = 0; i < lookup.size(); i++) {
        vector<int> combo = lookup[i];

        int count_player = 0;
        int count_opponent = 0;
        for (int j = 0; j < combo.size(); j++) {
            if (board[combo[j]] == player) {
                count_player++;
            } else if (board[combo[j]] == opponent) {
                count_opponent++;
            }
        }

        // 5 in a row
        if (count_player == GOAL) {
            value += BOARD_SIZE * BOARD_SIZE * GOAL;
        }

        // 4 in a row but opponent = 0
        if (count_player == (GOAL - 1) && count_opponent == 0) {
            value += (GOAL - 1);
        }

        // 3 in a row but opponent = 0
        if (count_player == (GOAL - 2) && count_opponent == 0) {
            value += (GOAL - 2);
        }

        // opponent has 5 in a row
        if (count_opponent == GOAL) {
            value -= BOARD_SIZE * BOARD_SIZE * GOAL;
        }

        // opponent has 4 in a row and not blocked
        if (count_opponent == (GOAL - 1) && count_player == 0) {
            value -= (GOAL - 1);
        }

        // opponent has 3 in a row and not blocked
        if (count_opponent == (GOAL - 2) && count_player == 0) {
            value -= (GOAL - 2);
        }
        count_player = 0;
        count_opponent = 0;
    }
    return value;
}

vector<int> AI_Player::NextMoves(const string &board, char player, char opponent) {
    vector<int> moves;
    for (int i = 0; i < lookup.size(); i++) {
        bool consider = false;
        vector<int> combo = lookup[i];
        for (int j = 0; j < combo.size(); j++) {
            if (board[combo[j]] == player || board[combo[j]] == opponent) {
                consider = true;
            }
        }
        if (consider) {
            for (int j = 0; j < combo.size(); j++) {
                if (board[combo[j]] == EMPTY_SPACE &&
                    (std::find(moves.begin(), moves.end(), combo[j]) ==
                     moves.end()) && moves.size() <= 10) { //magic number
                    moves.push_back(combo[j]);
                }
            }
        }
    }
    return moves;
}

int AI_Player::Minimax(string board, char player, int depth,
                       bool maximizing_player, char opponent) {
    //cout << depth << endl;
    int best_value = INT_MIN;
    if (depth == 0) {  // or is terminal node ????????
        int h = HeuristicCalculator(board, player, opponent);
       // cout << "Heuristic: " << h << endl;
        return h;
    }
    if (maximizing_player) {
        best_value = INT_MIN;
        // make a list of all valid moves (Basically everything with "."
        vector<int> good_moves = NextMoves(board, player, opponent);
        cout << good_moves.size() << endl; 
        for (int i = 0; i < good_moves.size(); i++) {
            int pos = good_moves[i];
            if (board[pos] == EMPTY_SPACE) {  // if valid move
                //string temporary_board = MakeTemporaryMove(board, player, pos);
                board[pos] = player; 
                int v = Minimax(board, opponent, depth - 1, false,
                                player);
                board[pos] = EMPTY_SPACE; 
                if (v > best_value) {
                    best_value = v;
                    best_move = pos;
                }
            }
        }
    } else {
        best_value = INT_MAX;
        vector<int> good_moves = NextMoves(board, player, opponent);
        cout << good_moves.size() << endl; 
        for (int i = 0; i < good_moves.size(); i++) {
            int pos = good_moves[i];
            if (board[pos] == EMPTY_SPACE) {
                //string temporary_board = MakeTemporaryMove(board, player, pos);
                board[pos] = player; 
                int v =
                    Minimax(board, opponent, depth - 1, true, player);
                board[pos] = EMPTY_SPACE; 
                if (v < best_value) {
                    best_value = v;
                    best_move = pos;
                }
            }
        }
    }
    return best_value;
}

string AI_Player::MakeTemporaryMove(string board, char player, int position) {
    string temp = "";
    for (int i = 0; i < board.length(); i++) {
        if (i == position) {
            temp += player;
        } else {
            temp += board[i];
        }
    }

    return temp;
}

/*def Minimax(board, player, depth, maximizingPlayer):
    if depth == 0 or IsTerminalNode(board, player):
        return EvalBoard(board, player)
    if maximizingPlayer:
        bestValue = minEvalBoard
        for y in range(n):
            for x in range(n):
                if ValidMove(board, x, y, player):
                    (boardTemp, totctr) = MakeMove(copy.deepcopy(board), x, y,
   player) v = Minimax(boardTemp, player, depth - 1, False) bestValue =
   max(bestValue, v) else: # minimizingPlayer bestValue = maxEvalBoard for y in
   range(n): for x in range(n): if ValidMove(board, x, y, player): (boardTemp,
   totctr) = MakeMove(copy.deepcopy(board), x, y, player) v = Minimax(boardTemp,
   player, depth - 1, True) bestValue = min(bestValue, v) return bestValue */

void AI_Player::GenerateLookupTable() {
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
