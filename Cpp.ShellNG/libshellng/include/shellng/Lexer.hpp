/*
Copyright (c) 2012 okard

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions: The above copyright notice and this 
permission notice shall be included in all copies or substantial portions of 
the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
*/
#pragma once
#ifndef __SHELLNG_LEXER__
#define __SHELLNG_LEXER__

#include <memory>

#include <shellng/Types.hpp>
#include <shellng/Exception.hpp>
#include <shellng/Token.hpp>
#include <shellng/Source.hpp>
#include <shellng/Buffer.hpp>


namespace sng {
	
/**
* Lexer Exception
*/
class LexerException : public Exception
{
public:
	/**
	* Constructor
	*/
	LexerException(const char* msg)
		: Exception(msg)
	{
	}
};

/**
* Lexer
* Move to Src because useless token ids 
*/
class Lexer
{
private:
    //SourceFile
    
    /// Source
    std::shared_ptr<Source> src_;
    
    // Buffer
    Buffer buf_;
    std::size_t pos_;
    
    //line number
    std::size_t lineNo_;
    
    //column number
    std::size_t colNo_;
    
public:
    /**
    * Create a new lexer
    */
    Lexer();
    
    /**
    * Destroy lexer
    */
    ~Lexer();
    
    /**
    * Open source file for lexing
    */
    void open(const std::shared_ptr<Source>& src);
    
    /**
    * Close source file
    */
    void close();
    
    /**
    * Get next token
    * set scope (comid/id)
    */
    TokenID next(Token& tok, bool com_identifier = true);
    
    
    //unsigned int next(Token& tok);
    
    static void print(const Token& tok);
    
private:
    
    //TODO callback to shell so shell can request more input?
    //But keeping internal buffer?
    
    /**
    * Fill in buffer from source file
    */
    bool fill();
    
    inline ubyte8 nextChar(bool autofill = true);
    inline ubyte8 peekChar(size_t offset);
    
    inline bool nextLine();
    
    //end of buffer
    inline bool isEOB();
    
    TokenID lexNumber(Token& tok);
    TokenID lexId(Token& tok);
    TokenID lexCommandId(Token& tok);
    TokenID lexString(Token& tok);
    
    inline ubyte8 currentChar();
};


}

#endif // __SHELLNG_LEXER__
