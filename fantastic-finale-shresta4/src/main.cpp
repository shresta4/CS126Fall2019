#include <fstream>
#include <iostream>
#include <json.hpp>
#include <string>
#include "gomoku_board.h"
#include "ofApp.h"
#include "ofMain.h"
#include "round.h"

using namespace std;
using json = nlohmann::json;

//========================================================================
int main() {
    /*cout << "Resume saved game? (Y if yes): ";
    bool read_from_json = false;
    string response;
    cin >> response;
    if (response == "Y") {
        read_from_json = true;
    }

    if (read_from_json) {
        string json_file =
            "C:\\Users\\Shresta\\source\\repos\\CS126FA19\\fantastic-finale-"
            "shresta4\\fantastic-finale-shresta4\\src\\sample_board_test.json";
        ifstream i(json_file);
        json j;
        i >> j;

        string user_name = j["user_name"].get<string>();
        char user_piece = j["user_piece"].get<char>();
        int user_wins = j["user_wins"].get<int>();

        string ai_name = j["ai_name"].get<string>();
        char ai_piece = j["ai_piece"].get<char>();
        int ai_wins = j["ai_wins"].get<int>();

        string board = j["board"].get<string>();
        string current_player = j["current_player"].get<string>();

        GomokuBoard gb = GomokuBoard(user_name, user_piece, user_wins, ai_name,
                                     ai_piece, ai_wins, board);
        cout << gb.board << "this was the current board";
        if (gb.GetWinner() != "no_result") {
            cout << endl
                 << "Previous round completed. Generating new round... "
                 << endl;
            gb = GomokuBoard(user_name, user_piece, user_wins, ai_name,
                             ai_piece, ai_wins,
                             "................................................."
                             "....................."
                             "................................................."
                             "....................."
                             "................................................."
                             "....................."
                             "................................................."
                             "....................."
                             "................................................."
                             "....................."
                             "...........");
        }
        Round r = Round(gb.ai, gb.human, gb, current_player);
        r.PlayRound();

    } else {
        GomokuBoard gb = GomokuBoard();
        Round r = Round(gb.ai, gb.human, gb);
        r.PlayRound();
    }*/

    ofSetupOpenGL((BOARD_SIZE + MARGIN) * (BOARD_SIZE + MARGIN) * SCALE + DISPLACE, (BOARD_SIZE + MARGIN) * (BOARD_SIZE + MARGIN) * SCALE + DISPLACE, OF_WINDOW);  // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}