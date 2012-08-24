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

#include <shellng/Token.hpp>
#include <shellng/Source.hpp>

namespace sng {

/**
* Lexer
* Move to Src because useless token ids 
*/
class Lexer
{
private:
    //SourceFile
    
    /// Source
    Source* src_;
      
    //re2c stuff
    char* re2c_cursor_;
    char* re2c_limit_;
    char* re2c_marker_;
    
    static const unsigned int RE2C_MAXFILL;
    
    //buffer
    void* buffer_;
    size_t bufSize_;
    
    //what is required
    // buffer memory
    char* m_buffer;
    char* m_token; //is is required?
    int m_buffer_size;
    int m_lineno;  
 
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
    void open(Source* const src);
    
    /**
    * Close source file
    */
    void close();
    
    /**
    * Get next token
    */
    unsigned int next(Token& tok);
    
private:
    
    //TODO callback to shell so shell can request more input?
    //But keeping internal buffer?
    
    /**
    * Fill in buffer from source file
    */
    bool fill(int size);
    
};


}

#endif // __SHELLNG_LEXER__