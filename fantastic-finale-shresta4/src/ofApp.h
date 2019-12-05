#pragma once

#include "circle.h"
#include "gomoku_board.h"
#include "ofMain.h"
#include "round.h"

constexpr int SCALE = 2;
constexpr int MARGIN = 4;

class ofApp : public ofBaseApp {
   public:
    GomokuBoard gb = GomokuBoard(); 
    Round r = Round(gb.ai, gb.human, gb);
    int currentPlayer = 1; 
    vector<Circle> circles;
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
};
