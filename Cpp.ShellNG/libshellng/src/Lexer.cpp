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
#include <cstdlib>

#include <shellng/Lexer.hpp>
#include <shellng/Token.hpp>

#include<exception>
#include<iostream>

using namespace sng;


Lexer::Lexer()
    : src_(nullptr),
      re2c_cursor_(nullptr),
      re2c_limit_(nullptr),
      re2c_marker_(nullptr),
      buffer_(nullptr),
      bufSize_(0)
{
}

Lexer::~Lexer()
{ 
}
    
void Lexer::open(Source* const src)
{
    src_ = src;
    
    //read initial buffer
    buffer_ = src_->read(&bufSize_);
    
    if(buffer_ != nullptr)
    {
        re2c_cursor_=static_cast<char*>(buffer_);
        re2c_marker_=static_cast<char*>(buffer_);
        //TODO is limit right set?
        re2c_limit_=&static_cast<char*>(buffer_)[bufSize_+1]; 
    }
}


void Lexer::close()
{
    src_ = nullptr;
    re2c_cursor_ = nullptr;
    re2c_limit_ = nullptr;
    re2c_marker_ = nullptr;
    
    if(buffer_ != nullptr)
        free(buffer_);
    
    bufSize_=0;
    buffer_=nullptr;
}


bool Lexer::fill(int size)
{
    std::cout << "Lexer::Fill(" << size << ") Eof: " << src_->isEOF() << std::endl;
    
    if(src_->isEOF())
    {
        return false;
    }
    
    //allocate buffer
    //src_->read(buffer_, size);
    
    //take a look into buffer and so on
    
    //this is used to read a special length from source
    
    //RE2C:
    //YYFILL(n) should adjust YYCURSOR, YYLIMIT, YYMARKER
    
    //fill from buffer 
    //for source files and son
    //or fill it from command line
    //via callback
    
    //initial read(size_t& size)
    //then use internal buffer?
    
    //source_
    
    
    return true;
}


/**
* The current marked token content
*/
const char* Lexer::getTokenContent()
{
	//return 
}


#include "Lexer_re2c.inc"
