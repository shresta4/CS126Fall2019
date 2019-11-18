#include <fstream>
#include <iostream>
//#include "ai_player.h"
#include "gomoku_board.h"
//#include "human_player.h"
#include "ofApp.h"
#include "ofMain.h"
#include "round.h"

using namespace std;

//========================================================================
int main() {
    std::cout << "Hello";
    GomokuBoard gb = GomokuBoard();
    Round r = Round(gb.ai, gb.human, gb);
    r.PlayRound(); 
    ofSetupOpenGL(1024, 768, OF_WINDOW);  // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
