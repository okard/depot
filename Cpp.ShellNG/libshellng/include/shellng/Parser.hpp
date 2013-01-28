/*
Copyright (c) 2013 okard

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
#ifndef __SHELLNG_PARSER__
#define __SHELLNG_PARSER__

#include <shellng/Types.hpp>
#include <shellng/Lexer.hpp>
#include <shellng/Ast.hpp>

namespace sng {

class Parser 
{
private:
	Lexer lexer_;

	//buffer token?
	Token curTok_;

public:	

	NodePtr parse();
	
	inline Lexer& getLexer() { return lexer_; }
	
	
private:

	NodePtr parseDeclaration();
	
	NodePtr parseStatement();
	NodePtr parseIfStatement();
	NodePtr parseForStatement();
	NodePtr parseCommandStatement();
	
	NodePtr parseExpression();
	NodePtr parseBinaryExpression();
	
	
	//helper


};


}//end namespace sng

#endif
