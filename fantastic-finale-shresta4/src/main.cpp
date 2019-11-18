#include <fstream>
#include <iostream>
#include "ai_player.h"
#include "gomoku_board.h"
#include "human_player.h"
#include "ofApp.h"
#include "ofMain.h"
#include "round.h"

using namespace std;

//========================================================================
int main() {
    std::cout << "Hello";
    GomokuBoard gb1 = GomokuBoard();
    AI_Player ai1 = AI_Player(0, 0);
    HumanPlayer h1 = HumanPlayer(0, 0);
    Round r = Round(ai1, h1, gb1);
    ofSetupOpenGL(1024, 768, OF_WINDOW);  // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
