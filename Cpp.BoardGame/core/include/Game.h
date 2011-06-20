/*
The MIT License

Copyright (c) 2011 okard

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <Board.h>
#include <Player.h>


/**
* Game Options
* Game Rules/ Parameters / ????
*/
struct GameOptions
{
    unsigned int armyLimit; 
    unsigned int boardSize;
    
    //bool diceRole
    //unsigned short diceDefault;
    
    //win terms
};

/**
* A Game
*/
class Game
{
public:
    /// Represents the Phases of a game
    enum Phase
    {
        PickPhase = 1,
        SetPhase = 2,
        GamePhase = 3
    };
    
    
    ///Represents the Phases of a turn
    //TurnState ?
    enum TurnPhase
    {
       DiceRole,
       MoveTake,
       Promote,
       Drop
    };
    
private:
    /// Player A
    Player* playerA;
    
    /// Player B
    Player* playerB;
    
    /// Board
    Board* board;
    
    /// Current Phase
    Phase gamePhase;
    
    /// Has Game started
    bool started;
    
    /// which turn?
    bool turnPlayerA;
    
    /// Rounds Played
    unsigned int rounds;
    
public:
    
    //init(GameOptions, PlayerA, PlayerB);
    
    /// Create new Game
    Game();
    
    /// Destructs Game
    ~Game();
    
    /// Set the Board
    void setBoard(Board* board);
    
    /// Get the Board
    Board* getBoard();

    /// Set Player A
    void setPlayerA(Player* player);
    
    /// Get Player A
    Player* getPlayerA();
    
    /// Set Player B
    void setPlayerB(Player* player);
    
    /// Get Player B
    Player* getPlayerB();
    
    /// Start Game
    void start();
    
    
    //Whichs Turn
    //End Turn
    //TurnPhase
    
    
    //do game actions and check rules
    //move (field a to field b)
    //take (field a to field b) 
        // check right player
        // check move allowed for token
        // check available ap
        // check phase
    //promote (field a)
    //drop (token, field)
    
    
    /// End Current Phase
    void endPhase();
    
    /// Get Current Phase
    Phase getPhase();
    
};



#endif // __GAME_HPP__