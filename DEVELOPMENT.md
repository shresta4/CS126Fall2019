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

11/_ /2019
- Make player abstract class and have AI and User extend from it 
- Notes to self: Account for the fact that -1 and -10 cannot be valid ai/player ids, Account for user error in entering invalid moves
- Make the json read a round instead of a game 
- Change the player id to a string, change the piece to X and O. 
- Currently free style gomoku. Implement: standard gomoku. No overlines 
- Check for invalid move whether the piece is already taken or not. 
- Make a file with constants "tie" "no result" etc etc. 
