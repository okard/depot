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
	||  b == '\t'
	||  b == '\r'
	/*||  b == '\n'*/)
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

void checkKeywords(Token& tok)
{
	if(tok.value == "def")
		tok.id = TokenID::TOKEN_KW_DEF;
	else if (tok.value == "if")
		tok.id = TokenID::TOKEN_KW_IF;
	else if (tok.value == "object")
		tok.id = TokenID::TOKEN_KW_OBJECT;
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
    
    //TODO skip shebang line already here?
    //TODO first read detect BOM and skip?
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
    
    //read in first chunk of bytes
    auto size = src_->read(reinterpret_cast<void*>(buf_.bufPtr()), buf_.allocatedMemory());
    buf_.resize(size); //set right content size
    pos_ = 0;
    
    std::cout.write(reinterpret_cast<const char*>(buf_.bufPtr()), buf_.size());
    
    return true;
}

bool Lexer::nextLine()
{
	while(buf_[pos_] != '\n')
		nextChar();
	
	std::cout << "nextline: pos: " << pos_ << std::endl;
}

//result?
ubyte8 Lexer::nextChar(bool autofill) 
{		
	//at end of buffer
	if(isEOB() && !autofill)
	{
		return 0x00;
	}
	else if(isEOB())
	{
		fill();
		return currentChar();
	}
	
	
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
	
	assert(skip > 0);
	
	//goes over current buffer
	
	if( pos_ + skip > buf_.size())
	{
		std::cerr << "SKIP over Buffer" << std::endl;
		return 0x00;
	}
	
	pos_ += skip;
	colNo_++;
	
	//handle at next
	if(buf_[pos_] == '\n')
	{
		lineNo_++;
		colNo_ = 0;
	}
	
	//std::cout << "nextchar: pos: " << pos_ << std::endl;
	
	return buf_[pos_];
}

inline ubyte8 Lexer::peekChar(size_t offset)
{
	if(offset + pos_ < 0 || offset + pos_ >= buf_.size())
		return 0x00;

	return buf_[pos_+offset];
}

TokenID Lexer::next(Token& tok, bool com_identifier)
{
	//clear the token 
	tok.id = TokenID::TOKEN_UNKOWN;
	tok.value.clear();
	
	if(!src_)
		throw LexerException("No Source File");
	
	//buffer is empty and no more todo
	if(isEOB() && src_->isEOF())
	{
		tok.id = TokenID::TEOF;
		return tok.id;
	}
	
	//at the end of buffer try to fill
	if(isEOB() && !fill())
	{
		//can not happen? the source file has to be eof then
		assert(false);
	}
	
	//move pos with buffer fill mechanism
	
	//whitespace is also irrelevant for command identifier
	while(isWhitespace(buf_[pos_]))
	{
		nextChar();
	}
	
	
	//chars with higher priority as com_identifier /* // $
	switch(buf_[pos_])
	{
		case '$': 
			nextChar();
			lexId(tok);
			tok.id = TokenID::TOKEN_IDENTIFIER_ID;
			nextChar();
			return tok.id;
			
		case '/':
			if(peekChar(1) == '/')
			{
				nextLine();
				return next(tok, com_identifier);
			}
			break;
			
		case '"':
			return lexString(tok);
	}
	
	//pay attention to commandline args
	//command identifier when requested
	// $ is not allowed
	if(com_identifier &&((isAsciiChar(buf_[pos_]) || utf8CharSize(buf_[pos_]) > 1)))
	{
		lexCommandId(tok);
		nextChar();
		checkKeywords(tok); //todo not all keywords
		return tok.id;
	}
	
	//special chars
	switch(buf_[pos_])
	{
		case '+': 
			tok.id = TokenID::TOKEN_PLUS;
			nextChar();
			return tok.id;
		case '-': 
			tok.id = TokenID::TOKEN_MINUS;
			nextChar();
			return tok.id;
		case '*':
			tok.id = TokenID::TOKEN_MUL;
			nextChar();
			return tok.id;
		case '/': 
			tok.id = TokenID::TOKEN_DIV;
			nextChar();
			//comments handled above
			return tok.id;
			
		case '=':
			tok.id = TokenID::Assign;
			nextChar();
			return tok.id;
					
		case ':':
			tok.id = TokenID::Colon;
			nextChar();
			return tok.id;
			
		case '.':
			tok.id = TokenID::Dot;
			nextChar();
			return tok.id;
			
		case ';':
			tok.id = TokenID::Semicolon;
			nextChar();
			return tok.id;
			
		case '(': 
			tok.id = TokenID::TOKEN_ROBRACKET;
			nextChar();
			return tok.id;
			
		case ')': 
			tok.id = TokenID::TOKEN_RCBRACKET;
			nextChar();
			return tok.id;
			
		case '{': 
			tok.id = TokenID::TOKEN_COBRACKET;
			nextChar();
			return tok.id;
			
		case '}':
			tok.id = TokenID::TOKEN_CCBRACKET;
			nextChar();
			return tok.id;
			
		case '[':
			tok.id = TokenID::TOKEN_SOBRACKET;
			nextChar();
			return tok.id;
			
		case ']': 
			tok.id = TokenID::TOKEN_SCBRACKET;
			nextChar();
			return tok.id;
			
		case '\\':
			//lex escape line end
			break;
			
		case '\n':
			tok.id = TokenID::TEOL;
			nextChar();
			return tok.id;
			
		//skip shebang line
		case '#':
			if(peekChar(1) == '!')
				nextLine();
			return next(tok, com_identifier);
			
			break;		
	}
	
	//tokenize number
	if(!com_identifier && isNumeric(buf_[pos_]))
	{
		lexNumber(tok);
		nextChar();
		return tok.id;
	}
	
	//tokenize identifier and keywords
	if(!com_identifier && (isAlpha(buf_[pos_])  || buf_[pos_] == '_'))
	{
		lexId(tok);
		nextChar();
		checkKeywords(tok);
		return tok.id;
	}
	
	
	std::cout << "unkown char: <" << buf_[pos_] << ">" << std::endl;
	//unkown token == error
	tok.id = TokenID::TOKEN_UNKOWN;
	nextChar();
	return tok.id;
}


