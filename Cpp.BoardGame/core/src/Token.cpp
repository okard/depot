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

#include <Token.h>

/**
* Create new Token
*/
Token::Token()
{
    //reset stats
    topSide.BaseValue = Black;
    bottomSide.BaseValue = Black;
    
    for(int i=0; i < Directions; i++)
    {
        bottomSide.Dir[i] = topSide.Dir[i] = None;
    }
}

/**
* Copy Constructor
*/
Token::Token(const Token& tok)
{
    topSide.BaseValue = tok.topSide.BaseValue;
    bottomSide.BaseValue = tok.bottomSide.BaseValue;
    
    for(int i=0; i < Directions; i++)
    {
        topSide.Dir[i] = tok.topSide.Dir[i];
        bottomSide.Dir[i] = tok.bottomSide.Dir[i];  
    }
}

/**
* Destructs token
*/
Token::~Token()
{
}

/**
* Value of token 
*/
Token::ubyte Token::getValue()
{
    // Base Values
    int fullValue = topSide.BaseValue + bottomSide.BaseValue;
    
    // Direction Values
    for(int i=0; i < Directions; i++)
    {
        //sum the value of actions in directions
        fullValue += topSide.Dir[i] + bottomSide.Dir[i];
    }
    
    return fullValue;
}


/**
* Is Token on Board
*/
bool Token::isActive()
{
    return active;
}

/**
* Is top side up
*/
bool Token::isTopSide()
{
    return currentTop;
}


/**
* Get Current Side
*/
Token::Side& Token::currentSide()
{
    return currentTop ? topSide : bottomSide;
}

/**
* get the Top Side
*/
Token::Side& Token::getTopSide()
{
    return topSide;
}

/**
* get the Bottom Side
*/
Token::Side& Token::getBottomSide()
{
    return bottomSide;
}


/**
* Swap Sides
*/
void Token::swapSide()
{
    currentTop = !currentTop;
}
