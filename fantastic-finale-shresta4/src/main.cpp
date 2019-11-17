#include <iostream>
#include "gomoku_board.h"
#include "ofApp.h"
#include "ofMain.h"

using namespace std;

//========================================================================
int main() {
    std::cout << "Hello";
    GomokuBoard gb = GomokuBoard();
    cout << gb;
    gb.PlacePiece(0, 1); 
	gb.PlacePiece(1, 1); 
	gb.PlacePiece(2, 1); 
	gb.PlacePiece(3, 1); 
	gb.PlacePiece(4, 1); 
	cout << gb << endl; 
	cout << gb.GetWinner(); 
	gb.WriteBoardToJson("sample_board_test.json");
    ofSetupOpenGL(1024, 768, OF_WINDOW);  // <-------- setup the GL context

	

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
