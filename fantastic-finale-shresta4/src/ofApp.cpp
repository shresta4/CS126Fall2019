#include "ofApp.h"
#include "circle.h"
#include "gomoku_board.h"

//--------------------------------------------------------------
void ofApp::setup() {}

//--------------------------------------------------------------
void ofApp::update() {
    if (r.current_player_id == r.ai.id) {
        int move = r.ai.GetNextMove(gb.board, r.human.piece, EMPTY_SPACE);
        gb.PlacePiece(move, r.ai.piece);

        vector<int> coords = convertIndexToPoint(move);

        Circle c = Circle(coords[0], coords[1], BOARD_SIZE,
                          0);  // color is indicated by 1 or 0 - CHANGE
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
                (BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN * 11);
            Sleep(1000);
        }
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
    if (gb.GetWinner() == "no_result" && r.current_player_id == r.human.id) {
        // check if its in bounds
        if (x < (BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN &&
            y < (BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE + MARGIN) {
            vector<int> new_coords = snapPoint(x, y);
            int index = convertPointToIndex(new_coords[0], new_coords[1]);

            // have to check if that's a valid click
            bool moved = gb.PlacePiece(index, gb.human.piece);
            if (moved) {
                convertPointToIndex(new_coords[0], new_coords[1]);
                Circle c = Circle(new_coords[0], new_coords[1], BOARD_SIZE,
                                  255);  // color is indicated by 1 or 0
                circles.push_back(c);

                r.current_player_id = r.ai.id;
            }
        }
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
    int new_y = ((y - 0) - (y % BOARD_SIZE + MARGIN)) / (BOARD_SIZE + MARGIN);
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
