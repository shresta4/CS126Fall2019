#include "ofApp.h"
#include "circle.h"
#include "gomoku_board.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // currentPlayer = -1;
}

//--------------------------------------------------------------
void ofApp::update() {}

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
	// check if its in bounds 
	if (x < (BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE +
                    MARGIN &&
            y < (BOARD_SIZE) * (BOARD_SIZE + MARGIN) * SCALE +
                    MARGIN) {
            vector<int> new_coords = snapPoint(x, y);

            Circle c =
                Circle(new_coords[0], new_coords[1], BOARD_SIZE,
                       currentPlayer * 255);  // color is indicated by 1 or 0
            circles.push_back(c);

            currentPlayer = 1 - currentPlayer;
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

int ofApp::convertPointToIndex(int x, int y) {
    // fix this
    return (y * BOARD_SIZE + x);
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
    cout << new_x << " " << new_y << endl; 
    return coords;
}
