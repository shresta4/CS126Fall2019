/*#include "catch.hpp"
#include "gomoku_board.h"

using namespace std;

string empty_board = "......................................................................"
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "......................................................................"
    "...........";

TEST_CASE("Placing piece in already taken position") {
    GomokuBoard gb = GomokuBoard("shresta", 'X', 0, "computer", 'O', 0, empty_board); 
	gb.PlacePiece(0, 'X'); 
	REQUIRE(gb.PlacePiece(0, 'O') == false); 
}

TEST_CASE("Placing piece in empty position") {
    GomokuBoard gb =
        GomokuBoard("shresta", 'X', 0, "computer", 'O', 0, empty_board);
    gb.PlacePiece(0, 'X');
    REQUIRE(gb.PlacePiece(1, 'O') == true);
}

TEST_CASE("Detecting winner - no winner") {
    GomokuBoard gb =
        GomokuBoard("shresta", 'X', 0, "computer", 'O', 0, empty_board);
    REQUIRE(gb.GetWinner() == "no_result"); 
}

TEST_CASE("Detecting winner - X winner") {
	string sample_board = "XXXXX................................................................."
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "...........";
    GomokuBoard gb =
        GomokuBoard("shresta", 'X', 0, "computer", 'O', 0, sample_board);

    REQUIRE(gb.GetWinner() == "shresta");
}

TEST_CASE("Detecting winner - O winner") {
    string sample_board =
        ".....OOOOO............................................................"
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "......................................................................"
        "...........";
    GomokuBoard gb =
        GomokuBoard("shresta", 'X', 0, "computer", 'O', 0, sample_board);

    REQUIRE(gb.GetWinner() == "computer");
}


*/