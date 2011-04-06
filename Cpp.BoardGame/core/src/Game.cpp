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
#include <Game.h>

/**
* Create a new game
*/
Game::Game()
    : playerA(0), playerB(0), board(0), gamePhase(PickPhase)
{

}

/**
* Destructs game
*/
Game::~Game()
{

}

/**
* Set the board
*/
void Game::setBoard(Board* board)
{
    this->board = board;
}

/**
* Get the Board
*/
Board* Game::getBoard()
{
    return board;
}

void Game::setPlayerA(Player* player)
{
    playerA = player;
}

/**
* Get Player A
*/
Player* Game::getPlayerA()
{
    return playerA;
}

/**
* Set Player B
*/
void Game::setPlayerB(Player* player)
{
    playerB = player;
}

/** 
* Get Player B
*/
Player* Game::getPlayerB()
{
    return playerB;
}

/**
* Start game
*/   
void Game::start()
{
    started = true;
}
    
/**
* end current phase and go to the next
*/    
void Game::endPhase()
{
    switch(gamePhase)
    {
        case PickPhase:
            gamePhase = SetPhase;
            break;
        case SetPhase:
            gamePhase = GamePhase;
            break;
    }
}

/**
* Get current game phase
*/
Game::Phase Game::getPhase()
{
    return gamePhase;
}