#include "catch.hpp"
#include "gomoku_board.h"

using namespace std;

string sample_board =
    "...........X.........................................................."
    "......................................................................"
    "...................O.................................................."
    "......................................................................"
    ".........O...............................X............................"
    "...........";

TEST_CASE("Checking if AI produces valid move") {
    GomokuBoard gb =
        GomokuBoard("shresta", 'X', 0, "computer", 'O', 0, sample_board);
    int next_move = gb.ai.GetNextMove(gb.board, gb.human.piece, EMPTY_SPACE); 
    REQUIRE(gb.PlacePiece(next_move, 'O') == true);
}

TEST_CASE("Testing if it places a move correctly") {
    GomokuBoard gb =
        GomokuBoard("shresta", 'X', 0, "computer", 'O', 0, sample_board);
    // int next_move = gb.ai.GetNextMove(gb.board, gb.human.piece, EMPTY_SPACE);
    string mock = gb.ai.MakeTemporaryMove(gb.board, gb.ai.piece, 0); 
    REQUIRE(gb.board[0] == gb.ai.piece);
}