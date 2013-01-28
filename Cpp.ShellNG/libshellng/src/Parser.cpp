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

#include <shellng/Parser.hpp>


#include <iostream>

using namespace sng;


NodePtr Parser::parse()
{
	lexer_.next(curTok_);
	
	if(curTok_.id == TOKEN_KW_DEF)
		return parseDeclaration();
	else
		return parseStatement();
	
	//else return parseStatement
	
	NodePtr ptr(new Node());
	
	return ptr;
}


NodePtr Parser::parseDeclaration()
{
	std::cout << "parseDeclaration()" << std::endl;
	
	//object
	//function
	//string
	//number
	//clone
	
	NodePtr decl(new Decl());
	return decl;
}


NodePtr Parser::parseStatement()
{
	std::cout << "parseStatement()" << std::endl;
	
	switch(curTok_.id)
	{
		case TOKEN_KW_IF:
			return parseIfStatement();
		case TOKEN_KW_FOR:
			return parseForStatement();
		//case TOKEN_KW_WHILE:
		//	
	}
	
	//if Identifier_ID
	//else 
	//parse expr
	
	
	NodePtr stmt(new Stmt());
	return stmt;
}

NodePtr Parser::parseIfStatement()
{
	NodePtr stmt(new IfStmt());
	return stmt;
}

NodePtr Parser::parseForStatement()
{
	NodePtr stmt(new ForStmt());
	return stmt;
}

NodePtr Parser::parseCommandStatement()
{
	NodePtr stmt(new Stmt());
	return stmt;
}

NodePtr Parser::parseExpression()
{
	//if $expr a normal expression
	
	//if number
	//else commandExpression
	
	
	NodePtr expr(new Expr());
	return expr;
}

NodePtr Parser::parseBinaryExpression()
{
	NodePtr expr(new Expr());
	return expr;
}
