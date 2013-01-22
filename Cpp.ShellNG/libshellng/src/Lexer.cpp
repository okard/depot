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

#include "Parser.h"

using namespace sng;


inline bool isAlpha(const ubyte8 b)
{
	if( b >= 'A' && b <= 'Z')
		return true;
	if ( b >= 'a' && b <= 'z')
		return true;
		
	return false;
}

inline bool isWhitespace(const ubyte8 b)
{
	if( b == ' '
	||  b == '\r'
	||  b == '\n')
		return true;
	
	return false;
}

inline bool isNumeric(const ubyte8 b)
{
	if( b >= '0' && b <= '9')
		return true;
	return false;
}


Lexer::Lexer()
    : src_(nullptr),
      buf_(1024)
{
}

Lexer::~Lexer()
{ 
}
    
void Lexer::open(Source* const src)
{
    src_ = src;
    //initial fill
	fill();
}


void Lexer::close()
{
    src_ = nullptr;
}


bool Lexer::fill()
{
    std::cout << "Lexer::Fill() Eof: " << src_->isEOF() << std::endl;
    
    if(src_->isEOF())
    {
        return false;
    }
    
    //read in first chunk of bytes
    auto size = src_->read(reinterpret_cast<void*>(buf_.bufPtr()), buf_.allocatedMemory());
    buf_.resize(size);
    pos_ = 0;
    
    return true;
}


unsigned int Lexer::next(Token& tok)
{
	//move pos with buffer fill mechanism
	
	//whitespace
	while(isWhitespace(buf_[pos_]))
	{
		if(buf_[pos_] == '\n')
		{
			lineNo_++;
			colNo_ = 0;
		}
			
		pos_++;
	}
	
	//special chars
	switch(buf_[pos_])
	{
		
		case '+': break;
		case '-': break;
		case '*': break;
		case '/': break;
		case '$': break;
		
		case '(': break;
		case ')': break;
		case '{': break;
		case '}': break;
		case '[': break;
		case ']': break;
		
		
		case '"':
			//read string
			break;
			
	}
	
	//tokenize number
	if(isNumeric(buf_[pos_]))
	{
	}
	
	//tokenize identifier and keywords
	if(isAlpha(buf_[pos_]) 
	|| buf_[pos_] == '_')
	{
		//to subfunction
		
		std::size_t tpos = pos_;
		
		while(isAlpha(buf_[pos_])  || buf_[pos_] == '_')
		{
			
			if(pos_ == buf_.size())
			{
				tok.value.append (buf_[tpos], pos_-tpos);
				if(fill())
				{
					tpos_ = pos_;
				}
				else
				{
					break;
				}
			}
			else
				pos_++;
			
			//append if buffer is at end reset tpos
		}
		
		//append
		tok.value.append (buf_[tpos], pos_-tpos);
		
		
		//save temp pos
		//read until end
		//copy to string in tok
		//parse id
		
		//before buffer skip copy
		
		//check for keywords
		//TOKEN_KW_DEF
		//int strncmp ( const char * str1, const char * str2, size_t num );
		//int memcmp ( const void * ptr1, const void * ptr2, size_t num );
		
		//if(tok.value == "def")
		
		//tok.value std::string(const char* s, size_t n);
		
		tok.type = TOKEN_IDENTIFIER;
		
		return tok.type;
	}
	
	
	tok.type = 0;
	
	
	return tok.type;
}


