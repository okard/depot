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
#include "Board.h"

#include "Token.h"

/**
* Create new Board
*/
Board::Board(unsigned int size)
    : size(size), board(new Field[size*size])
{
    //Clean Board
    for(int i=0; i < size*size; i++)
        board[i].tok = 0;
}

/**
* Destructs board
*/ 
Board::~Board()
{
    delete[] board;
}


/** 
* get size
*/
unsigned int Board::getSize()
{
    return size;
}

/**
* Get Token at position
*/ 
Token* Board::get(unsigned int x, unsigned int y)
{
    if(x >= size || y >= size)
    {
        throw "Out of Bounds";
    }
    
    return getField(x,y).tok;
}

/**
* Set Token to Position
*/
void Board::set(unsigned int x, unsigned int y, Token* tok)
{
    if(x >= size || y >= size)
    {
        throw "Out of Bounds";
    }
    
    //check if field is empty?
    getField(x,y).tok = tok;
}

/// Get Direction
Board::Direction Board::getDirection(unsigned int x, unsigned int y)
{
    return getField(x,y).dir;
}

/// Set Direction
void Board::setDirection(unsigned int x, unsigned int y, Direction dir)
{
    getField(x,y).dir = dir;
}

/// Get Field
Board::Field& Board::getField(unsigned int x, unsigned int y)
{
    return board[y*size+x];
}