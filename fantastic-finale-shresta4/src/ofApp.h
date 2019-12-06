#pragma once

#include <ofxButtons.h>
#include <map>
#include "circle.h"
#include "gomoku_board.h"
#include "ofMain.h"
#include "round.h"

constexpr int SCALE = 2;
constexpr int MARGIN = 4;
constexpr int DISPLACE = 75;
constexpr int MAX_COLOR = 255;
constexpr int MIN_COLOR = 0;
//string json_file = "C:\\Users\\Shresta\\source\\repos\\CS126FA19\\fantastic-finale-shresta4\\fantastic-finale-shresta4\\src\\sample_board_test.json";

using namespace std;

class ofApp : public ofBaseApp {
   public:
    GomokuBoard gb = GomokuBoard();
    Round r = Round(gb.ai, gb.human, gb);
    int currentPlayer = 1;
    vector<Circle> circles;
    map<char, int> pieceToColorMap = {
        {'X', MIN_COLOR},
        {'O', MAX_COLOR}};  // piece to color mapping, X = black = first player
    void setup();
    void update();
    void draw();

    void readFromJson();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    int convertPointToIndex(
        int x, int y);  // from coordinate point get index in board string
    vector<int> snapPoint(int x, int y);
    vector<int> ofApp::convertIndexToPoint(int index);

    ButtonManager buttons;
    bool bReset;
    bool bSaveToJson;
    bool bResumeSavedGame;
};
