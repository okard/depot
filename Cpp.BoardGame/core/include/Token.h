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
#ifndef __CORE_TOKEN_H__
#define __CORE_TOKEN_H__

/**
* A Token
*/
class Token
{
public:
    /// Helper Typedef
    typedef unsigned char ubyte;
    
    static const int Directions = 8;
    
    /// Base Value
    enum Base
    {
        Black = 1,
        Red = 2,
        Green = 3,
        Blue = 4,
        Gold = 5
    };
    
    /// Actions
    enum Action 
    { 
        None = 0, 
        Move = 1, 
        Attack = 2 
        
    };
    
    /// Directions
    enum Direction 
    { 
        N = 0, 
        NE = 1, 
        E = 2,
        SE = 3,
        S = 4,
        SW = 5,
        W = 6,
        NW = 7
    };
    
    /**
    * Structure for a token side
    */
    struct Side
    {
        /// Actions Available in the 8 Directions
        Action Dir[Directions];
        
        /// The Base Value 1-5
        Base BaseValue;
    };
    
private:
    /// Top Side
    Side topSide;
    
    /// Bottom Side
    Side bottomSide;
    
    /// Which Side at the moment
    bool currentTop;
    
    /// Is currently on the game board
    bool active;
    
    ///Position?
    ///Direction?
     
public:
    /// Create new Token
    Token();
    
    /// Copy Constructor
    Token(const Token& tok);
    
    /// Destructs Token
    ~Token();
    
    /**
    * The Value of Token
    */
    ubyte getValue();
    
    /**
    * Is Token on Board
    */
    bool isActive();
    
    /**
    * Is top side up
    */
    bool isTopSide();
    
    /**
    * Get Current Side
    */
    Side& currentSide();
    
    /**
    * get the Top Side
    */
    Side& getTopSide();
    
    /**
    * get the Bottom Side
    */
    Side& getBottomSide();
    
    /**
    * Swap Sides
    */
    void swapSide();
};




#endif // __CORE_TOKEN_H__