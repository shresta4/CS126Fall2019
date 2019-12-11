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
- Making display update according to json 

12/6/2019
- Removed magic numbers for circle colors (0 and 225), Associated colors with X and O
- Text color changes based on whose turn it is (in case they forgot which color piece is theirs.) 
- Used ofxButtons to create reset, save buttons
- Made sure reset works after the game ends 

12/10/2019
- Make AI using Minimax algorithm
- Speed up AI with slight design changes
- Test cases

11/_ /2019 
- UI for name and piece
- Fix error with lookup table
- Comments/documentation
