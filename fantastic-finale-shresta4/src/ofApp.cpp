#include "ofApp.h"
#include <json.hpp>
#include "circle.h"
#include "gomoku_board.h"

using json = nlohmann::json;

//--------------------------------------------------------------
void ofApp::setup() {
    cout << "Resume saved game from json? (Y for yes): " << endl;
    string response;
    cin >> response;
    if (response == "Y") {
        readFromJson();
    }
}

void ofApp::readFromJson() {
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

    cout << user_name << " " << user_piece << " " << user_wins << " " << ai_name
         << " " << ai_wins << " " << ai_piece << " " << ai_wins << " " << board
         << current_player << endl;

    gb = GomokuBoard(user_name, user_piece, user_wins, ai_name, ai_piece,
                     ai_wins, board);

    if (gb.GetWinner() != "no_result") {
        cout << endl
             << "Previous round completed. Generating new round... " << endl;
        gb = GomokuBoard(user_name, user_piece, user_wins, ai_name, ai_piece,
                         ai_wins,
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
    } else {  // add circles to circle vector
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
            if (board[i] == user_piece) {
                vector<int> coords = convertIndexToPoint(i);
                Circle c = Circle(coords[0], coords[1], BOARD_SIZE,
                                  pieceToColorMap[user_piece]);
                circles.push_back(c);
            } else if (board[i] == ai_piece) {
                vector<int> coords = convertIndexToPoint(i);
                Circle c = Circle(coords[0], coords[1], BOARD_SIZE,
                                  pieceToColorMap[ai_piece]);
                circles.push_back(c);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    // cout << "HELLO" << endl;

    if (gb.GetWinner() != "no_result") {
        r.current_player_id = "no_player";
    }
    if (r.current_player_id == r.ai.id) {
        int move = r.ai.GetNextMove(gb.board, r.human.piece, EMPTY_SPACE);
        gb.PlacePiece(move, r.ai.piece);

        vector<int> coords = convertIndexToPoint(move);

        Circle c = Circle(coords[0], coords[1], BOARD_SIZE,
                          pieceToColorMap[r.ai.piece]);
        circles.push_back(c);

        r.current_player_id = r.human.id;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    // draw board
    ofNoFill();
    ofSetColor(0, 0, 0);
    for (int i = 0; i < BOARD_SIZE - 1; i++) {
        for (int j = 0; j < BOARD_SIZE - 1; j++) {
            glm::vec3 p;
            p.x = i * (BOARD_SIZE + MARGIN) * SCALE +
                  BOARD_SIZE;  // column by column
            p.y = j * (BOARD_SIZE + MARGIN) * SCALE + BOARD_SIZE;
            ofDrawRectangle(p, BOARD_SIZE * SCALE + MARGIN,
                            BOARD_SIZE * SCALE + MARGIN);  // Draw the rectangle
        }
    }

    // place pieces
    ofFill();
    for (Circle c : circles) {
        ofSetColor(c.color, c.color, c.color);
        ofDrawCircle(c.x, c.y, c.radius);
    }

    // text
    glPointSize(10);
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(
        "Gomoku!", ((BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN) / 2,
        (BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN * 5);

    if (gb.GetWinner() == "no_result") {
        if (r.current_player_id == r.human.id) {
            ofDrawBitmapString(
                "Your turn.",
                ((BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN) / 2,
                (BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN * 8);
        } else {
            ofDrawBitmapString(
                "AI turn.",
                ((BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN) / 2,
                (BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN * 8);
            Sleep(1000);
        }
    } else {
        ofSetColor(0, 0, 0);
        ofDrawBitmapString(
            "Game over. " + gb.GetWinner() + " wins.",
            ((BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN) / 2,
            (BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN * 8);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    // cout << "MOUSE WAS PRESSED";
    if (gb.GetWinner() != "no_result") {
        r.current_player_id = "no_player";
    }
    if (gb.GetWinner() == "no_result" && r.current_player_id == r.human.id) {
        // check if its in bounds
        if (x < (BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN &&
            y < (BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN) {
            // cout << "original points " << x << " " << y << endl;
            vector<int> new_coords = snapPoint(x, y);
            int index = convertPointToIndex(new_coords[0], new_coords[1]);
            // cout << "snapped to " << new_coords[0] << " " << new_coords[1]
            //     << " converted to index " << index << endl;

            // have to check if that's a valid click
            bool moved = gb.PlacePiece(index, gb.human.piece);
            if (moved) {
                convertPointToIndex(new_coords[0], new_coords[1]);
                Circle c = Circle(new_coords[0], new_coords[1], BOARD_SIZE,
                                  pieceToColorMap[r.human.piece]);
                circles.push_back(c);

                r.current_player_id = r.ai.id;
            }
        }
        // cout << "number of circles " << circles.size() << endl;
        cout << gb << endl;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}

int ofApp::convertPointToIndex(int x, int y) {  // from snap point
    int new_x = ((x - 0) - (x % (BOARD_SIZE + MARGIN))) / (BOARD_SIZE + MARGIN);
    int new_y = ((y - 0) - (y % (BOARD_SIZE + MARGIN))) / (BOARD_SIZE + MARGIN);
    return (new_y * BOARD_SIZE + new_x) / 2;
}

vector<int> ofApp::convertIndexToPoint(int index) {
    // fix
    int x_part = index % BOARD_SIZE;
    int y_part = index / BOARD_SIZE;
    vector<int> coords;
    coords.push_back(x_part * (BOARD_SIZE + MARGIN) * SCALE + BOARD_SIZE);
    coords.push_back(y_part * (BOARD_SIZE + MARGIN) * SCALE + BOARD_SIZE);
    return coords;
}

vector<int> ofApp::snapPoint(int x, int y) {
    int new_x = (x + BOARD_SIZE) -
                (x % ((BOARD_SIZE + MARGIN) *
                      SCALE));  // (x - (MARGIN / MARGIN)) / SCALE - MARGIN;
    int new_y = (y + BOARD_SIZE) -
                (y % ((BOARD_SIZE + MARGIN) *
                      SCALE));  // (y - (MARGIN / MARGIN)) / SCALE - MARGIN;
    vector<int> coords;
    coords.push_back(new_x);
    coords.push_back(new_y);
    return coords;
}
