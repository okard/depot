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
#ifndef __CORE_BOARD_H__
#define __CORE_BOARD_H__

class Token;

/**
* Game Board
*/
class Board
{
private:
    /// Token Direction
    enum Direction
    {
        North,
        South
    };
    
    /// a Field
    struct Field
    {
        //Token
        Token* tok;
        //Direction North or South
        Direction dir;
    };

    /// Size n x n
    unsigned int size;
    
    /// The board
    Field* board;

public:
    Board(unsigned int size);
    ~Board();
    
    
    //move
    
    //attack
    //calculate move/attack
    //place
    
    /// Get Token
    Token* get(unsigned int x, unsigned int y);
    
    /// Set Token
    void set(unsigned int x, unsigned int y, Token* tok);
    
    /// Get Direction
    Direction getDirection(unsigned int x, unsigned int y);
    
    /// Set Direction
    void setDirection(unsigned int x, unsigned int y, Direction dir);
    
    /// get size
    unsigned int getSize();
    
private:
    /// Get Field
    Field& getField(unsigned int x, unsigned int y);
    
};


#endif // __CORE_BOARD_H__