TokenID Lexer::lexNumber(Token& tok)
{
	//while(isNumeric())
	
	while(isNumeric(buf_[pos_]))
	{
		nextChar();
		
	}
	
	tok.id = TokenID::TOKEN_NUMBER;
	return tok.id;
}

TokenID Lexer::lexId(Token& tok)
{	
	//save start position of id
	std::size_t tpos = pos_;
	
	//now numbers are allowed
	while(isAlpha(buf_[pos_])  || buf_[pos_] == '_')
	{
		//if position is at the end of the current buffer
		// append the current value and go forward with the next buffer
		if(isEOB())
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
			nextChar(false);	
	}
	
	//append
	tok.value.append (reinterpret_cast<const char*>(buf_.bufPtr(tpos)), pos_-tpos);
	
	tok.id = TokenID::TOKEN_IDENTIFIER;
	return tok.id;
}

TokenID Lexer::lexCommandId(Token& tok)
{
	//contains complex characters not only ascii [a-zA-Z_]
	std::size_t tpos = pos_;
	
	while(isAsciiChar(buf_[pos_]) || utf8CharSize(buf_[pos_]) > 1)
	{
		if(isEOB())
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
			nextChar(false);
	}
	tok.value.append (reinterpret_cast<const char*>(buf_.bufPtr(tpos)), pos_-tpos);
	
	tok.id = TokenID::TOKEN_IDENTIFIER_COM;
	return tok.id;
}

TokenID Lexer::lexString(Token& tok)
{
	assert(buf_[pos_] == '"');
	
	nextChar(); //skip "
	
	std::size_t tpos = pos_;
	
	//isAsciiChar() && utf8CharSize()
	
	while(buf_[pos_] != '"')
	{
		//std::cout << "lex string: pos: " << pos_ << std::endl;
		//TODO Escaping
		//if(buf_[pos_] == '\\')
		
		if(isEOB())
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
		else
			nextChar(false);
	}
	tok.value.append (reinterpret_cast<const char*>(buf_.bufPtr(tpos)), pos_-tpos);
	
	assert(buf_[pos_] == '"');
	
	//skip ending "
	nextChar();
	
	tok.id = TokenID::String;
	return tok.id;
}


ubyte8 Lexer::currentChar()
{
	return buf_[pos_];
}


void Lexer::print(const Token& tok)
{
	switch(tok.id)
	{
		case TokenID::TOKEN_IDENTIFIER:
			std::cerr << "IDENTIFIER: " << tok.value;
			break;
			
		case TokenID::TOKEN_IDENTIFIER_ID:
			std::cerr << "ID_IDENTIFIER: " << tok.value;
			break;
			
		case TokenID::TOKEN_IDENTIFIER_COM:
			std::cerr << "COM_IDENTIFIER: " << tok.value;
			break;
			
		case TokenID::String:
			std::cerr << "String: " << tok.value;
			break;
			
		case TokenID::TEOL:
			std::cerr << "End of Line"; break;
		
		default:
			std::cerr << "Not configured Token:" << static_cast<int>(tok.id);
	}
	
	std::cerr << std::endl;
}
