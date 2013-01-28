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
#include <cassert>
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
	// 0x00 - 0x20 ??? 0x7F
	
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
	//4byte utf8 1111 xxxx
	if((b & 0xF0) == 0xF0)
		return 4;
	
	//3 byte utf8 111x xxxx
	if((b & 0xE0) == 0xE0)
		return 3;
		
	//2 byte utf8 11xx xxxx
	if((b & 0xC0) == 0xC0)
		return 2;
		
	// if 10 it is follow byte 10xx xxxx
	if((b >> 7) == 1)
		return 0;
	
	assert( b <= 0x7F);
	return 1; //standard ascii/utf8 char 0x00 - 0x7F
}


Lexer::Lexer()
    : src_(nullptr),
      buf_(1024)
{
}

Lexer::~Lexer()
{ 
}
    
void Lexer::open(const std::shared_ptr<Source>& src)
{
    src_ = src;
    //initial fill
	fill();
}


void Lexer::close()
{
    src_.reset();
}


bool Lexer::isEOB()
{
	//no content in buffer
	if(buf_.size() == 0)
		return true;
			
	//position is at the end of buffer
	if(pos_ == buf_.size())
		return true;
		
	return false;
}

bool Lexer::fill()
{
    if(!src_)
		throw LexerException("No Source File");
		
	 std::cout << "Lexer::Fill() Eof: " << src_->isEOF() << std::endl;
    
    if(src_->isEOF())
        return false;
        
	//first read detect BOM
    
    //read in first chunk of bytes
    auto size = src_->read(reinterpret_cast<void*>(buf_.bufPtr()), buf_.allocatedMemory());
    buf_.resize(size); //set right content size
    pos_ = 0;
    
    return true;
}

bool Lexer::nextLine()
{
	while(nextChar() && buf_[pos_] != '\n');
}

ubyte8 Lexer::nextChar()
{
	if(buf_[pos_] == '\n')
	{
		lineNo_++;
		colNo_ = 0;
	}
		
	//at end of buffer
	if(pos_ == buf_.size())
		return 0x00;
	
	size_t skip = 1;
	
	switch(src_->getEncoding())
	{
		case ENCODING_UTF8:
			skip = utf8CharSize(buf_[pos_]);
			break;
		case ENCODING_UTF16:
			skip = 2;
			break;
		case ENCODING_UTF32:
			skip = 4;
			break;
	}
	
	//goes over current buffer
	if( pos_ + skip > buf_.size())
		return 0x00;
	
	pos_ += skip;
	colNo_++;
	
	return buf_[pos_];
}


TokenID Lexer::next(Token& tok)
{
	//buffer is empty and no more todo
	if(isEOB() && (!src_ || src_->isEOF()))
	{
		tok.id = TOKEN_EOF;
		return tok.id;
	}
	
	//move pos with buffer fill mechanism
	
	//whitespace
	while(isWhitespace(buf_[pos_]))
	{
		nextChar();
		
		if(isEOB() && !src_ && !src_->isEOF())
		{
			fill();
		}
		else
		{
			//no more todo
			tok.id = TOKEN_EOF;
			return tok.id;
		}
	}
	
	//special chars
	switch(buf_[pos_])
	{
		
		case '+': 
			tok.id = TOKEN_PLUS;
			return tok.id;
		case '-': 
			tok.id = TOKEN_MINUS;
			return tok.id;
		case '*':
			tok.id = TOKEN_MUL;
			return tok.id;
		case '/': 
			tok.id = TOKEN_DIV;
			return tok.id;
		case '$': 
			pos_++;
			lexId(tok);
			tok.id = TOKEN_IDENTIFIER_ID;
			return tok.id;
		
		case '(': 
			tok.id= TOKEN_ROBRACKET;
			return tok.id;
		case ')': 
			tok.id = TOKEN_RCBRACKET;
			return tok.id;
		case '{': 
			tok.id = TOKEN_COBRACKET;
			return tok.id;
		case '}':
			tok.id = TOKEN_CCBRACKET;
			return tok.id;
		case '[':
			tok.id = TOKEN_SOBRACKET;
			return tok.id;
		case ']': 
			tok.id = TOKEN_SCBRACKET;
			return tok.id;
			
		//skip shebang line
		case '#':
			if(nextChar() == '!')
				nextLine();
			return next(tok);
			
			break;
		
		
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
	
	
	//com id here
	
	//default parse com identifier
	// set scope via parameter to parse_identifier
	
	//tokenize identifier and keywords
	if(isAlpha(buf_[pos_]) 
	|| buf_[pos_] == '_')
	{
		lexId(tok);
		
		//keyword check
		if(tok.value == "def")
			tok.id = TOKEN_KW_DEF;
		else if (tok.value == "if")
			tok.id = TOKEN_KW_IF;
		
		//to subfunction
		return tok.id;
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
	
	std::size_t tpos = pos_;
	
	while(isAsciiChar(buf_[pos_]) || utf8CharSize(buf_[pos_]) > 1)
	{
		
	}
	
	
	return tok.id;
}

TokenID Lexer::lexString(Token& tok)
{
	assert(buf_[pos_] == '"');
	
	pos_++; //skip "
	
	std::size_t tpos = pos_;
	
	//isAsciiChar() && utf8CharSize()
	
	while(buf_[pos_] != '"')
	{
		//TODO Escaping
		
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
				throw LexerException("Invalid String Token");
			}
		}

		pos_++;
		
	}
	
	tok.value.append (reinterpret_cast<const char*>(buf_.bufPtr(tpos)), pos_-tpos);
}

