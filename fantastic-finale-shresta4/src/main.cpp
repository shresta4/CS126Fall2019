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
    cout << "Hello" << endl;

    GomokuBoard gb;
    Round r; 
    bool read_from_json = false;

    if (!read_from_json) {
        gb = GomokuBoard();
        r = Round(gb.ai, gb.human, gb);
    } else {
        json j = ReadFromFile(
            "C:\\Users\\Shresta\\source\\repos\\CS126FA19\\fantastic-finale-"
            "shresta4\\fantastic-finale-shresta4\\src\\sample_board_test.json");
        gb = GomokuBoard(j["user_name"], j["user_piece"], int(j["user_wins"]),
                         j["ai_name"], j["ai_piece"], int(j["ai_wins"]),
                         j["board"], j["current_player"]); 
        r = Round(gb.ai, gb.human, gb, j["current_player"]); 
    }

    r.PlayRound();
    ofSetupOpenGL(1024, 768, OF_WINDOW);  // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}

json ReadFromFile(string json_file) {
    ifstream i(json_file);
    json j;
    return j; 
    /*string user_name = j["user_name"];
    char user_piece = j["user_piece"];
    int user_wins = j["user_wins"];
    string ai_name = j["ai_name"];
    char ai_piece = j["ai_piece"];
    int ai_wins = j["ai_wins"];
    string board = j["board"];
    string current_player_id = j["current_player"]

        GomokuBoard g = GomokuBoard*/
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
