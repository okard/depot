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

//all printable ascii chars 33-126
inline bool isAsciiChar(const ubyte8 b)
{
	if(b >= '!' && b <= '~')
		return true;
	return false;
}

inline ubyte8 utf8CharSize(const ubyte8 b)
{
	//4byte utf8
	if((b & 0xF0) == 0xF0)
		return 4;
	
	//3 byte utf8
	if((b & 0xE0) == 0xE0)
		return 3;
		
	//2 byte utf8
	if((b & 0xC0) == 0xC0)
		return 2;
		
	// if 10 it is follow byte
	if((b >> 7) == 1)
		return 0;
	else
		return 1; //standard ascii/utf8 char
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
    
    if(src_ == nullptr)
		return false;
    
    if(src_->isEOF())
        return false;
        
	//first read detect BOM
    
    //read in first chunk of bytes
    auto size = src_->read(reinterpret_cast<void*>(buf_.bufPtr()), buf_.allocatedMemory());
    buf_.resize(size); //set right content size
    pos_ = 0;
    
    return true;
}


TokenID Lexer::next(Token& tok)
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
		case '$': break; //make $id a special token?
						 // after a $ a id is expected
		
		case '(': break;
		case ')': break;
		case '{': break;
		case '}': break;
		case '[': break;
		case ']': break;
		
		
		case '"':
			return lexString(tok);
			//read string
			break;
			
	}
	
	//tokenize number
	if(isNumeric(buf_[pos_]))
	{
		return lexNumber(tok);
	}
	
	//tokenize identifier and keywords
	if(isAlpha(buf_[pos_]) 
	|| buf_[pos_] == '_')
	{
		//to subfunction
		return lexId(tok);
	}
	
	
	tok.id = TOKEN_UNKOWN;
	
	
	return tok.id;
}


TokenID Lexer::lexNumber(Token& tok)
{
	//while(isNumeric())
	
	
	tok.id = TOKEN_UNKOWN;
	return tok.id;
}

TokenID Lexer::lexId(Token& tok)
{
	//notice id are all chars exclude whitespaces?
	// and exclude $
	// unicode utf8!
	
	//save start position of id
	std::size_t tpos = pos_;
	
	//now numbers are allowed
	while(isAlpha(buf_[pos_])  || buf_[pos_] == '_')
	{
		//if position is at the end of the current buffer
		// append the current value and go forward with the next buffer
		if(pos_ == buf_.size())
		{
			//append if buffer is at end reset tpos
			tok.value.append (reinterpret_cast<const char*>(buf_.bufPtr(tpos)), pos_-tpos);
			if(fill())
			{
				tpos = pos_;
			}
			else
			{
				break;
			}
		}
		else
			pos_++;	
	}
	
	//append
	tok.value.append (reinterpret_cast<const char*>(buf_.bufPtr(tpos)), pos_-tpos);
	
	
	//check for keywords
	//TOKEN_KW_DEF
	//int strncmp ( const char * str1, const char * str2, size_t num );
	//int memcmp ( const void * ptr1, const void * ptr2, size_t num );
	
	//if(tok.value == "def")
	
	//tok.value std::string(const char* s, size_t n);
	
	tok.id = TOKEN_IDENTIFIER;
	
	return tok.id;
}

TokenID Lexer::lexCommandId(Token& tok)
{
	
	
	return tok.id;
}

TokenID Lexer::lexString(Token& tok)
{
	std::size_t tpos = pos_;
	
	
	while(buf_[pos_] != '"')
	{
		//TODO Escaping
		
		pos_++;
		
	}
	
	tok.value.append (reinterpret_cast<const char*>(buf_.bufPtr(tpos)), pos_-tpos);
}

