Shresta Bangaru | CS126 Final Project

# Gomoku

## Requirements
* Windows machine
* [Microsoft Visual Studio 2017](https://www.techspot.com/downloads/6278-visual-studio.html) 
* [openFrameworks](https://openframeworks.cc/download/) (add-ons: [ofxButtons](https://github.com/timknapen/ofxButtons), ofxXmlSettings) 
* Download [nlohmann/json](https://github.com/nlohmann/json) 

## Game Instructions
Free-style Gomoku: First player to get at least 5 in a row on the 19x19 board wins. X (black) goes first. 
Program prompts user to enter a name, select piece, and load existing game. 

#### Game options
* Reset: clear game
* Save game: Save to local json file to be read later

## Implementation
Front-end uses openFrameworks. Back-end is C++. AI player uses Minimax algorithm. 
