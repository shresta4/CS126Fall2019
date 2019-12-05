11/15/2019
- Started assignment
- GomokuBoard class: << overload, constructors

11/16/2019
- Finished GomokuBoard class
- Adding constructor to read from json file
- Asked on piazza how to write test cases
- "AI" player with random moves

11/17/2019
- HumanPlayer class that takes input (to-do: account for people entering invalid values)
- Reading and writing to json using nlohmann/json.hpp
- Made sure Round.cpp works

11/18/2019
- Change player id to a string, change piece to a char
- Accounting for invalid user input. 
- Making a round run in the main method while letting the user define their name/piece

11/19/2019
- Reading/writing round to json 

11/20/2019
- Excluding json from build
- Making sure if json file has a finished game, it moves on to a new game 

11/26/2019 
- Making a board display and having user place pieces which snap into place. 
- Incorporating a round into the ofApp.cpp. 
- Fixing winner detection

11/27/2019
- Reading https://web.archive.org/web/20140411074912/http://chalmersgomoku.googlecode.com/files/allis1994.pdf to learn how to make the AI 

12/5/2019
- Fixing parenthesis issues (was causing errors and the game wouldn't end at the right time) 

11/_ /2019
- Make player abstract class and have AI and User extend from it 
- Currently free style gomoku. Implement: standard gomoku. No overlines 
- Make a file with constants "tie" "no result" etc etc., Save no_player as a constant 
- Have the user pick a color instead of X or O
- Add a delay before the AI plays 
- Move title to the top of the screen 
- Add buttons for load json, save, restart, exit (ofxdatgui)
- Read game from json 
- Account for when there's no winner but the board is full 
- Fix ending the game on time 
