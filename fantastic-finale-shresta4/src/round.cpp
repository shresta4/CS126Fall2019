#include "round.h"
#include <fstream>
#include <iostream>
#include <json.hpp>
#include "gomoku_board.h"

using namespace std;
using json = nlohmann::json;

Round::Round(AI_Player& a, HumanPlayer& h, GomokuBoard& g)
    : ai(a), human(h), gb(g) {
    ai = a;
    human = h;
    gb = g;

    // first player is X
    if (ai.piece == 'X') {
        current_player_id = ai.id;
    } else {
        current_player_id = human.id;
    }
}

Round::Round(AI_Player& a, HumanPlayer& h, GomokuBoard& g, string curr_id)
    : ai(a), human(h), gb(g) {
    ai = a;
    human = h;
    gb = g;
    current_player_id = curr_id;
}

void Round::PlayRound() {
    while (gb.GetWinner() == "no_result") {
        cout << "____________________________________________" << endl;
        cout << gb << endl;
        if (current_player_id == ai.id) {
            cout << "ai turn" << endl;
            int potential_move =
                ai.GetNextMove(gb.board, human.piece, EMPTY_SPACE);
            gb.PlacePiece(potential_move, ai.piece);
            current_player_id = human.id;
        } else {
            bool moved = false;
            do {
                int potential_move = human.GetNextMove();
                if (potential_move == -128) {  // magic number
                    cout << endl << "Game terminated by user. Saving data...";
                    WriteRoundToJson(
                        "C:"
                        "\\Users\\Shresta\\source\\repos\\CS126FA19\\fantastic-"
                        "finale-shresta4\\fantastic-finale-"
                        "shresta4\\src\\sample_board_test.json");
                    cout << "Done.";
                    return; 
                }
                moved = gb.PlacePiece(potential_move, human.piece);
            } while (!moved);
            current_player_id = ai.id;
        }
    }
    cout << gb << endl;
    string win_status = gb.GetWinner();
    if (win_status == "tie") {
        cout << "Round over. Result: Tie." << endl;
    } else if (win_status == ai.id) {
        cout << "Round over. Result: Player " << ai.id << " won.";
    } else {
        cout << "Round over. Result: Player " << human.id << " won.";
    }
    WriteRoundToJson(
        "C:"
        "\\Users\\Shresta\\source\\repos\\CS126FA19\\fantastic-"
        "finale-shresta4\\fantastic-finale-"
        "shresta4\\src\\sample_board_test.json");
}

void Round::WriteRoundToJson(string json_file) {
    json j;
    j["user_name"] = human.id;
    j["user_piece"] = human.piece;
    j["user_wins"] = human.wins;
    j["ai_name"] = ai.id;
    j["ai_piece"] = ai.piece;
    j["ai_wins"] = ai.wins;
    j["board"] = gb.board;
    j["current_player"] = current_player_id;

    ofstream file(json_file);
    file << j << endl;
    file.close();
}